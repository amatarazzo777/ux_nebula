/*
 * This file is part of the ux_nebula distribution
 * (https://github.com/amatarazzo777/ux_nebula).
 * Copyright (c) 2023 Anthony Matarazzo.
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
\author Anthony Matarazzo
\file viewManager.hpp
\date 11/19/19
\version 1.0
\brief Header file that implements the document object model interface.
The attributes, Element base class, and document entities are defined within
the file. The enumeration values for object options as well as the event class
are defined here. Within this file, several preprocessor macros exist that
simplify and document the code base. Based upon the environment of the compiler,
several platform specific header files are included. However all of the
platform OS code is only coded within the platform object. The system exists
within the viewManager namespace.
*/
#pragma once

/**
\addtogroup Library Build Options
\brief Library Options
\details These options provide the selection to configure selection
options when compiling the source.
@{
*/
/**
\def DEFAULT_WINDOW_TITLE
\brief when a window title is not provided, this is used.

*/
#include "std_base.h"

#define DEFAULT_WINDOW_TITLE                                                   \
  std::string(__FILE__) + std::string("  ") + std::string(__DATE__)

/**
\def SYSTEM_DEFAULTS
\brief sets the defaults for each window created.

*/
#define SYSTEM_DEFAULTS                                                        \
  in(absolute_coordinate_t(), text_render_normal_t{},                          \
     text_font_t{"Arial 20px"}, text_color_t{"black"},                         \
     surface_area_brush_t{"white"}, text_indent_t{100.0},                      \
     text_alignment_t{text_alignment_options_t::left},                         \
     text_ellipsize_t{text_ellipsize_options_t::off}, text_line_space_t{1.0},  \
     text_tab_stops_t{                                                         \
         std::vector<double>{250, 250, 250, 250, 250, 250, 250, 250}},         \
     surface_area_title_t{DEFAULT_WINDOW_TITLE});

#if defined(__linux__)
#include "../os/linux_xcb/os_interface.h"
#endif

/**
\namespace viewManager

\brief The viewManager namespace is the top level name where all of the
API exists.

*/
namespace viewManager {
// forward declaration
class Element;
class StyleClass;
class event;

/// \typedef ElementQuery typedef is used to specify the parameter to the
/// query function when a lambda is provided.
typedef std::function<bool(const Element &)> ElementQuery;

/// \typedef ElementList is used to provide vector based parameters to the
/// base API The caller should create their vectors using this typedef. The
/// return values from all of the API work correctly in that the push_back
/// method is used to add to the list.
typedef std::vector<std::reference_wrapper<Element>> ElementList;

/**
  \brief the dataTransformMap provides a translation between a storage type
and the transform function used to generate elements for the underlying data.

  \tparam std::size_t I - a numeric literal
  \tparam T - the element type
*/
template <std::size_t I, typename T>
using dataTransformMap =
    std::unordered_map<const typename std::tuple_element<I, T>::type &,
                       std::function<Element &(T &)>>;
/**
\internal
\brief Contains all elements allocated using the system api. They are
contained here as smart pointers and are automatically memory managed.
*/
extern std::unordered_map<std::size_t, std::unique_ptr<Element>> elements;
typedef std::unordered_map<std::size_t, std::unique_ptr<Element>>::iterator
    elementsIterator;

/**
\internal
\brief Contains a map of indexed elements by the name. The indexBy attributes
specifies the string to use when placing items into the map. The name is case
sensitive.
*/
extern std::unordered_map<std::string, std::reference_wrapper<Element>>
    indexedElements;

/**
\internal
\brief Contains all elements allocated using the system api. They are
contained here as smart pointers and are automatically memory managed.
*/
extern std::vector<std::unique_ptr<StyleClass>> styles;

/**
\enum eventType
\brief the eventType enumeration contains a sequenced value for all of the
events that can be dispatched by the system.
*/
enum class eventType : uint8_t {
  paint,
  focus,
  blur,
  resize,
  keydown,
  keyup,
  keypress,
  mouseenter,
  mousemove,
  mousedown,
  mouseup,
  click,
  doubleclick,
  contextmenu,
  wheel,
  mouseleave
};

/// \typedef eventHandler is used to note and declare a lambda function for
/// the specified event.
typedef std::function<void(const event &et)> eventHandler;

/**
\class event

\brief the event class provides the communication between the event system and
the caller. There is one event class for all of the distinct events. Simply
different constructors are selected based upon the necessity of information
given within the parameters.
*/
using event = class event {
public:
  event(const eventType &et) {
    evtType = et;
    bVirtualKey = false;
  }
  event(const eventType &et, const char &k) {
    evtType = et;
    key = k;
    bVirtualKey = false;
  }
  event(const eventType &et, const unsigned int &vk) {
    evtType = et;
    virtualKey = vk;
    bVirtualKey = true;
  }

  event(const eventType &et, const short &mx, const short &my,
        const short &mb_dis) {
    evtType = et;
    mousex = mx;
    mousey = my;
    if (et == eventType::wheel)
      wheelDistance = mb_dis;
    else
      mouseButton = static_cast<char>(mb_dis);
    bVirtualKey = false;
  }
  event(const eventType &et, const short &w, const short &h) {
    evtType = et;
    width = w;
    height = h;
    bVirtualKey = false;
  }
  event(const eventType &et, const short &distance) {
    evtType = et;
    wheelDistance = distance;
    bVirtualKey = false;
  }
  ~event(){};

public:
  eventType evtType;
  bool bVirtualKey;
  char key;
  unsigned int virtualKey;
  std::wstring unicodeKeys;
  short mousex;
  short mousey;
  char mouseButton;
  short width;
  short height;
  short wheelDistance;
};

/**
\enum numericFormat
\brief numericFormat provides a mode measurement for each of the numeric
parameters given. Each of the numeric attributes within the system use the
doubleNF class which has this stored in it as well as the numerical value.
*/
using numericFormat = enum option { px, pt, em, percent, autoCalculate };

/**
\enum colorFormat
\brief provides the color mode interpret option. Options can be based on
numerical values for rgb, hsl or a string value.
*/
using colorFormat = enum colorFormat { rgb, hsl, name };

/**
\class doubleNF
\brief The class used to hold numeric values along with a mode.

The class provides an easy to use data entry mechanism for numerical values.
Attributes that are numerically based use this as a base class.
*/
class doubleNF {
public:
  double value;
  numericFormat option;
  doubleNF(const doubleNF &_val) : value(_val.value), option(_val.option) {}
  doubleNF(const double &_val, const numericFormat &_nf)
      : value(_val), option(_nf) {}
  doubleNF(const std::string &_str);
  double toPx(void);
  double toPt(void);
};

/**
\internal
\typedef colorMap
\brief the colorMap typedef provides the type for translating a textual name
to a numerical color
*/
typedef std::unordered_map<std::string, unsigned long> colorMap;

/**
\class colorNF
\brief the colorNF class provides a color manipulation base class for
data of this nature. There are several constructor methods which can be used to
declare a color. Such as numerical value, string, a 24bit ulcolor.

*/
class colorNF {
public:
  std::array<double, 4> value;
  colorFormat option;
  static const colorMap colorFactory;
  static colorMap::const_iterator colorIndex(const std::string &_colorName);
  colorNF(const colorFormat &_opt, const std::array<double, 4> &_val)
      : option(_opt), value(_val) {}
  colorNF(const unsigned long &ulColor);
  colorNF(const std::string &_colorName);
  colorNF(colorMap::const_iterator);
  colorNF(const colorNF &_colorObj)
      : option(_colorObj.option), value(_colorObj.value) {}

