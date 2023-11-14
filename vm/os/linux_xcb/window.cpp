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
 * @file ux_os_xcb_linux.h
 * @date Oct 12, 2020
 * @version 1.0
 * @details The file implements the os interface which provides the
 * communication to the os for basic visualization services such as window
 * manager functions. The message queue processor is defined and implemented
 * here.
 */
// clang-format off

#include <base/unit_object.h>


#include <os/linux_xcb/os.h>
#include <os/linux_xcb/window.h>

// clang-format on

using namespace std;
using namespace uxdevice;

uxdevice::os_xcb_linux_t::os_xcb_linux_t() {  }
uxdevice::os_xcb_linux_t::~os_xcb_linux_t() { }

/// @brief copy constructor
uxdevice::os_xcb_linux_t::os_xcb_linux_t(const os_xcb_linux_t &other) : {}

/// @brief move constructor
uxdevice::os_xcb_linux_t::os_xcb_linux_t(os_xcb_linux_t &&other) noexcept : {}

/**
 * @fn uxdevice::os_xcb_linux_t operator =&(const os_xcb_linux_t&)
 * @brief copy assignment operator
 *
 * @param other
 * @return
 */
uxdevice::os_xcb_linux_t &
uxdevice::os_xcb_linux_t::operator=(const os_xcb_linux_t &other) {
  window_manager_base_t::operator=(other);

  xdisplay = other.xdisplay;
  connection = other.connection;
  screen = other.screen;
  window = other.window;
  graphics = other.graphics;
  visual_type = other.visual_type;
  return *this;
}

/**
 * @fn uxdevice::os_xcb_linux_t operator =&(os_xcb_linux_t&&)
 * @brief move assignment operator
 *
 * @param other
 * @return
 */
uxdevice::os_xcb_linux_t &
uxdevice::os_xcb_linux_t::operator=(os_xcb_linux_t &&other) noexcept {
  window_manager_base_t::operator=(other);
  xdisplay = other.xdisplay;
  connection = other.connection;
  screen = other.screen;
  window = other.window;
  graphics = other.graphics;
  visual_type = other.visual_type;

  return *this;
}



void uxdevice::os_xcb_linux_t::fn_close_window(void) {
    xcb_shm_detach(m_connection, m_info.shmseg);
  shmdt(m_info.shmaddr);

  xcb_free_pixmap(m_connection, m_pix);

  if (graphics) {
    xcb_free_gc(connection, graphics);
    graphics = 0;
  }

  if (window) {
    xcb_destroy_window(connection, window);
    window = 0;
  }

  if (xdisplay) {
    XCloseDisplay(xdisplay);
    xdisplay = nullptr;
  }


  xcb_disconnect(m_connection);
}
/**
 *
 * @internal
 * @fn fn_open_window

 */
