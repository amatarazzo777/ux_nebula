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
#include "os_interface.h"

// clang-format on

using namespace std;
using namespace viewManager;

/**
 * @fn uxdevice::os_xcb_linux_t operator =&(const os_xcb_linux_t&)
 * @brief copy assignment operator
 *
 * @param other
 * @return
 */
viewManager::os_xcb_linux_t &
viewManager::os_xcb_linux_t::operator=(const os_xcb_linux_t &other) {
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
viewManager::os_xcb_linux_t &
viewManager::os_xcb_linux_t::operator=(os_xcb_linux_t &&other) noexcept {
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
 * @fn  keyboard_device_event_t()
 * @brief constructor implementation
 *
 */
void viewManager::os_xcb_linux_t::fn_initialize(void)
    : keyboard_device_base_t() syms =
          xcb_key_symbols_alloc(window_manager -> connection);
if (!syms) {
  std::stringstream sError;
  sError << "xcb_key_symbols_alloc " << "  " << __FILE__ << " " << __func__;
  throw std::runtime_error(sError.str());
}
}

/**
 * @fn  ~keyboard_device_event_t()
 * @brief
 *
 */
void viewManager::os_xcb_linux_t::terminate(void) {
  if (syms) {
    xcb_key_symbols_free(syms);
    syms = nullptr;
  }
}

/**
 *
 * @internal
 * @fn fn_open_window

 */
void viewManager::os_xcb_linux_t::fn_open_window(void) {
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

void viewManager::os_xcb_linux_t::fn_close_window(void) {
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
 * @fn void flush(void)
 * @brief completes cairo surface and flushes the xcb connection
 *
 */
void viewManager::os_xcb_linux_t::fn_flush_window(void) {
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
xcb_generic_event_t *viewManager::os_xcb_linux_t::fn_wait_message(void) {
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
xcb_generic_event_t *viewManager::os_xcb_linux_t::fn_poll_message(void) {
  return xcb_poll_for_queued_event(connection);
}

/**
 * @internal
 * @fn complete_message(xcb_generic_event_t *xcb)
 * @brief frees the event
 * @return void
 */
void VM::os_xcb_linux_t::fn_complete_message(xcb_generic_event_t *xcb) {
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
void viewManager::os_xcb_linux_t::fn_visit_dispatch(os_message_t xcb) {

  /**
   * @internal
   * @brief handles mouse move events.
   * @param motion_notify_xcb_t xcb
   */
   event_t e;
  switch (xcb->response_type & ~0x80) {
  case XCB_KEY_PRESS: {
    // get key symbol
    e.sym = xcb_key_press_lookup_keysym(syms, xcb, 0);

    // in range of keys?
    if (e.sym < 0x99) {

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
        e.alias = std::type_index{typeid(listen_keypress_t)};
      } else {
        // send a keydown event
        e.alias = std::type_index{typeid(listen_keydown_t)};
      }
    }
  } break;

  /**
   * @internal
   * @brief handles key release event
   * @param xcb_configure_notify_event_t *xcb
   */
  case XCB_KEY_RELEASE: {
    e.sym = xcb_key_press_lookup_keysym(syms, xcb, 0);
    e.alias = std::type_index{typeid(listen_keyup_t)};
  } break;

  case XCB_MOTION_NOTIFY: {
    e.x = xcb->event_x;
    e.y = xcb->event_y;
    e.alias = std::type_index{typeid(listen_mousemove_t)};
  } break;

  /**
   * @internal
   * @brief handles mouse button press. this also includes wheel for linux
   * which is 4 & 5 index.
   * @param button_press_xcb_t xcb
   */
  case XCB_BUTTON_PRESS:
    // pluck relative items from the xcb event and place into
    // interface.
    e.x = xcb->event_x;
    e.y = xcb->event_y;

    /** @brief interpret these values as up and down wheel.*/
    if (xcb->detail == XCB_BUTTON_INDEX_4 ||
        xcb->detail == XCB_BUTTON_INDEX_5) {
      e.d = xcb->detail == XCB_BUTTON_INDEX_4 ? 1 : -1;
      e.alias = std::type_index{typeid(listen_wheel_t)};
    } else {
      e.d = xcb->detail;
      e.alias = std::type_index{typeid(listen_mousedown_t)};
    }
  }
  break;

/**
 * @internal
 * @brief handles mouse button release
 * @param button_release_xcb_t xcb
 */
case XCB_BUTTON_RELEASE: {
  // ignore button 4 and 5 which are wheel events.
  if (xcb->detail != XCB_BUTTON_INDEX_4 && xcb->detail != XCB_BUTTON_INDEX_5)
    e.ti = std::type_index{typeid(listen_mouseup_t)};
  else
    e.alias = std::type_index{typeid(mouse_device_xcb_t)};
} break;

/**
 * @internal
 * @brief handles expose events which are translated into paint
 * @param surface_expose_xcb_t xcb
 */
case XCB_EXPOSE: {
  e.x = xcb->x;
  e.y = xcb->y;
  e.w = xcb->width;
  e.h = xcb->height;
  e.alias = std::type_index{typeid(listen_paint_t)};
} break;

/**
 * @internal
 * @brief handles resize event
 * @param configure_notify_xcb_t xcb
 */
case XCB_CONFIGURE_NOTIFY: {
  if (xcb->window == window_manager->window &&
      ((short)xcb->width != window_manager->window_width ||
       (short)xcb->height != window_manager->window_height)) {
    e.w = xcb->width;
    e.h = xcb->height;

    bvideo_output = true;
    e.alias = std::type_index{typeid(listen_resize_t)};
  }
} break;

/**
 * @internal
 * @brief handles client message such as close window.
 * @param client_message_xcb_t xcb
 */
case XCB_CLIENT_MESSAGE: {
  // filter subset for this... original from stack over flow
  if (xcb->data.data32[0] == window_manager->reply2->atom) {
    e.alias = std::type_index{typeid(listen_close_window_t)};
  }
} break;
}
}

/**
 *
 */
void viewManager::os_xcb_linux_t::fn_set_window_title(void) {
  // set window title
  xcb_change_property(connection, XCB_PROP_MODE_REPLACE, window,
                      XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8, title.size(),
                      title.data());
}

// clang-format on

/**
\internal
\brief the function clears the dirty rectangles of the off screen buffer.
*/
void VM::os_xcb_linux_t::clear(void) {
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
void VM::os_xcb_linux_t::putPixel(const int x, const int y,
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
unsigned int VM::os_xcb_linux_t::getPixel(const int x, const int y) {
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
void VM::os_xcb_linux_t::resize(const int _w, const int _h) {

  w = _w;
  h = _h;

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

/**
\brief The function copies the pixel buffer to the screen

*/
void VM::os_xcb_linux_t::fn_flip() {
  // copy offscreen data to the shared memory video buffer
  memcpy(m_screenMemoryBuffer, m_offscreenBuffer.data(),
         m_offscreenBuffer.size());

  // blit the shared memory buffer
  xcb_copy_area(m_connection, m_pix, m_window, m_graphics, 0, 0, 0, 0, _w, _h);

  xcb_flush(m_connection);
}

VM::os_xcb_linux_t::fn_library_open(std::string &_library_name) {

  // build correct path from os indenpendant name. (.so vs .dl). This would also
  // be a place to add current path and a software search path.
  library_name = _library_name;
  library_filename = "./" + sym + ".so";
  dl_handle = dlopen(library_filename.data(), RTLD_LAZY);

  if (!dl_handle) {
    std::stringstream serror;
    serror << "Cannot load library: " << dlerror() << "  " << library_name
           << " given, searched for  " << library_filename;
    error_message = serror.str();
    return;
  }
}

/**
 * @internal
 * @fn library_close
 * @brief The function issues the dlopen and stores the handle in dl_ptr.
 *
 */
VM::os_xcb_linux_t::fn_library_close(std::string &_library_name) {

  if (dl_handle)
    if (dlclose(dl_handle)) {
      std::stringstream serror;
      serror << "Error close library: " << dlerror() << "  " << library_name
             << " given, searched for  " << library_filename;
      error_message = serror.str();
    }

  // clear it.
  dl_handle = nullptr;
}

/**
 * @internal
 * @fn library_symbol
 * @brief loads a symbol, low level pointer void * used with bind.
 *
 */
void *VM::os_xcb_linux_t::library_symbol(std::string &symbol) {
  void *ptr_sym = {};

  if (dl_handle) {
    ptr_sym = dlsym(dl_handle, symbol.data());

    const char *dlsym_error = dlerror();
    if (dlsym_error) {
      std::stringstream serror;
      serror << "Cannot load library: " << dlsym_error << "  " << symbol
             << " given, searched for  " << sfilename;
      error_message = serror.str();
    }
  }

  return ptr_sym;
}