  void lighter(const double &step = 0.1);
  void darker(const double &step = 0.1);
  void monochromatic(const double &step = 0.1);
  void triad(void);            /*hsl rotate 120*/
  void neutralCooler(void);    /* hsl rotate -30 */
  void neutralWarmer(void);    /* hsl rotate 30 */
  void complementary(void);    /* hsl rotate 180*/
  void splitComplements(void); /*hsl rotate 150 */
};

uint8_t strToEnum(const std::string_view &sListName,
                  const std::unordered_map<std::string, uint8_t> &optionMap,
                  const std::string &sOption);

std::tuple<double, uint8_t>
strToNumericAndEnum(const std::string_view &sListName,
                    const std::unordered_map<std::string, uint8_t> &optionMap,
                    const std::string &_sOption);

std::tuple<doubleNF, doubleNF, doubleNF, doubleNF>
parseQuadCoordinates(const std::string _sOptions);

/**
\internal
\def _NUMERIC_ATTRIBUTE
\brief INTERNEL MACROS to reduce code needed for these attribute storage
implementations. These macros develop the storage class or
inheritance to implement a complex attribute. Within the system, the
"using" provides an alias to name a specific type. Therefore, all classes
declared using these macros will establish their storage space securely at
its position within the attribute storage container. When a getAttribute
with a specific attribute is requested, the reference to this class is
returned. Therefore, values and such can be read or edited using only the
memory. getAttribute is templated so that the most modified values attain
their own specific function. Therefore, newer or specific interfaces can be
developed.
*/
#define _NUMERIC_ATTRIBUTE(NAME)                                               \
  using NAME = class NAME {                                                    \
  public:                                                                      \
    double value;                                                              \
    NAME(const double &_val) : value(_val) {}                                  \
    NAME(const NAME &_val) : value(_val.value) {}                              \
    NAME(const std::string &_str) { value = std::stod(_str, NULL); }           \
  }
/**
\internal
\def _STRING_ATTRIBUTE
\param NAME
\brief declares a string attribute
*/
#define _STRING_ATTRIBUTE(NAME)                                                \
  using NAME = class NAME {                                                    \
  public:                                                                      \
    std::string value;                                                         \
    NAME(const std::string &_val) : value(_val) {}                             \
    NAME(const NAME &_val) : value(_val.value) {}                              \
  }

/**
\internal
\def _NUMERIC_WITH_FORMAT_ATTRIBUTE
\param NAME
\brief declares a numeric with a format specifier attribute
*/
#define _NUMERIC_WITH_FORMAT_ATTRIBUTE(NAME)                                   \
  using NAME = class NAME : public doubleNF {                                  \
  public:                                                                      \
    NAME(const double &_val, const numericFormat &_nf)                         \
        : doubleNF(_val, _nf) {}                                               \
    NAME(const doubleNF &_val) : doubleNF(_val) {}                             \
    NAME(const NAME &_val) : doubleNF(_val) {}                                 \
    NAME(const std::string &_str) : doubleNF(_str) {}                          \
  }

/**
\internal
\def _ENUMERATED_ATTRIBUTE
\param NAME The official name of the attribute class
\param ... a define preprocessor param pack.
\brief declares an enumerated attribute
*/
#define _ENUMERATED_ATTRIBUTE(NAME, ...)                                       \
  using NAME = class NAME {                                                    \
  public:                                                                      \
    enum optionEnum : uint8_t { __VA_ARGS__ };                                 \
    optionEnum value;                                                          \
                                                                               \
  public:                                                                      \
    NAME(const optionEnum &val) : value(val) {}                                \
    NAME(const NAME &val) : value(val.value) {}                                \
    NAME(const std::string &_opt);                                             \
  }

/**
\internal
\def _NUMERIC_WITH_ENUMERATED_ATTRIBUTE
\param NAME The official name of the attribute class
\param ... a define preprocessor param pack.
\brief declares an attribute composed of a numerical value and an
enumerated constant
*/
#define _NUMERIC_WITH_ENUMERATED_ATTRIBUTE(NAME, ...)                          \
  using NAME = class NAME {                                                    \
  public:                                                                      \
    enum optionEnum : uint8_t { __VA_ARGS__ };                                 \
    double value;                                                              \
    optionEnum option;                                                         \
    NAME(const double &_val, const optionEnum &_opt)                           \
        : value(_val), option(_opt) {}                                         \
    NAME(const NAME &_val) : value(_val.value), option(_val.option) {}         \
    NAME(const std::string &_str);                                             \
  }

/**
\internal
\def _COLOR_ATTRIBUTE
\param NAME The official name of the attribute class
\brief declares an attribute composed of a numerical value and an
enumerated constant
*/
#define _COLOR_ATTRIBUTE(NAME)                                                 \
  using NAME = class NAME : public colorNF {                                   \
  public:                                                                      \
    NAME(const double &_v1, const double &_v2, const double &_v3)              \
        : colorNF(colorFormat::rgb, {_v1, _v2, _v3, 0}) {}                     \
    NAME(const std::string &_colorName) : colorNF(_colorName) {}               \
    NAME(const colorFormat &_opt, const std::array<double, 4> &_val)           \
        : colorNF(_opt, _val) {}                                               \
    NAME(const colorFormat _opt, const double &_v1, const double &_v2,         \
         const double &_v3)                                                    \
        : colorNF(_opt, {_v1, _v2, _v3, 0}) {}                                 \
    NAME(const colorFormat &_opt, const double &_v1, const double &_v2,        \
         const double &_v3, const double &_v4)                                 \
        : colorNF(_opt, {_v1, _v2, _v3, _v4}) {}                               \
    NAME(const colorNF &_opt) : colorNF(_opt) {}                               \
  }

/**
\internal
\def _VECTOR_ATTRIBUTE
\param NAME The official name of the attribute class
\brief declares an attribute composed of a vector of string
*/
#define _VECTOR_ATTRIBUTE(NAME)                                                \
  using NAME = class NAME {                                                    \
  public:                                                                      \
    std::vector<std::string> value;                                            \
    NAME(std::vector<std::string> _val) : value(std::move(_val)) {}            \
  }

#define _STRUCT_ATTRIBUTE(NAME, NAME2) using NAME = NAME2

/**
  \addtogroup Attributes
  @{
*/
/// \class indexBy attribute for naming an element using a string. The value
/// is used to index.
_STRING_ATTRIBUTE(indexBy);
/// \class display attribute provides the method to control the layout flow
_ENUMERATED_ATTRIBUTE(display, in_line, block, none);
/// \class position to control the calculation of the position
_ENUMERATED_ATTRIBUTE(position, absolute, relative);
/// \class objectTop controls the position of the object
_NUMERIC_WITH_FORMAT_ATTRIBUTE(objectTop);
/// \class objectLeft controls the position of the object
_NUMERIC_WITH_FORMAT_ATTRIBUTE(objectLeft);
/// \class objectHeight controls the dimension of the object
_NUMERIC_WITH_FORMAT_ATTRIBUTE(objectHeight);
/// \class objectWidth controls the dimension of the object
_NUMERIC_WITH_FORMAT_ATTRIBUTE(objectWidth);
/// \class scrollTop controls the scrolling position of the inner object's
/// contents
_NUMERIC_WITH_FORMAT_ATTRIBUTE(scrollTop);
/// \class scrollLeft controls the scrolling position of the inner object's
/// contents
_NUMERIC_WITH_FORMAT_ATTRIBUTE(scrollLeft);
/// \class background controls the background color
_COLOR_ATTRIBUTE(background);
/// \class opacity controls the transparency of the background
_NUMERIC_ATTRIBUTE(opacity);
/// \class textFace controls true type font used when drawing text. should be
/// a ttf file
_STRING_ATTRIBUTE(textFace);
/// \class textSize controls text rendering size
_NUMERIC_WITH_FORMAT_ATTRIBUTE(textSize);
/// \class textWeight controls character width boldness
_NUMERIC_ATTRIBUTE(textWeight);
/// \class textColor controls character color
_COLOR_ATTRIBUTE(textColor);
/// \class textAlignment controls text alignment
_ENUMERATED_ATTRIBUTE(textAlignment, left, center, right, justified);
/// \class textIndent controls the indentation spacing
_NUMERIC_WITH_FORMAT_ATTRIBUTE(textIndent);
/// \class tabSize controls the indentation spacing
_NUMERIC_WITH_FORMAT_ATTRIBUTE(tabSize);
/// \class lineHeight controls the height of a line when rendered.
_NUMERIC_WITH_ENUMERATED_ATTRIBUTE(lineHeight, normal, numeric);
/// \class marginTop controls the top margin spacing.
_NUMERIC_WITH_FORMAT_ATTRIBUTE(marginTop);
/// \class marginLeft controls the left margin spacing.
_NUMERIC_WITH_FORMAT_ATTRIBUTE(marginLeft);
/// \class marginBotton controls the bottom margin spacing.
_NUMERIC_WITH_FORMAT_ATTRIBUTE(marginBottom);
/// \class marginRight controls the right margin spacing.
_NUMERIC_WITH_FORMAT_ATTRIBUTE(marginRight);
/// \class paddingTop controls the padding at the top.
_NUMERIC_WITH_FORMAT_ATTRIBUTE(paddingTop);
/// \class paddingLeft controls the padding at the left.
_NUMERIC_WITH_FORMAT_ATTRIBUTE(paddingLeft);
/// \class paddingBottom controls the padding at the bottom.
_NUMERIC_WITH_FORMAT_ATTRIBUTE(paddingBottom);
/// \class paddingRight controls the padding at the right.
_NUMERIC_WITH_FORMAT_ATTRIBUTE(paddingRight);
/// \class borderStyle controls the style in which the borders are rendered.
_ENUMERATED_ATTRIBUTE(borderStyle, none, dotted, dashed, solid, doubled, groove,
                      ridge, inset, outset);
/// \class borderWidth controls the width of the border.
_NUMERIC_WITH_FORMAT_ATTRIBUTE(borderWidth);
/// \class borderColor controls the color of the border.
_COLOR_ATTRIBUTE(borderColor);
/// \class borderRadius controls the curvature of the border.
_NUMERIC_ATTRIBUTE(borderRadius);
/// \class focusIndex controls the tab order focus of the user interface
/// element.
_NUMERIC_ATTRIBUTE(focusIndex);
/// \class zIndex controls the zplane order rendering .
_NUMERIC_ATTRIBUTE(zIndex);

/// \class listStyleType controls the icon used to show aside the list items.
_ENUMERATED_ATTRIBUTE(listStyleType, none, disc, circle, square, decimal, alpha,
                      greek, latin, roman);

/// \class windowTitle sets the title of the window. The window class is
/// viewManagerApp always.
_STRING_ATTRIBUTE(windowTitle);

/// \class documentState holds the document state. The stateStructure applies
/// the structure which holds the information.
using documentState = class documentState {
public:
  int i;
  Element *focusField;
};

/** @}*/

/**
 \brief StyleClass provides a way to collect several attributes
 that have a style organized. The name can be applied to an
 element's style property and the class is automatically
 cross referenced to this one.
*/
class StyleClass {
public:
  std::unordered_map<std::type_index, std::any> attributes;
  StyleClass *self;

public:
  template <typename... Args> StyleClass(const Args &...args) : self(this) {
    setValue({args...});
  }
  void setValue(const std::vector<std::any> &attrs) {
    for (auto &n : attrs) {
      std::type_index ti = std::type_index(n.type());
      attributes[ti] = n;
    }
  }
};

/**
  \internal
  \brief Internal function to create elements. The function
  accepts an array where as the main interface version is variodic
*/
template <typename TYPE>
auto &_createElement(const std::vector<std::any> &attr);

/**
\internal
\typedef factoryLambda is used by the document element factory as a
data type for the factory function within the unordered_map.
*/
typedef std::function<Element &(const std::vector<std::any> &attr)>
    factoryLambda;
/**
\internal
\typedef factoryMap is a definition of strings and lambda creation functions.
The document element is referenced by textual tag name wher the function
returns the creation of the object.
*/
typedef std::unordered_map<std::string, factoryLambda> factoryMap;
/**
\internal
\var objectFactoryMap is a constant unordered_map which contains the table.
*/
extern const factoryMap objectFactoryMap;
/**
\internal
\typedef attributeLambda is a function that sets the specific attribute upon
the pased element object.
*/
typedef std::function<void(Element &e, const std::string &param)>
    attributeLambda;
/**
\internal
\typedef attributeStringMap defines the unordered_map that is searched for
an attribute text name. The storage provides an information of the expected
number of parameters. 0 or 1.
*/
typedef std::unordered_map<std::string, std::pair<bool, attributeLambda>>
    attributeStringMap;
/**
\internal
\var attributeFactory is a const variable which holds the collection of
attribute strings, numer of parameters and attribute setting lambda.
*/
extern const attributeStringMap attributeFactory;

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

  
/**
  \class Element
  \brief This is the main Element API. All document entities have this
  interface.
*/
class Element {
public:
  std::string_view softName;

public:
  Element(const std::string_view &_softName,
          const std::vector<std::any> &attribs = {})
      : softName(_softName), m_self(this),
        m_parent(nullptr), m_firstChild(nullptr), m_lastChild(nullptr),
        m_nextChild(nullptr), m_previousChild(nullptr), m_nextSibling(nullptr),
        m_previousSibling(nullptr), m_childCount(0), ingestStream(false) {
    setAttribute(attribs);
  }
  ~Element() {  }
  Element(const Element &other);
  Element(Element &&other) noexcept;
  Element &operator=(const Element &other);
  Element &operator=(Element &&other) noexcept;
#if 0
  inline bool operator==(const Element& lhs, const Element& rhs) {
    return lhs.m_self == rhs.m_self;
  }
#endif

public:
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
  template <typename T> Element &operator<<(const T &data) {

    // display units and event listeners are intercepted here.
    if constexpr (std::is_base_of<display_node_t, T>::value) {
//                  std::is_base_of<listener_t<T>, T>::value) {
    displayList.push_back(data);
    
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

  void stream_input(const std::string &s) {}
  void stream_input(const std::string_view &s) {}

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
  void in(const T &obj, const Args &...args) {
    operator<<(obj);
    in(args...);
  }

public:
  /**
  \tparam R notes the type of element that is to be created
  \tparam T notes the storage form of the associated data.
  \param std::string& is a markup string which is parsed. The form
  notes how the document fragment should be built and where the elements
  inside the named format. Typically the item is a tuple or a struct.

  \brief dataTransform templated function provides the interface for
  providing a transform function to go along with a data set.

  \details
  The dataTransform functionality is very similar to the xsl implementation.
  This version of the templated function provides the capability to have the
  system build elements based upon a markup string while providing an
  association with a data storage format.

  Example
  -------
  \snippet examples.cpp dataTransform_markup_with_data
  */
  template <typename R, typename T>
  void dataTransform(const std::string &txtFn) {}

  /**
  \tparam R notes the type of element that is to be created
  \tparam T notes the strage form of the associated data.
  \param std::string& is a markup string which is parsed. The form
  notes how the document fragment should be built and where the elements
  inside the named format. Typically the item is a tuple or a struct.
  \param std::function<bool(T &)>& provides a Boolean evaluation of the
  data element. The provided function should return true or false based upon
  the desired formatting. If true is return, the string is used to
  format the object.

  \brief dataTransform templated function provides the interface for
  providing a transform function to go along with a data set.

  \details
  The dataTransform functionality is very similar to the xsl implementation.
  This version of the templated function provides the capability to have the
  system build elements based upon a markup string while providing an
  association with a data storage format. In addition, the second parameter
  is an evaluation function which is called for each element proposed for
  display by the rendering system.

  Example
  -------
  \snippet examples.cpp dataTransform_markup_with_data_boolean_func
  */
  template <typename R, typename T>
  void dataTransform(const std::string &txtFn,
                     const std::function<bool(T &)> &_fn) {}

  /**
  \tparam R notes the type of element that is to be created
  \tparam T notes the storage form of the associated data.
  \param const std::function<R &(T &)>& The given parameter is a function
  which is called directly when a particular data element should be displayed
  according to visibility. The function should build the document
  fragment using the createElement API and return the parent object
  of the tree fragment.

  \brief dataTransform templated function provides the interface for
  providing a transform function to go along with a data set.

  \details
  The dataTransform functionality is very similar to the xsl implementation.
  This version of the templated function provides the capability to have the
  system build elements based upon the return of the given function. This
  function is called directly with a reference to the data element that
  will need display.

  Example
  -------
  \snippet examples.cpp dataTransform_func
  */
  template <typename R, typename T>
  void dataTransform(const std::function<R &(T &)> &_fn) {
    std::function<R &(T &)> fn = _fn;
    std::type_index tIndex = std::type_index(typeid(std::vector<T>));

    // if the requested data adapter does not exist,
    // create its position within the adapter member vector
    // return this to the caller.
  }

  /**
  \tparam R notes the type of element that is to be created
  \tparam T notes the storage form of the associated data.

  \brief This data transform uses the named value of the numerical column.

  \details
  This data transform uses an unordered_map to reference a lambda by a
  particular column within the tuple. So each record within the definition,
  provides a layout capability that is coded by the key. This creates a
  situation where maintenance of the layout is based editing the list.

  Example
  -------
  \snippet examples.cpp dataTransform_unordered_map
  */
  template <std::size_t I, typename T>
  void dataTransform(
      const std::unordered_map<typename std::tuple_element<I, T>::type,
                               std::function<Element &(T &)>> &_transformList) {
  }
  /**
    \brief data access interface for element based data storage.
    Elements can store vectors of the named type. This method provides
    an easy way to insert children into the element. As well by using the
    dataTransform in conjunction with the data() templated member, child
    elements may be build and formatted to the developer's specification. The
    information when given should always be in the form of a vector initializer
    list.

    \tparam T defaulted to a std::string.

    Example setting data
    --------------------
    \snippet examples.cpp data

    Example pushing the vector
    --------------------------
    \snippet examples.cpp data_push

  */
  template <typename T = std::string> auto &data(void) {
    // distingish from multiple types of inputs
    if constexpr (std::is_base_of<std::string, T>::value) {
      return m_data;
    }
  }
  template <typename T = std::string> void data(const T &data) {
    // distingish from multiple types of inputs
    if constexpr (std::is_base_of<std::string, T>::value) {
      m_data=data;
    } else {
      std::ostringstream s;
      s << data;
      m_data=s;
    }
  }

  /**
  \brief the dataHint function provides the mechanism to inform the rendering
  system of changes to the underlying data within the buffers.

  */
  template <typename T>
  void dataHint(const T &hint1, std::size_t hint2 = 0, std::size_t hint3 = 0) {}

  template <typename T>
  void dataHint(int hint1 = 0, std::size_t hint2 = 0, std::size_t hint3 = 0) {}

  /**
  \var ingestStream
  \brief The ingestStream Boolean value is a setting which determines
  if the stream coming into the system is first interpreted as markup
  content. Two functions both check this value. The stream input operator and
  the printf function. If you desire that content should be parsed as a markup
  stream, this variable should be set to true.
  */
  bool ingestStream; // change form documentation

  auto query(const std::string &queryString) { return 0;};
  auto query(const ElementQuery &queryFunction) { return 0;};
private:
  Element *m_self;
  Element *m_parent;
  Element *m_firstChild;
  Element *m_lastChild;
  Element *m_nextChild;
  Element *m_previousChild;
  Element *m_nextSibling;
  Element *m_previousSibling;
  std::size_t m_childCount;
  std::string m_data;

  // interface access points for the tree traversal functions
public:
/**
  \internal
  \def _REF_INTERFACE
  \brief the macro creates a public interface for the named data member.
  The first macro parameter names the interface while the second parameter
  names a member pointer. Noted that the interface will return a reference
  wrapper or nullptr. This macro is used to declare and implement the document
  tree traversal methods.
*/
#define _REF_INTERFACE(NAME, xNAME)                                            \
  std::optional<std::reference_wrapper<Element>> NAME(void) {                  \
    return (xNAME ? std::optional<std::reference_wrapper<Element>>{*xNAME}     \
                  : std::nullopt);                                             \
  }
  /**
   \fn parent
   \brief contains the parent element within the document traversal hierarchy

   Example
   -------
   \snippet examples.cpp parent
  */
  _REF_INTERFACE(parent, m_parent);

  /**
  \fn firstChild
  \brief contains the firstChild element within the document traversal
   hierarchy

   Example
   -------
   \snippet examples.cpp firstChild
  */
  _REF_INTERFACE(firstChild, m_firstChild);

  /**
    \fn lastChild
    \brief contains the lastChild element within the document traversal
    hierarchy

    Example
    -------
    \snippet examples.cpp lastChild
  */
  _REF_INTERFACE(lastChild, m_lastChild);

  /**
    \fn nextChild
    \brief contains the nextChild element within the document traversal
    hierarchy

    Example
    -------
    \snippet examples.cpp nextChild
  */
  _REF_INTERFACE(nextChild, m_nextChild);

  /**
    \fn previousChild
    \brief contains the previousChild element within the document traversal
    hierarchy

    Example
    -------
    \snippet examples.cpp previousChild
  */
  _REF_INTERFACE(previousChild, m_previousChild);

  /**
    \fn nextSibling
    \brief contains the nextSibling element within the document traversal
    hierarchy

    Example
    -------
    \snippet examples.cpp nextSibling
  */
  _REF_INTERFACE(nextSibling, m_nextSibling);

  /**
    \fn previousSibling
    \brief contains the previousSibling element within the document traversal
    hierarchy

    Example
    -------
    \snippet examples.cpp previousSibling
  */
  _REF_INTERFACE(previousSibling, m_previousSibling);

  /**
    \fn childCount
    \brief contains the number of children

    Example
    -------
    \snippet examples.cpp childCount
  */
  inline std::size_t &childCount(void) { return m_childCount; }

  /**
  \internal
  \class iterator
  \brief An iterator class that traverses the tree
  */
  class iterator {
  public:
    iterator(Element *pNode) noexcept : m_pCurrentNode(pNode) {}
    iterator &operator=(Element *pNode);
    iterator &operator++();
    iterator operator++(int);
    iterator &operator--();
    bool operator!=(const iterator &iterator);
    Element &operator*();
    iterator begin();
    iterator end();

  private:
    Element *m_pCurrentNode;
  };

  /**
  \fn children(void)
  \brief The function provides a method to easily write range based for loops.
  \details The children function provides a method that returns an iterator
  object. This iterator object is an internally defined class that implements
  the c++ interface for iterators.

  \snippet examples.cpp children

  */
  auto children(void) -> iterator { return iterator(this); };

  /**
    \var styles
    \brief contains the style classes associated with the element

    Example
    -------
    \snippet examples.cpp styles
  */
  std::vector<std::reference_wrapper<StyleClass>> styles;

private:
  std::unordered_map<std::type_index, std::any> attributes;

public:
  display_list_t displayList;

public:
  auto appendChild(const std::string &sMarkup) -> Element &;
  auto appendChild(Element &newChild) -> Element &;
  auto appendChild(const ElementList &elementCollection) -> Element &;
  /**
   \brief the templated function accepts an element type within the template
   parameter and attributes within the parameter. The created element is
   appended as a child.
   \tparam ATTR... param pack of attribute objects.
   \return Element& a reference to the newly appended child

   Example
   -------
   \snippet examples.cpp appendChild_parampack

  */
  template <typename TYPE, typename... ATTRS>
  auto appendChild(const ATTRS &...attrs) -> Element & {
    TYPE &e = _createElement<TYPE>({attrs...});
    appendChild(e);
    return (e);
  }

public:
  auto append(const std::string &sMarkup) -> Element &;
  auto append(Element &sibling) -> Element &;
  auto append(ElementList &elementCollection) -> Element &;
  /**
  \brief the templated function accepts a element type within the template
  parameter and attributes within the parameter. The created element is
  appended as a sibling of the referenced element.

  \tparam ATTR... param pack of attribute objects.

  \return a reference to the appended object for continuation syntax.

  Example
  -------
  \snippet examples.cpp append_parampack

  */
  template <typename TYPE, typename... ATTRS>
  auto append(const ATTRS &...attrs) -> Element & {
    TYPE &e = _createElement<TYPE>({attrs...});
    append(e);
    return (e);
  }

public:
  Element &setAttribute(const std::vector<std::any> &attribs);
  Element &setAttribute(const std::any &setting);

  /** \brief The setAttribute templated function provides a
  parameter pack version which expands the parameters into a vector of
  std::any.
  \tparam TYPES... a param pack of attributes

  Example
  -------
  \snippet examples.cpp setAttribute_parampack

  */
  template <typename... TYPES> Element &setAttribute(const TYPES &...settings) {
    setAttribute(std::vector<std::any>{settings...});
    return *this;
  }

public:
  /**
    \brief the templated function returns specified attribute.
    \tparam ATTR_TYPE a named object.
    \return returns a reference to the attribute. An exception
    is raised if the attribute is currently not associated.
    \exception std::invalid_argument When an element does not contain
    an element, an exception is thrown.

    Example
    -------
    \snippet examples.cpp getAttribute

  */
  template <typename ATTR_TYPE> ATTR_TYPE &getAttribute(void) {
    ATTR_TYPE *ret = nullptr;
    auto it = attributes.find(std::type_index(typeid(ATTR_TYPE)));
    if (it != attributes.end()) {
      ret = &std::any_cast<ATTR_TYPE &>(it->second);

    } else {
      std::string info = typeid(ret).name();
      info += " attribute not found";

      throw std::invalid_argument(info);
    }
    return *ret;
  }

private:
  std::vector<eventHandler> onfocus;
  std::vector<eventHandler> onblur;
  std::vector<eventHandler> onresize;
  std::vector<eventHandler> onkeydown;
  std::vector<eventHandler> onkeyup;
  std::vector<eventHandler> onkeypress;
  std::vector<eventHandler> onmouseenter;
  std::vector<eventHandler> onmouseleave;
  std::vector<eventHandler> onmousemove;
  std::vector<eventHandler> onmousedown;
  std::vector<eventHandler> onmouseup;
  std::vector<eventHandler> onclick;
  std::vector<eventHandler> ondblclick;
  std::vector<eventHandler> oncontextmenu;
  std::vector<eventHandler> onwheel;

private:
  std::vector<eventHandler> &getEventVector(eventType evtType);

public:
  auto move(const double t, const double l) -> Element &;
  auto resize(const double w, const double h) -> Element &;
  auto addListener(eventType evtType, eventHandler evtHandler) -> Element &;
  auto removeListener(eventType evtType, eventHandler evtHandler) -> Element &;
  void dispatch(const event &e);
  auto insertBefore(Element &newChild, Element &existingElement) -> Element &;
  auto insertBefore(Element &newChild, std::string &sID) -> Element &;
  auto insertAfter(Element &newChild, Element &existingElement) -> Element &;
  auto insertAfter(Element &newChild, std::string &sID) -> Element &;
  void remove(void);
  auto removeChild(Element &childElement) -> Element &;
  auto removeChild(std::string &sID) -> Element &;
  auto removeChildren(void) -> Element &;
  auto clear(void) -> Element &;
  auto replaceChild(Element &newChild, Element &oldChild) -> Element &;
  auto replaceChild(Element &newChild, std::string &sID) -> Element &;

#if defined(__clang__)
  void printf(const char *fmt, ...)
      __attribute__((__format__(__printf__, 2, 0)));
#else
  void printf(const char *fmt, ...);
#endif

private:
  /// \enum the type of tokenized data
  enum itemType {
    element,
    elementTerminal,
    attribute,
    attributeValue,
    attributeSimple,
    color,
    textData
  };

  /// \typedef the variant holds the payload from the tokenizer
  typedef std::variant<std::string, factoryLambda, attributeLambda, colorNF>
      parserOperator;

  /// \typedef the structure that holds the parser context.
  typedef struct {
    // the elements parsed thus far token
    std::vector<std::tuple<itemType, bool, parserOperator>> parsedData;
    // stack holding the tree of elements
    std::vector<std::reference_wrapper<Element>> elementStack;
    // true when a < is encountered, Presumed that the information will be a
    // markup
    bool bSignal;
    // true when a primary token has been captured, ie the first item after the
    // <
    bool bToken;
    // skips the character from being captured.
    bool bSkip;
    // true when the / is encountered and a signal has been found
    bool bTerminal;
    // true when the attributes are being set.
    bool bAttributeList;
    // true when an attribute value is expected
    bool bAttributeListValue;
    // true when the information should be queried for a token
    bool bQuery;
    // holds the position of the signal start
    const char *signalStart;
    // the capturing of an element or token name
    std::string sCapture;
    // text information that will be added to the elements data
    std::string sText;

  } parserContext;

  void processParseContext(parserContext &pc);
  auto ingestMarkup(Element &node, const std::string &markup) -> Element &;
  void updateIndexBy(const indexBy &setting);
}; // class Element

// prototypes for the user defined literals
auto operator""_pt(unsigned long long int value) -> doubleNF;
auto operator""_pt(long double value) -> doubleNF;
auto operator""_em(unsigned long long int value) -> doubleNF;
auto operator""_em(long double value) -> doubleNF;
auto operator""_px(unsigned long long int value) -> doubleNF;
auto operator""_px(long double value) -> doubleNF;
auto operator""_percent(unsigned long long int value) -> doubleNF;
auto operator""_percent(long double value) -> doubleNF;
auto operator""_pct(unsigned long long int value) -> doubleNF;
auto operator""_pct(long double value) -> doubleNF;
auto operator""_normal(unsigned long long int value) -> lineHeight;
auto operator""_normal(long double value) -> lineHeight;
auto operator""_numeric(unsigned long long int value) -> lineHeight;
auto operator""_numeric(long double value) -> lineHeight;

/**
\addtogroup Entities Document Entities

The document entities is a collection which is established in the
base model. Typical character processing and basic flow layout are
established by these objects. The document entity must derrive from the
Element class as a base class.

@{
*/
/**
\class BR
\brief line break
\extends Element

\details When the BR element is present within the document
hierarchy, it is likened to the effects of a \n new line or return.
The next position of textual or document flow will go to the next line
position.

Example
-------
\snippet examples.cpp BR

*/
using BR = class BR : public Element {
public:
  BR(const std::vector<std::any> &attribs) : Element("br") {
    setAttribute(attribs);
  }
};
/**
\class H1
\brief heading level 1
\extends Element
\details The H1 element provides a heading of a level 1 within a document.
The element is useful for titles. The object is created with the following
default styles.

- display::block
- marginTop{.67_em}
- marginLeft{.67_em}
- marginBottom{0_em}
- marginRight{0_em}
- textSize{2_em}
- textWeight{800}

Example
-------
\snippet examples.cpp H1
*/
using H1 = class H1 : public Element {
public:
  H1(const std::vector<std::any> &attribs)
      : Element("h1", {display::block, marginTop{.67_em}, marginLeft{.67_em},
                       marginBottom{0_em}, marginRight{0_em}, textSize{2_em},
                       textWeight{800}}) {
    setAttribute(attribs);
  }
};
/**
\class H2
\brief heading level 2
\extends Element
\details The H2 element provides a heading of a level 2 within a document.
The element is useful for titles. The object is created with the following
default styles.

- display::block
- marginTop{.83_em}
- marginLeft{.83_em}
- marginBottom{0_em}
- marginRight{0_em}
- textSize{1.5_em}
- textWeight{800}

Example
-------
\snippet examples.cpp H2
*/
using H2 = class H2 : public Element {
public:
  H2(const std::vector<std::any> &attribs)
      : Element("h2", {display::block, marginTop{.83_em}, marginLeft{.83_em},
                       marginBottom{0_em}, marginRight{0_em}, textSize{1.5_em},
                       textWeight{800}}) {
    setAttribute(attribs);
  }
};
/**
\class H3
\brief heading level 3
\extends Element
\details The H2 element provides a heading of a level 2 within a document.
The element is useful for titles. The object is created with the following
default styles.

- display::block
- marginTop{1_em}
- marginLeft{1_em}
- marginBottom{0_em}
- marginRight{0_em}
- textSize{1.17_em}
- textWeight{800}

Example
-------
\snippet examples.cpp H3
*/
using H3 = class H3 : public Element {
public:
  H3(const std::vector<std::any> &attribs)
      : Element("h3", {display::block, marginTop{1_em}, marginLeft{1_em},
                       marginBottom{0_em}, marginRight{0_em}, textSize{1.17_em},
                       textWeight{800}}) {
    setAttribute(attribs);
  }
};
/**
\class PARAGRAPH
\brief a paragraph of text
\extends Element
\details The paragraph element allows for a flowing block of information that
is considered to be a paragraph. The object is created with the following
defaulted attributes:

- listStyleType::disc
- marginTop{1_em}
- marginLeft{1_em}
- marginBottom{0_em}
- marginRight{0_em}

Example
-------
\snippet examples.cpp PARAGRAPH
*/
using PARAGRAPH = class PARAGRAPH : public Element {
public:
  PARAGRAPH(const std::vector<std::any> &attribs)
      : Element("paragraph", {display::block, marginTop{1_em}, marginLeft{1_em},
                              marginBottom{0_em}, marginRight{0_em}}) {
    setAttribute(attribs);
  }
};
/**
\class DIV
\brief a divisor block
\extends Element
\details The DIV element provides a block level element. Within the
box model, the information aligns top down. When additional blocks are added,
the items flow as if a carriage return were entered. The object is created
with the following default styles:

- display::block

Example
-------
\snippet examples.cpp DIV
*/
using DIV = class DIV : public Element {
public:
  DIV(const std::vector<std::any> &attribs) : Element("div", {display::block}) {
    setAttribute(attribs);
  }
};
/**
\class SPAN
\brief a span block
\extends Element
\details The SPAN block provides a continued flowing element. The
object has no default styles associated.


Example
-------
\snippet examples.cpp SPAN
*/
using SPAN = class SPAN : public Element {
public:
  SPAN(const std::vector<std::any> &attribs)
      : Element("span", {display::in_line}) {
    setAttribute(attribs);
  }
};
/**
\class UL
\brief an unordered list
\extends Element
\details The UL block provides an unordered list of items. Children
of the list can be added using the data() or by manually adding LI elements.
When created, the following default attributes are established:

- listStyleType::disc
- display::block
- marginTop{1_em}
- marginLeft{1_em}
- marginBottom{0_em}
- marginRight{0_em}
- paddingLeft{40_px}

Example
-------
\snippet examples.cpp UL
*/
using UL = class UL : public Element {
public:
  UL(const std::vector<std::any> &attribs)
      : Element("ul", {listStyleType::disc, display::block, marginTop{1_em},
                       marginLeft{1_em}, marginBottom{0_em}, marginRight{0_em},
                       paddingLeft{40_px}}) {
    setAttribute(attribs);
  }
};
/**
\class OL
\brief an ordered list
\extends Element
\details The UL block provides an ordered list of items. When multiple
children exists, they are numerically numbered automatically. The listStyleType
notes what for the numeric literals are shown as. Children
of the list can be added using the data() or by manually adding LI elements.
When created, the following default attributes are established:

- listStyleType::decimal
- display::block
- marginTop{1_em}
- marginLeft{1_em}
- marginBottom{0_em}
- marginRight{0_em}
- paddingLeft{40_px}

Example
-------
\snippet examples.cpp OL
*/
using OL = class OL : public Element {
public:
  OL(const std::vector<std::any> &attribs)
      : Element("ol", {listStyleType::decimal, display::block, marginTop{1_em},
                       marginLeft{1_em}, marginBottom{0_em}, marginRight{0_em},
                       paddingLeft{40_px}}) {
    setAttribute(attribs);
  }
};
/**
\class LI
\brief an list item, can be inserted into ol or ul
\extends Element
\details The LI element is a list item. Its persistence is
associated with the UL and OL elements. As a child, this
object is usually in a series of items of these list items.

Example
-------
\snippet examples.cpp LI

*/
using LI = class LI : public Element {
public:
  LI(const std::vector<std::any> &attribs) : Element("li", {display::block}) {
    setAttribute(attribs);
  }
};

/**
  \typedef tableColumns
  \brief tableColumns is a two dimensional string vector named appropiately
  for the TABLE element.
  \see TABLE
*/
using tableColumns = std::vector<std::string>;

/**
\typedef tableData
\brief The tableData alias is used by the TABLE element. It
is useful when setting the data that is shown within the view.
It is a two dimensional vector of std::string.
  \see TABLE
*/
using tableData = std::vector<std::vector<std::string>>;

/**
\class TABLE
\brief a table element to manage a grid of information
\extends Element
\details The TABLE element provides a grid layout of information.
the child elements that are applied is the table data attribute.
This attribute is a two dimensional vector composed of string
values.

Example
-------
\snippet examples.cpp TABLE

*/
using TABLE = class TABLE : public Element {
public:
  TABLE(const std::vector<std::any> &attribs) : Element("table") {
    setAttribute(attribs);
  }
};
/**
\class IMAGE
\brief an image
\extends Element
\details The IMAGE element display an image. The filename of the image
should be given within the data property as a string.

Example
-------
\snippet examples.cpp IMAGE

*/
using IMAGE = class IMAGE : public Element {
public:
  IMAGE(const std::vector<std::any> &attribs)
      : Element("image", {display::in_line}) {
    setAttribute(attribs);
  }
};
/**
\class textNode
\brief a node of textual information
\extends Element
\details The textNode is a textual component that at times is necessary
for children of other main document entities. When colors are modified
mid stream for other document elements, the subsequent text along with
the specified color is added as a textNode automatically by the parsing
stream API.

Example
-------
\snippet examples.cpp textNode

*/
class textNode : public Element {
public:
  textNode(const std::vector<std::any> &attribs) : Element("textNode") {
    setAttribute(attribs);
  }
};
/** @}*/

/**
\def USE_LOWER_CASE_ENTITY_NAMES
\brief Options for compiling that provide recognition of
 lower case entity names.
*/
#define USE_LOWER_CASE_ENTITY_NAMES
// map lower case terms as well for flexibility
#ifdef USE_LOWER_CASE_ENTITY_NAMES
using element = Element;
using paragraph = PARAGRAPH;
using br = BR;
using h1 = H1;
using h2 = H2;
using h3 = H3;
using dblock = DIV;
using span = SPAN;
using ul = UL;
using ol = OL;
using li = LI;
using image = IMAGE;
using textnode = textNode;
#endif

/**
\internal
\brief_createElement that accepts a vector of std::any attributes
\tparam TYPE is a named document entity.
*/
template <typename TYPE>
auto &_createElement(const std::vector<std::any> &attrs) {
  // create object
  std::unique_ptr<TYPE> e = std::make_unique<TYPE>(attrs);
  // storage key is actually the numeric pointer.
  std::size_t storageKey = (std::size_t)e.get();

  // this version of the insert returns the position of where it was inserted.
  // this is important as the pointer will be owned by the unordered_map
  // simply getting the value
  std::pair<elementsIterator, bool> ret =
      elements.insert({storageKey, std::move(e)});

  TYPE *typedReturn = static_cast<TYPE *>(ret.first->second.get());
  return static_cast<TYPE &>(*typedReturn);
}

/**
\addtogroup API Global Document API

@{
*/

/**
\brief A templated factory implementation for reference based callee and
viewManager ownership of the object.

\tparam TYPE is the object type to create. This class should be one that
is derrived from the base element class.

\tparam ATTRS... is a parameter pack of attributes.

\details The createElement templated function is the main way in which
top level elements are created. The function returns a reference object.
Internally the function manufactures a smart pointer to the document entity
and object

Example
-------
\snippet examples.cpp createElement

*/
template <class TYPE, typename... ATTRS>
auto &createElement(const ATTRS &...attribs) {
  return _createElement<TYPE>({attribs...});
  ;
}
/**
\brief A templated function that creates a collection of attributes. The
returned value can be placed upon the style vector of an element. This
provides the mechanism to define styles once and have them linked to several.

\tparam Types... is a parameter pack of attributes. The parameter pack is
expanded and places inside a vector which is the style.
*/
template <typename... Types> auto createStyle(Types... args) -> StyleClass & {
  std::unique_ptr<StyleClass> newStyle = std::make_unique<StyleClass>(args...);
  styles.push_back(std::move(newStyle));
  return *styles.back().get();
}

auto query(const std::string &queryString) -> ElementList;
auto query(const ElementQuery &queryFunction) -> ElementList;

/**
  \brief The getElement function searches the indexed elements and
  returns the referenced element. The indexBy attributes is used to index.
  \tparam T is defaulted to the base object type of Element. A specific
  element type can also be sought and returned.
*/
template <class T = Element &> auto getElement(const std::string &key) -> T & {

  auto it = indexedElements.find(key);
  if (it != indexedElements.end()) {
    T &ret = reinterpret_cast<T &>(it->second.get());
    return ret;

  } else {
    std::string info = key;
    info += " element not found by ID ";

    throw std::invalid_argument(info);
  }
}

bool hasElement(const std::string &key);
/** @}*/

/**
\def
The object factory map provides a parser allocation map for base objects.
Currently the implementation is const. When more elements are added this
will need updating to support the alternate methods of allocation. Perhaps
architecturally the functionality can be turned into a function during the
ingestMarkup routine. When the ingestMarkup routine finds a unrecognized entry
according to the map lookup, the dynamic map provided for extension is then
queried. The dynamic extension table is provided for growth when different tools
are added on top of the viewManager base library.
*/
#define CREATE_OBJECT(OBJECT_TEXT, OBJECT_TYPE)                                \
  {                                                                            \
    #OBJECT_TEXT, [](const std::vector<std::any> &attrs) -> Element & {        \
      return _createElement<OBJECT_TYPE>(attrs);                               \
    }                                                                          \
  }


/**
\brief The class is the main document viewer. Applications must create this as
the top node of the tree. All subsequent operations are added or appended to
this object.
*/

class Viewer : public Element {
public:
  Viewer(const std::vector<std::any> &attribs);
  ~Viewer();
  Viewer(const Viewer &) : Element("Viewer") {}
  Viewer &operator=(const Viewer &) {return *this;}
  Viewer &operator=(Viewer &&other) noexcept {return *this;} // move assignment
  void render();
  void processEvents(void);
  void dispatchEvent(const event_t &e);

private:
  std::unique_ptr<os_interface_manager_t> m_os;
  display_list_t m_displaylist;
};
} // namespace viewManager

#ifdef INCLUDE_UX
#include "viewManagerUX.hpp"
#endif