void uxdevice::os_xcb_linux_t::fn_open_window(void) {
  /// @brief if the items have already been initialized by another logic path,
  /// use the ones provided.
  if (xdisplay && connection && graphics)
    return;

  if (!xdisplay = XOpenDisplay(nullptr))
    throw_error_report(__FILE__, const std::size_t ln, __func__,
                       "XOpenDisplay returned null.");

  /* get the connection to the X server */
  if (!connection = XGetXCBConnection(xdisplay))
    throw_error_report(__FILE__, const std::size_t ln, __func__,
                       "XGetXCBConnection returned null.");

  /* Get the first screen */
  screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;
  if (!screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data)
    throw_error_report(__FILE__, const std::size_t ln, __func__,
                       "xcb_setup_roots_iterator returned null.");

  /* Create black (foreground) graphic context */
  window = screen->root;
  graphics = xcb_generate_id(connection);
  uint32_t mask = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
  uint32_t values[] = {screen->black_pixel, 0};
  xcb_create_gc(connection, graphics, window, mask, values);

  if (!graphics)
    throw_error_report(__FILE__, const std::size_t ln, __func__,
                       "xcb_create_gc returned null.");

  /// @brief set the base window manager's settings.
  screen_width = screen->width_in_pixels;
  screen_height = screen->height_in_pixels;

  /* Create a window */
  window = xcb_generate_id(connection);
  mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
  mask = XCB_CW_OVERRIDE_REDIRECT | XCB_CW_EVENT_MASK;
  mask = XCB_CW_BORDER_PIXEL | XCB_CW_BIT_GRAVITY | XCB_CW_OVERRIDE_REDIRECT |
         XCB_CW_SAVE_UNDER | XCB_CW_EVENT_MASK;

  uint32_t vals[] = {
      screen->black_pixel, XCB_GRAVITY_NORTH_WEST, 0, 1,
      XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS |
          XCB_EVENT_MASK_KEY_RELEASE | XCB_EVENT_MASK_POINTER_MOTION |
          XCB_EVENT_MASK_BUTTON_MOTION | XCB_EVENT_MASK_BUTTON_PRESS |
          XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_STRUCTURE_NOTIFY};

  xcb_create_window(connection, XCB_COPY_FROM_PARENT, window, screen->root,
                    static_cast<unsigned short>(window_x),
                    static_cast<unsigned short>(window_y), ,
                    static_cast<unsigned short>(window_width),
                    static_cast<unsigned short>(window_height), 0,
                    XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual, mask,
                    vals);

  if (!window)
    throw_error_report(__FILE__, const std::size_t ln, __func__,
                       "XOpenDisplay returned null.");

  /* Map the window on the screen.*/
  xcb_map_window(connection, window);

  // setup close window event
  cookie = xcb_intern_atom(connection, 1, 12, "WM_PROTOCOLS");
  reply = xcb_intern_atom_reply(connection, cookie, 0);

  cookie2 = xcb_intern_atom(connection, 0, 16, "WM_DELETE_WINDOW");
  reply2 = xcb_intern_atom_reply(connection, cookie2, 0);

  xcb_change_property(connection, XCB_PROP_MODE_REPLACE, window, (*reply).atom,
                      4, 32, 1, &(*reply2).atom);

}


/**
 * @fn void flush(void)
 * @brief completes cairo surface and flushes the xcb connection
 *
 */
void uxdevice::os_xcb_linux_t::fn_flush_window(void) {
  if (connection)
    xcb_flush(connection);
}

/**
 * @internal
 * @fn wait_message(void)
 * @brief waits for an event. The system will no return until a message has been
 * received.
 * @return xcb_generic_event_t *
 *
 */
xcb_generic_event_t *uxdevice::os_xcb_linux_t::fn_wait_message(void) {
  return xcb_wait_for_event(connection);
}

/**
 * @internal
 * @fn poll_message(void)
 * @brief polls for an event. retrusn null when non exists. this gives the
 * opportunity to process a batch of them. Starting with a wait, and then
 * calling this function until there are no more.
 * @return xcb_generic_event_t *
 *
 */
xcb_generic_event_t *uxdevice::os_xcb_linux_t::fn_poll_message(void) {
  return xcb_poll_for_queued_event(connection);
}

/**
 * @internal
 * @fn complete_message(xcb_generic_event_t *xcb)
 * @brief frees the event
 * @return void
 */
voiduxdevice::os_xcb_linux_t::fn_complete_message(xcb_generic_event_t *xcb) {
  free(xcb);
}

/**
 * @internal
 * @var message_dispatch_t
 * @brief translates between system domain.
 * generic_os_event_queue_message_t is defined in compile options as it is
 * associated with os compile target. It is defined as a static so only one
 * exists in all versions of the window object.
 */
