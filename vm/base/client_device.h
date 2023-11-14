#pragma once

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
 * @file ux_device.hpp
 * @date 9/7/20
 * @version 1.0
 * @brief interface for the platform.
 */

/**
 * @namespace uxdevice
 * @brief The major invocation of API object usage is defined here.
 * surface_area_t and its constructors are here. The class provides the stream
 * operations for the system to provide an input mechanism. These are template
 * functions. Object composition and discrete initializations of the object is
 * accomplished here as well.
 *
 * Do not let clang format change the order of includes as order of dependency
 * is established in this serialized list that each of the modules includes. The
 * namespace uxdevice is used.
 *
 * The list of includes below is the major build order for the object class
 * definitions.
 */

namespace uxdevice {

class event;

class bounds {
public:
  double x = 0, y = 0, w = 0, h = 0;
};

class point {
public:
  double x = 0, y = 0;
};

/**
 * @internal
 * @def UX_DECLARE_STREAM_INTERFACE
 * @brief the macro creates the stream interface for both constant references
 * and shared pointers as well as establishes the prototype for the insertion
 * function. The implementation is not standard and will need definition. This
 * is the route for formatting objects that accept numerical data and process to
 * human readable values. Modern implementations include the processing of size
 * information. Yet within the c++ implementation, the data structures that
 * report and hold information is elaborate.
 */

#define UX_DECLARE_STREAM_INTERFACE(CLASS_NAME)                                \
public:                                                                        \
  template <typename T> surface_area_t &operator<<(const CLASS_NAME &data) {   \
    stream_input(data);                                                        \
    return *this;                                                              \
  }                                                                            \
  template <typename T>                                                        \
  surface_area_t &operator<<(const std::shared_ptr<CLASS_NAME> data) {         \
    stream_input(data);                                                        \
    return *this;                                                              \
  }                                                                            \
                                                                               \
private:                                                                       \
  surface_area_t &stream_input(const CLASS_NAME &_val);                        \
  surface_area_t &stream_input(const std::shared_ptr<CLASS_NAME> _val);

/**
 * @class surface_area_t
 * @brief The main interface object of the system.
 */
class surface_area_t  {
public:
  surface_area_t();

  /**
   * @fn surface_area_t
   * @brief template constructor providing variable number of arguments. This
   * provides the expansion of the open window interface to accept typed
   * parameters that are set to the window manager.
   */
  template <typename... Args> surface_area_t(Args... args) {
    window_manager = linked_window_manager_t();
    window_manager->set(args...);

    window_manager->open_window();

    set_surface_defaults();
  }

  ~surface_area_t();

  // copy constructor
  surface_area_t(const surface_area_t &other);

  // move constructor
  surface_area_t(surface_area_t &&other) noexcept;

  // copy assignment operator
  surface_area_t &operator=(const surface_area_t &other);

  // move assignment operator
  surface_area_t &operator=(surface_area_t &&other) noexcept;

  /**
   * @fn operator<<
   * @tparam T
   * @brief This overload accepts const data and not shared pointers. If the
   * object is of a type such as listener or a display unit, a shared pointer
   * is created and is owned by the system. Using the operator<< member
   * function within this context allows for one function to handle the object
   * layers. Adding new layers to the object will not affect two routines in
   * the update.
   *
   * Otherwise the information is shipped to a ostreamstream for stream
   * insertion formatting. This is a good place to provide functions
   * formatting c standard library and raw formats such as int, float.
   *
   */
  template <typename T> surface_area_t &operator<<(const T &data) {

    // display units and event listeners are intercepted here.
    if constexpr (std::is_base_of<display_node_t, T>::value ||
                  std::is_base_of<listener_t<T>, T>::value) {
      T obj = display_list<T>(data);
      operator<<(obj);

      // otherwise the input is another type. Try
      // the default string stream.
    } else {
      std::ostringstream s;
      s << data;
      std::string sData = s.str();
      stream_input(sData);
    }

    return *this;
  }


  /**
   * Declare interface only.  uxdevice.cpp contains implementation. These are
   * the stream interface with a function prototype for the invoke(). The
   * uxdevice.cpp file contains the implementation.  surface_area_t
   * &uxdevice::surface_area_t::stream_input( const CLASS_NAME _val) is the
   * prototype developed.
   */

  UX_DECLARE_STREAM_INTERFACE(std::string)
  UX_DECLARE_STREAM_INTERFACE(std::stringstream)
  UX_DECLARE_STREAM_INTERFACE(std::string_view)

  /** declares the interface and implementation for these objects when these
   * are invoked, the pipeline_memory class is also updated. When rendering
   * objects are created, text, image or other, these these shared pointers
   * are used as a reference local member initialized at invoke() public
   * member. The parameters and options are validated as well. */

  /**
   * @fn in
   * @tparam T - object to insert using the stream operator.
   * @tparam Args - list of them, param pack expansion calls recursively to
   * operator.
   * @brief An alternative input function to stream syntax.
   *  e.g. vis.in(text_font_t{"Arial 20px"}, coordindate_t{0,0}, "Hello");
   */
public:
  // template <typename T> void in(const T &&obj) { operator<<(obj); }
  template <typename T> void in(const T &obj) { operator<<(obj); }

  template <typename T, typename... Args>
  void in(const T &obj, const Args &... args) {
    operator<<(obj);
    in(args...);
  }

  std::string &operator[](std::string _val) noexcept;

  bool processing(void) { return bProcessing; };

  void clear(void);
  void notify_complete(void);
 
}; // namespace uxdevice

} // namespace uxdevice
