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
 * manager functions. THe message queue processor is defined and implemented
 * here..
 */

#pragma once

#include <sys/ipc.h>
#include <sys/shm.h>

/// @brief could separpate into categoriy by implement, yet this is simple to
/// maintain for the xcb or any platform.

#include <X11/Xlib-xcb.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>

#include <sys/types.h>
#include <xcb/xcb_keysyms.h>

namespace uxdevice {
/// @brief forward template class allows the os message and platform to be
/// resolved early within the build process.

/**
 * @typedef os_message_t
 * @brief this is used to generalize parts of the code here and else where. The
 * typedef should be defined.
 *
 */

typedef xcb_generic_event_t *os_message_t;


/**
 * @internal
 * @class os_xcb_linux_t
 * @brief The class provides the necessary implementation details according to
 * the window_manager_base_t class. The window_manager_t base class provides
 * functions that are used by the rest of the system. THe message queue and a
 * threaded dispatcher is provided by the base. The mutex operation of the
 * surface and drawing functions are handled. This class must implement the
 * function attach_surface().
 */

class os_xcb_linux_t : generic_os_interface_t {
public:
  using generic_os_interface_t::generic_os_interface_t;

  os_xcb_linux_t();
  virtual ~os_xcb_linux_t();

  /// @brief move, assignment constructors, operators implementation
  os_xcb_linux_t(const os_xcb_linux_t &other);
  os_xcb_linux_t(os_xcb_linux_t &&other) noexcept;
  os_xcb_linux_t &operator=(const os_xcb_linux_t &other);
  os_xcb_linux_t &operator=(os_xcb_linux_t &&other) noexcept;

  /// @brief os specific implementation functions.
  void fn_open_window(void);
  void fn_close_window(void);
  void fn_flush_window(void);

  /// @brief the base window manager has a threaded event queue and a variant
  /// visit interface. These functions are called by this logic. The odd ball,
  /// fn_complete_message is a free(). This routine is called when the system
  /// completes processing of the message.
  xcb_generic_event_t *fn_wait_message(void);
  xcb_generic_event_t *fn_poll_message(void);
  void fn_complete_message(xcb_generic_event_t *);

  /// @brief the composition of the event and its logic causing invocation of
  /// event listeners attached.
  void fn_visit_dispatch(xcb_generic_event_t *e);

  /// @brief window attributes
  void fn_set_title(const std::string &s);


  /* load library functions. A very powerful set of functions that can be used to expand, or
   reduce code compilation complexity. Yet internal knowlegde of the interfaces and componets
   leads to a version magnification. The long description, some formal object notations, boxing types,
   leads to expansion. Creating a compressed logical stream of parameter formatting to these routines
   with logic allows the user to experience native application drawing. 
   
   Yet the formal usage of this system is to show how complexity of system api design can be transgressed
   into a better form with better structure. Information Archecture is the field of distinct and named
   field of noun title placement at a heirarchial level.  Linux offers capabilities, and also does the MS platform.
   A new overcoat to the kernel as a linux concept to apply from the commandline, loading of a desktop unit 
   and windowing system with enhanced font rendering from the command line without X, XCB but utilizing the 
   linux driver model, system requests, DRM? The system of IPC, currently DBUS.

Connecting the systems together with an easy syntax light language that is designed for an audience. Business
audicences may be component oriented, documentation and plain text labels the desktop experience. Modern computer 
language concepts are very easy to read. minimizing the code definition and complexity and tailoring runtime
output with JIT magnifies reduction in development time. Cobol was a language defined that gave new insite to
a fortitude of business systems. With its intrensic ISAM (database index) file format, record keeping was a numerical 
concept. So to effectively design a language that is for the desktop experience, is a new concept to understand.
A visual layout of interaction of user interaction, designed controls, simplification, window system, etc. As a 
select language can be tailored for great competition. 

Using the color, brush, vector programming object pattern provides natural definition of great texture capabilities. 
Simply the outline, or vector system of ploted interface points, with structure annotations in object form, can summarize 
interface creation from an engine point of view. The system of scrolling, buffer manulipation can be managed 
using c++ algorithms. As a build system, the output of this compatible layer structure for desktop and application models
can be versitile. That is, as a server compilation model, desktops are native compiled for the video card to supply
the desktop experience.


  Codec license of various image file formats are often applied in modern day to video, audio, books. To expound upon
  these natures at the booting time, this code may be handled elsewhere. The input video alignment of the internal buffer
  is easy for driver plotting. Designing the communication portal from the input devices to internal queues for event 
  handling. Without the xcb interface, many forgotten functions are forgotten about. Pixel format conversion from an
  image source. To simplify design the VM system utilizes the most current hardware, forgetting about legacy.
  All modern modern micro processors have a quality of video buffer color align at a 24 bit color scale. Or the 
  computer supports a maximum resolution and color depth. The code must compile at this native depth and provide color 
  buffer support at the native level. Simply this is a format, size of data, order of data. Older computers designed with 
  16 colors such as the EGA are not needing support. 

  Knowing the physical size and DPI of the screen is also necessary. Providing the windowing system to be built in.

  Supporting multiple monitors for HDMI creates some newer designs where multiple desktops, or video off screen 
  buffers have to exist and be utilized.

  Finally from this point of view, capabilities of the video card that are three dimensional can be designed to integrate
  with native driver interface video protocols. Before NVIDIA, there was glfx. 

    */

  void fn_library_open();

private:
  Display *xdisplay = {};
  xcb_connection_t *connection = {};
  xcb_screen_t *screen = {};
  xcb_drawable_t window = {};
  xcb_gcontext_t graphics = {};
  xcb_visualtype_t *visual_type = {};

  /// @brief wm_close message enable
  xcb_intern_atom_cookie_t cookie = {};
  xcb_intern_atom_reply_t *reply = {};
  xcb_intern_atom_cookie_t cookie2 = {};
  xcb_intern_atom_reply_t *reply2 = {};

};

/// @brief type alias to generalize other parts of the code if necessary.
using os_window_manager_t = os_xcb_linux_t;

} // namespace uxdevice
