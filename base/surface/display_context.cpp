/*
 * This file is part of the ux_gui_stream distribution
 * (https://github.com/amatarazzo777/ux_gui_stream).
 * Copyright (c) 2020 Anthony Matarazzo.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @author Anthony Matarazzo
 * @file display_context.cpp
 * @date 9/7/20
 * @version 1.0
 * @brief
 */
// clang-format off

#include <base/unit_object.h>
#include <base/render_base.h>
#include "region.h"
#include "display_context.h"

// clang-format on

uxdevice::display_context_t::display_context_t(
    std::shared_ptr<os_window_manager> _wm)
    : window_manager(_wm) {}

uxdevice::display_context_t::display_context_t(const display_context_t &other)
    : hash_members_t(other), system_error_t(other), pipeline_memory_t(other),
      regions_storage(other.regions_storage),
      surface_requests_storage(other.surface_requests_storage) {}

// move constructor
uxdevice::display_context_t::display_context_t(
    display_context_t &&other) noexcept
    : hash_members_t(other), system_error_t(other), pipeline_memory_t(other),
      regions_storage(other.regions_storage),
      surface_requests_storage(other.surface_requests_storage) {}

/**
 * @fn display_context_t operator =&(const display_context_t&)
 * @brief
 *
 * @param other
 * @return
 */
uxdevice::display_context_t &uxdevice::display_context_t::operator=(
    const uxdevice::display_context_t &other) {
  hash_members_t::operator=(other);
  system_error_t::operator=(other);
  pipeline_memory_t::operator=(other);

  regions_storage = other.regions_storage;
  surface_requests_storage = other.surface_requests_storage;

  return *this;
}

/**
 * @internal
 * @brief The routine checks the system for render work which primarily arrives
 * to the thread via the regions list. However, when no official work exists,
 * the condition variable cvRenderWork is placed in a wait state. The condition
 * may be awoke by calling the routine state_notify_complete().
 * @return bool - true - work exists, false none.
 */
bool uxdevice::display_context_t::surface_prime() {
  bool bRet = false;

  // no surface allocated yet, TODO refine surface_fn to provide auto return -
  // concepts20
  window_manager->surface_fn([&](auto surface) { bRet = surface != nullptr; });

  if (!bRet)
    return bRet;

  // determine if painting should also occur
  bRet = state();
  if (bRet)
    return bRet;

  // wait for render work if none has already been provided.
  // the state routines could easily produce region rectangular information
  // along the notification but do not. The user should call notify_complete.
  if (!bRet) {
    std::unique_lock<std::mutex> lk(render_work_mutex);
    render_work_condition_variable.wait(lk);
    lk.unlock();
    bRet = true;
  }

  return bRet;
}
/**
 * @internal
 * @brief The routine provides the synchronization of the xcb cairo surface and
 * the video system of xcb.
 */
void uxdevice::display_context_t::flush() { window_manager->video_flush(); }

/**
 * @internal
 * @brief The routine
 */
void uxdevice::display_context_t::device_offset(double x, double y) {
  window_manager->surface_fn(
      [&](auto surface) { cairo_surface_set_device_offset(surface, x, y); });

  state(0, 0, window_manager->window_width, window_manager->window_height);
}
/**
 * @internal
 * @brief The routine
 */
void uxdevice::display_context_t::device_scale(double x, double y) {
  window_manager->surface_fn(
      [&](auto surface) { cairo_surface_set_device_scale(surface, x, y); });

  state(0, 0, window_manager->window_width, window_manager->window_height);
}

/**
 * @internal
 * @brief The routine is called by a client to resize the window surface. In
 * addition, other work may be applied such as paint, however those go into a
 * separate list as the operating system provides these message independently,
 * that is Configure window event and a separate paint rectangle.
 */
void uxdevice::display_context_t::resize_surface(const int w, const int h) {
  window_manager->resize_surface(w, h);
}

/**
 * @internal
 * @brief The routine paints the surface requests. The background brush is
 * emitted first then plot routine is called.
 */
void uxdevice::display_context_t::render(void) {

}

/**
 * @internal
 * @param std::shared_ptr<display_visual_t> _obj
 * @brief The routine adds a drawing output object to the appropriate list, on
 * or offscreen. If the item is on screen, a region area paint is requested
 * for the object's area.
 */