void uxdevice::os_xcb_linux_t::fn_visit_dispatch(xcb_generic_event_t *xcb) {
  static const message_dispatch_t message_dispatch = {
      {XCB_KEY_PRESS,
       [&]() { dispatch<keyboard_device_xcb_t, key_press_xcb_t>(xcb); }},

      {XCB_KEY_RELEASE,
       [&]() { dispatch<keyboard_device_xcb_t, key_release_xcb_t>(xcb); }},

      {XCB_BUTTON_PRESS,
       [&]() { dispatch<mouse_device_xcb_t, button_press_xcb_t>(xcb); }},

      {XCB_BUTTON_RELEASE,
       [&]() { dispatch<mouse_device_xcb_t, button_release_xcb_t>(xcb); }},

      {XCB_MOTION_NOTIFY,
       [&]() { dispatch<mouse_device_xcb_t, motion_notify_xcb_t>(xcb); }},

      {XCB_EXPOSE,
       [&]() { dispatch<window_service_xcb_t, surface_expose_xcb_t>(xcb); }},

      {XCB_CONFIGURE_NOTIFY,
       [&]() { dispatch<window_service_xcb_t, configure_notify_xcb_t>(xcb); }},

      {XCB_CLIENT_MESSAGE,
       [&]() { dispatch<window_service_xcb_t, client_message_xcb_t>(xcb); }}

  };

  /** @brief process, depending upon filter, non handled messages may be
   * faster with a bit range check. this can be enhanced with specific
   * numerical representation. xcb internals possibly. The it->second()
   * invocation performs a dispatch using the std::visit function. */
  auto it = message_dispatch.find(xcb->response_type & ~0x80);
  if (it != message_dispatch.end())
    it->second();
}

/**
 *
 */
void uxdevice::os_xcb_linux_t::fn_set_window_title(void) {
  // set window title
  xcb_change_property(connection, XCB_PROP_MODE_REPLACE, window,
                      XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8, title.size(),
                      title.data());
}


// clang-format on

/**
 * @internal
 * @fn mouse_device_xcb_t
 * @details handles the mouse device visits. The lambda functions below are
 * called based upon the visit for the variant. The variant is defined in
 * the class definition on the event_base_t template parameters. There must
 * be one entry here for each type mention within the parameters as well as
 * handling std::monostate which the base class inserts by default.
 * @returns mouse_device_xcb_t *
 */
uxdevice::mouse_device_xcb_t *uxdevice::mouse_device_xcb_get(void) {

  static const overload_visitors_t visit_map = overload_visitors_t{

      /**
       * @internal
       * @brief handles mouse move events.
       * @param motion_notify_xcb_t xcb
       */
       switch(xcb) {}
      case motion_notify_xcb_t xcb) {
        x = xcb->event_x;
        y = xcb->event_y;
        alias = std::type_index{typeid(listen_mousemove_t)};
      },

      /**
       * @internal
       * @brief handles mouse button press. this also includes wheel for linux
       * which is 4 & 5 index.
       * @param button_press_xcb_t xcb
       */
      [&](button_press_xcb_t xcb) {
        // pluck relative items from the xcb event and place into
        // interface.
        x = xcb->event_x;
        y = xcb->event_y;

        /** @brief interpret these values as up and down wheel.*/
        if (xcb->detail == XCB_BUTTON_INDEX_4 ||
            xcb->detail == XCB_BUTTON_INDEX_5) {
          d = xcb->detail == XCB_BUTTON_INDEX_4 ? 1 : -1;
          alias = std::type_index{typeid(listen_wheel_t)};
        } else {
          d = xcb->detail;
          alias = std::type_index{typeid(listen_mousedown_t)};
        }
      },

      /**
       * @internal
       * @brief handles mouse button release
       * @param button_release_xcb_t xcb
       */
      [&](button_release_xcb_t xcb) {
        // ignore button 4 and 5 which are wheel events.
        if (xcb->detail != XCB_BUTTON_INDEX_4 &&
            xcb->detail != XCB_BUTTON_INDEX_5)
          alias = std::type_index{typeid(listen_mouseup_t)};
        else
          alias = std::type_index{typeid(mouse_device_xcb_t)};
      },
      [&](std::monostate) { alias = std::type_index{typeid(std::monostate)}; }};

  std::visit(visit_map, data);
  return this;
}



/**
 * @var window_service_event_t::visit_map
 * @brief window services such as resize, move, and expose.
 */
