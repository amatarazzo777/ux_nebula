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
 * @file textual_render_storage.cpp
 * @date Sep 24, 2020
 * @version 1.0
 * @brief
 */
// clang-format off

#include <base/unit_object.h>
#include "textual_render_storage.h"

// clang-format on

uxdevice::textual_render_storage_t::textual_render_storage_t() {}

uxdevice::textual_render_storage_t::~textual_render_storage_t() {
  if (layout)
    g_object_unref(layout);
}

/// @brief move constructor
uxdevice::textual_render_storage_t::textual_render_storage_t(
    textual_render_storage_t &&other) noexcept
    : hash_members_t(other), system_error_t(other), display_visual_t(other),
      pipeline_memory_t(other), layout(other.layout), ink_rect(other.ink_rect),
      logical_rect(other.logical_rect) {}

/// @brief copy constructor
uxdevice::textual_render_storage_t::textual_render_storage_t(
    const textual_render_storage_t &other)
    : hash_members_t(other), system_error_t(other), display_visual_t(other),
      pipeline_memory_t(other), ink_rect(other.ink_rect),
      logical_rect(other.logical_rect) {
  if (other.layout)
    layout = pango_layout_copy(other.layout);
}

/// @brief copy assignment
uxdevice::textual_render_storage_t &
uxdevice::textual_render_storage_t::operator=(
    const textual_render_storage_t &other) {
  hash_members_t::operator=(other);
  system_error_t::operator=(other);
  display_visual_t::operator=(other);
  pipeline_memory_t::operator=(other);

  if (other.layout)
    layout = pango_layout_copy(other.layout);
  ink_rect = other.ink_rect;
  logical_rect = other.logical_rect;
  return *this;
}

/// @brief move assignment
uxdevice::textual_render_storage_t &
uxdevice::textual_render_storage_t::operator=(
    const textual_render_storage_t &&other) noexcept {
  hash_members_t::operator=(other);
  system_error_t::operator=(other);
  display_visual_t::operator=(other);
  pipeline_memory_t::operator=(other);
  layout = other.layout;
  ink_rect = other.ink_rect;
  logical_rect = other.logical_rect;
  return *this;
}

/**
 * @internal
 * @fn textual_render_storage_t::hash_code(void)
 * @brief hash code of the textual rendering. used to detect changes that might
 * occur within all of the dependent rendering parameters,
 * @return std::size_t the hash value
 */
std::size_t uxdevice::textual_render_storage_t::hash_code(void) const noexcept {
  std::size_t __value = {};
  hash_combine(__value, std::type_index(typeid(textual_render_storage_t)),
               pango_layout_get_serial(layout), ink_rect.x, ink_rect.y,
               ink_rect.width, ink_rect.height, matrix.hash_code(),
               pipeline_memory_hash_code());
  return __value;
}

/**
 * @internal
 * @fn textual_render_storage_t::pipeline_acquire
 * @param cairo_t *cr
 * @param coordinate_t *a
 * @brief
 */
void uxdevice::textual_render_storage_t::pipeline_acquire() {
  /**  @details The cached rendering function has not been established, create
   * the text rendering pipeline consisting of individualized lambda functions.
   */

  /** @brief
   *
   * these steps are common in the first part of the textual rendering  The
   * visitor of the pango, and cairo operate in a sorted fashion to execute
   * themselves within a rule based set of order. refinements within the stream
   * can occur as successive execution happens but this is not facilitated by
   * current code (pipeline_optimize is suffice). Initialization for example,
   * and build up of graphics composite layers.
   */



  return;
}

/**
 * @internal
 * @fn textual_render_storage_t::pipeline_has_required_linkages
 * @brief
 * @return bool
 */
bool uxdevice::textual_render_storage_t::pipeline_has_required_linkages(void) {
  if (!((pipeline_memory_access<text_color_t>() ||
         pipeline_memory_access<text_outline_t>() ||
         pipeline_memory_access<text_fill_t>()) &&
        pipeline_memory_access<coordinate_t>() &&
        pipeline_memory_access<text_data_t>() &&
        pipeline_memory_access<text_font_t>())) {
    const char *s = "A textual_render_t object must include the following "
                    "attributes: A text_color_t, text_outline_t or "
                    " text_fill_t. As well, a coordinate_t, text and "
                    "text_font_t object.";
    error_report(s);
    return false;
  }
  return true;
}