void uxdevice::display_context_t::add_visual(
    std::shared_ptr<display_visual_t> object_ptr) {

  /** @brief Allow object to instantiate itself. The object will select the
  visitor_target_bits from the pipeline memory. As well, add any special
  pipeline memory parameters used to communicate to other objects. Such as
  context variables like PangoLayout *. The object sets its ink_area at this
  point.

  */
  object_ptr->emit(this);

  /** @brief perform intersection test with the viewport */
  object_ptr->intersect(viewport_rectangle);

  /** initialize the display_visual_t object to utilize the drawing pipeline.
   * Both base (fn, clipping) and cached(fn,clipping) are initialized;*/
  auto ptr_pipeline = std::dynamic_pointer_cast<pipeline_memory_t>(object_ptr);

  object_ptr->fn_base_surface = [&]() {
    object_ptr->fn_draw = [&]() { ptr_pipeline->pipeline_visit(this); };

    object_ptr->fn_draw_clipped = [&]() {
      window_manager->draw_fn([&](auto cr) {

        ptr_pipeline->pipeline_visit(this);

      });

      /**@brief linkage of object invocation within the current
       * display_context_t. "this" internally to the object provides the link
       * to pipeline memory visitation. The function uses the window_manager
       * internally to reference cairo_t and other attributes. The
       * ptr_pipeline->pipeline_visit(this); function is distinct for each
       * visual object as the drawing operations, order and initialization are
       * encapsulated. */
      ptr_pipeline->pipeline_visit(this);

      window_manager->draw_fn([&](auto cr) { });
    };
  };

  object_ptr->fn_cache_surface = object_ptr->fn_base_surface;

  // validate object
  if (!ptr_pipeline->pipeline_has_required_linkages())
    return; // not adding error objects

  if (object_ptr->overlap == CAIRO_REGION_OVERLAP_OUT) {
    std::lock_guard lock(viewport_off_mutex);
    viewport_off.emplace_back(object_ptr);

  } else {
    std::lock_guard lock(viewport_on_mutex);
    viewport_on.emplace_back(object_ptr);
    state(object_ptr);
  }
}
/**
 * @internal
 * @brief The routine scans the offscreen list to see if any are now visible.
 */
void uxdevice::display_context_t::partition_visibility(void) {}

/**
 * @internal
 * @brief The routine clears the display context.
 */
void uxdevice::display_context_t::clear(void) {
  clearing_frame = true;

  {
    std::scoped_lock(regions_storage_mutex, viewport_on_mutex,
                     viewport_off_mutex);
    regions_storage.remove_if([](auto &n) { return !n.bOSsurface; });
    viewport_on.clear();
    viewport_off.clear();
  }

  offsetx = 0;
  offsety = 0;

  pipeline_memory_clear();
  state(0, 0, window_manager->window_width, window_manager->window_height);
}
/**
 * @internal
 * @brief The routine sets the background surface brush.
 */
void uxdevice::display_context_t::surface_brush(painter_brush_t &b) {

  {
    std::lock_guard lock(window_manager->background_brush_mutex);
    window_manager->background_brush = b;
  }

  state(0, 0, window_manager->window_width, window_manager->window_height);
}

/**
 * @internal
 * @brief The routine accepts a drawing output object and adds the
 * associated render work with the object's coordinate_t. note
 * stateNotifyComplete must be called after this to inform the renderer
 * there is work.
 */
void uxdevice::display_context_t::state(std::shared_ptr<display_visual_t> obj) {
  std::lock_guard lock(regions_storage_mutex);
  std::size_t onum = reinterpret_cast<std::size_t>(obj.get());

  regions_storage.emplace_back(context_cairo_region_t(
      onum, obj->ink_rectangle.x, obj->ink_rectangle.y,
      obj->ink_rectangle.width, obj->ink_rectangle.height));
}

/**
 * @internal
 * @brief The routine adds a generalized region area paint for the rendered
 * to find. note stateNotifyComplete must be called after this to inform the
 * renderer there is work.
 */
void uxdevice::display_context_t::state(int x, int y, int w, int h) {
  std::lock_guard lock(regions_storage_mutex);
  regions_storage.emplace_back(context_cairo_region_t{false, x, y, w, h});
}

/**
 * @internal
 * @brief The routine adds a surface oriented painting request to the render
 * queue. the items are inserted first before any other so that painting of
 * a newly resized window area occurs first.
 */
void uxdevice::display_context_t::state_surface(int x, int y, int w, int h) {
  std::lock_guard lock(regions_storage_mutex);

}
/**
 * @internal
 * @brief The routine notifies the condition variable that work has been
 * requested and should immediately being to render. Having this as a
 * separate function provides the ability to add work without rendering
 * occurring. However, message queue calls this when a resize occurs.
 */
void uxdevice::display_context_t::state_notify_complete(void) {
  render_work_condition_variable.notify_one();
}

/**
 * @internal
 * @brief The routine returns whether work is within the system.
 */
bool uxdevice::display_context_t::state(void) {
  bool ret = {};

  {
    std::lock_guard lock(regions_storage_mutex);
    ret = !regions_storage.empty();
  }

  /** surface requests should be performed, the render function sets the
   * surface size and exits if no region work.*/
  if (!ret) {
    {
      std::lock_guard lock(surface_requests_storage_mutex);
      ret = !surface_requests_storage.empty();
    }
  }

  return ret;
}

/**
 * @internal
 * @fn plot
 * @param context_cairo_region_t &plotArea
 * @details Routine iterates each of objects that draw and tests if the
 * rectangle is within the region.
 */
void uxdevice::display_context_t::plot(context_cairo_region_t &plotArea) {
  bool bDone = false;

}

bool uxdevice::display_context_t::pipeline_has_required_linkages(void) {
  return true;
}

std::size_t uxdevice::display_context_t::hash_code(void) {
  std::size_t __value = {};
  hash_combine(__value, std::type_index(typeid(this)),
               pipeline_memory_hash_code());

  return __value;
}