uxdevice::window_service_xcb_t *uxdevice::window_service_xcb_t::get(void) {
  static const overload_visitors_t visit_map = overload_visitors_t{

      /**
       * @internal
       * @brief handles expose events which are translated into paint
       * @param surface_expose_xcb_t xcb
       */
      [&](surface_expose_xcb_t xcb) {
        x = xcb->x;
        y = xcb->y;
        w = xcb->width;
        h = xcb->height;
        alias = std::type_index{typeid(listen_paint_t)};
      },

      /**
       * @internal
       * @brief handles resize event
       * @param configure_notify_xcb_t xcb
       */
      [&](configure_notify_xcb_t xcb) {
        if (xcb->window == window_manager->window &&
            ((short)xcb->width != window_manager->window_width ||
             (short)xcb->height != window_manager->window_height)) {
          w = xcb->width;
          h = xcb->height;

          bvideo_output = true;
          alias = std::type_index{typeid(listen_resize_t)};
        }
      },

      /**
       * @internal
       * @brief handles client message such as close window.
       * @param client_message_xcb_t xcb
       */
      [&](client_message_xcb_t xcb) {
        // filter subset for this... original from stack over flow
        if (xcb->data.data32[0] == window_manager->reply2->atom) {
          alias = std::type_index{typeid(listen_close_window_t)};
        }
      },
      [&](std::monostate) { alias = std::type_index{typeid(std::monostate)}; }};

  std::visit(visit_map, data);

  return this;
}


/**
 * @fn  keyboard_device_event_t()
 * @brief constructor implementation
 *
 */
uxdevice::keyboard_device_xcb_t::keyboard_device_xcb_t()
    : keyboard_device_base_t() 
  syms = xcb_key_symbols_alloc(window_manager->connection);
  if (!syms) {
    std::stringstream sError;
    sError << "xcb_key_symbols_alloc "
           << "  " << __FILE__ << " " << __func__;
    throw std::runtime_error(sError.str());
  }
}

/**
 * @fn  ~keyboard_device_event_t()
 * @brief
 *
 */
uxdevice::keyboard_device_xcb_t::~keyboard_device_xcb_t() {
  if (syms) {
    xcb_key_symbols_free(syms);
    syms = nullptr;
  }
}

/**
 * @fn uxdevice::event_t get(void)
 * @brief
 *
 * @return
 */
uxdevice::keyboard_device_xcb_t *uxdevice::keyboard_device_xcb_t::get(void) {

      /**
       * @internal
       * @brief handles keypress event
       * @param xcb_configure_notify_event_t *xcb
       */
      switch(xcb) {
        case key_press_xcb_t: {
        // get key symbol
        sym = xcb_key_press_lookup_keysym(syms, xcb.get(), 0);

        // in range of keys?
        if (sym < 0x99) {

          // use xwindows to lookup the string
          XKeyEvent keyEvent;
          keyEvent.display = window_manager->xdisplay;
          keyEvent.keycode = xcb->detail;
          keyEvent.state = xcb->state;
          keyEvent.root = xcb->root;
          keyEvent.time = xcb->time;
          keyEvent.window = xcb->event;
          keyEvent.serial = xcb->sequence;

          // filter as a keypress event
          if (XLookupString(&keyEvent, c.data(), c.size(), nullptr, nullptr)) {
            alias = std::type_index{typeid(listen_keypress_t)};
          } else {
            // send a keydown event
            alias = std::type_index{typeid(listen_keydown_t)};
          }
        }
      }
      break;

      /**
       * @internal
       * @brief handles key release event
       * @param xcb_configure_notify_event_t *xcb
       */
      case key_release_xcb_t: {
        sym = xcb_key_press_lookup_keysym(syms, xcb.get(), 0);
        alias = std::type_index{typeid(listen_keyup_t)};
      }
      break;

      default:
        sym = {};
        alias = std::type_index{typeid(std::monostate)};
      break;

      }
  return this;
}







/**
\internal
\brief the function clears the dirty rectangles of the off screen buffer.
*/
void viewManager::Visualizer::platform::clear(void) {
  fill(m_offscreenBuffer.begin(), m_offscreenBuffer.end(), 0xFF);
  m_xpos = 0;
  m_ypos = 0;
}

/**
\brief The function places a color into the offscreen pixel buffer.
    Coordinate start at 0,0, upper left.
\param x - the left point of the pixel
\param y - the top point of the pixel
\param unsigned int color - the bgra color value

*/
void viewManager::Visualizer::platform::putPixel(const int x, const int y,
                                                 const unsigned int color) {
  if (x < 0 || y < 0)
    return;

  // clip coordinates
  if (x >= _w || y >= _h)
    return;

  // calculate offset
  unsigned int offset = x * 4 + y * 4 * _w;

  // put rgba color
  unsigned int *p =
      reinterpret_cast<unsigned int *>(&m_offscreenBuffer[offset]);
  *p = color;
}

/**
\brief The function returns the color at the pixel space. Coordinate start
at 0,0, upper left. \param x - the left point of the pixel \param y - the
top point of the pixel \param unsigned int color - the bgra color value

*/
unsigned int viewManager::Visualizer::platform::getPixel(const int x,
                                                         const int y) {
  // clip coordinates
  if (x < 0 || y < 0)
    return 0;

  if (x >= _w || y >= _h)
    return 0;

  // calculate offset
  unsigned int offset = x * 4 + y * 4 * _w;

  // put rgba color
  unsigned int *p =
      reinterpret_cast<unsigned int *>(&m_offscreenBuffer[offset]);
  return *p;
}

/**
\brief The function provides the reallocation of the offscreen buffer

*/
void viewManager::Visualizer::platform::resize(const int w, const int h) {

  _w = w;
  _h = h;


  // free old one if it exists
  if (m_pix) {
    xcb_shm_detach(m_connection, m_info.shmseg);
    shmdt(m_info.shmaddr);

    xcb_free_pixmap(m_connection, m_pix);
  }

  // Shared memory test.
  // https://stackoverflow.com/questions/27745131/how-to-use-shm-pixmap-with-xcb?noredirect=1&lq=1
  xcb_shm_query_version_reply_t *reply;

  reply = xcb_shm_query_version_reply(
      m_connection, xcb_shm_query_version(m_connection), NULL);

  if (!reply || !reply->shared_pixmaps) {
    cout << "Could not get a shared memory image." << endl;
    exit(0);
  }

  m_info.shmid = shmget(IPC_PRIVATE, _w * _h * 4, IPC_CREAT | 0777);
  m_info.shmaddr = (uint8_t *)shmat(m_info.shmid, 0, 0);

  m_info.shmseg = xcb_generate_id(m_connection);
  xcb_shm_attach(m_connection, m_info.shmseg, m_info.shmid, 0);
  shmctl(m_info.shmid, IPC_RMID, 0);

  m_screenMemoryBuffer = static_cast<uint8_t *>(m_info.shmaddr);

  m_pix = xcb_generate_id(m_connection);
  xcb_shm_create_pixmap(m_connection, m_pix, m_window, _w, _h,
                        m_screen->root_depth, m_info.shmseg, 0);

  int _bufferSize = _w * _h * 4;

  if (m_offscreenBuffer.size() < _bufferSize)
    m_offscreenBuffer.resize(_bufferSize);

  // clear to white
  clear();

}

bool viewManager::Visualizer::platform::filled() { return m_ypos > _h; }

/**
\brief The function copies the pixel buffer to the screen

*/
void viewManager::Visualizer::platform::flip() {
  // copy offscreen data to the shared memory video buffer
  memcpy(m_screenMemoryBuffer, m_offscreenBuffer.data(),
         m_offscreenBuffer.size());

  // blit the shared memory buffer
  xcb_copy_area(m_connection, m_pix, m_window, m_graphics, 0, 0, 0, 0, _w, _h);

  xcb_flush(m_connection);


}

