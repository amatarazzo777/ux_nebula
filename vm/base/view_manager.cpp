/**
\file viewManager.cpp

\author Anthony Matarazzo

\date 11/19/19
\version 1.0
*/

/**
\brief class that implements that main creation interface.
 The file contains initialization, termination.

*/

/**
  \def
  \brief
  this definition provides the ability to utilize the UX namespace
*/
#include <vm/vm.h>

using namespace std;
using namespace viewManager;

/**
\internal

\brief These namespace specific data structures hold the system
level document elements. The tracking of them is done using a
smart pointer. The elements in the main allocation of the system
are indexed by the numeric pointer address. When elements are removed
from the system, they should be done so through the element unordered_map.
This unordered map tracks them by the numerical pointer id.
Elements may also be indexed using the indexBy attribute
and the map contains a reference wrapper to the element. These items
are not normally accessed by the developer. They are accessed using the
API. The create, append, and getElement functions provide the searching and
creation of the objects.
*/
std::unordered_map<std::size_t, std::unique_ptr<Element>> viewManager::elements;
std::unordered_map<std::string, std::reference_wrapper<Element>>
    viewManager::indexedElements;
std::vector<std::unique_ptr<StyleClass>> viewManager::styles;

/**
\internal

\brief The objectFactoryMap provides an easy to maintain table of document
entities. The syntax, for consolidation, uses the macros CREATE_OBJECT
and CREATE_OBJECT_ALIAS. These macros expand to a string and a lambda
function which calls the createElement document API. The function
returns the newly created element. The table is used by the
parser to instantiate document elements.

*/
const factoryMap viewManager::objectFactoryMap = {

#ifdef INCLUDE_UX
    CREATE_OBJECT(text, UX::text),
    CREATE_OBJECT(password, UX::password),
    CREATE_OBJECT(multiline, UX::multiline),
    CREATE_OBJECT(number, UX::number),
    CREATE_OBJECT(masked, UX::masked),
    CREATE_OBJECT(pushbutton, UX::pushButton),
    CREATE_OBJECT(button, UX::pushButton),
    CREATE_OBJECT(radiobutton, UX::radioButton),
    CREATE_OBJECT(radio, UX::radioButton),
    CREATE_OBJECT(hotimage, UX::hotImage),
    CREATE_OBJECT(group, UX::group),
    CREATE_OBJECT(checkbox, UX::checkBox),
    CREATE_OBJECT(date, UX::date),
    CREATE_OBJECT(datetime, UX::dateTime),
    CREATE_OBJECT(week, UX::week),
    CREATE_OBJECT(time, UX::time),
    CREATE_OBJECT(file, UX::file),
    CREATE_OBJECT(verticalscrollbar, UX::verticalScrollbar),
    CREATE_OBJECT(horizontalscrollbar, UX::horizontalScrollbar),
    CREATE_OBJECT(listselector, UX::listSelector),
    CREATE_OBJECT(list, UX::listSelector),
    CREATE_OBJECT(menu, UX::menu),
    CREATE_OBJECT(gridedit, UX::gridEdit),
    CREATE_OBJECT(tabbedpanel, UX::tabbedPanel),
    CREATE_OBJECT(sliderrange, UX::sliderRange),
    CREATE_OBJECT(knobrange, UX::knobRange),
    CREATE_OBJECT(knob, UX::knobRange),
    CREATE_OBJECT(accordion, UX::accordion),
    CREATE_OBJECT(progress, UX::progress),
    CREATE_OBJECT(dialog, UX::dialog),
#endif

    CREATE_OBJECT(br, BR),
    CREATE_OBJECT(h1, H1),
    CREATE_OBJECT(h2, H2),
    CREATE_OBJECT(h3, H3),
    CREATE_OBJECT(paragraph, PARAGRAPH),
    CREATE_OBJECT(p, PARAGRAPH),
    CREATE_OBJECT(div, DIV),
    CREATE_OBJECT(span, SPAN),
    CREATE_OBJECT(ul, UL),
    CREATE_OBJECT(ol, OL),
    CREATE_OBJECT(li, LI),
    CREATE_OBJECT(image, IMAGE)

};

// clang-format off

/**
\internal
\details
The attribtueStringMap provides a lookup table for
lower case attributes and aliases of an attribute.
The second map storage is a lambda function which
sets the specific attribute. The lambda accepts to parameters,
the base element for which to set the attribute on and
the string value of the setting. It should be noted that the
attribute objects themselves parse the input parameter where needed.

The Boolean value notes if the item is a compound or single word.
Items that are single words are shorthand for attributes that have enumeration values
for example block instead of using display:block.
This informs the context of the parser to advance and except a secondary value or not.

*/
const attributeStringMap
    viewManager::attributeFactory = {
    {"id",{true,
        [](Element &e, string s) {
            e.setAttribute(indexBy{s});
        }}
    },

    {"indexby",{true,
        [](Element &e, string s) {
            e.setAttribute(indexBy{s});
        }}
    },

    {"block",{false,
        [](Element &e, string s) {
            e.setAttribute(display::block);
        }}
    },

    {"inline",{false,
        [](Element &e, string s) {
            e.setAttribute(display::in_line);
        }}
    },

    {"hidden",{false,
        [](Element &e, string s) {
            e.setAttribute(display::none);
        }}
    },

    {"display",{true,
        [](Element &e, string s) {
            e.setAttribute(display{s});
        }}
    },

    {"absolute",{false,
        [](Element &e, string s) {
            e.setAttribute(position::absolute);
        }}
    },

    {"relative",{false,
        [](Element &e, string s) {
            e.setAttribute(position::relative);
        }}
    },

    {"position",{true,
        [](Element &e, string s) {
            e.setAttribute(position{s});
        }}
    },

    {"objecttop",{true,
        [](Element &e, string s) {
            e.setAttribute(objectTop{doubleNF(s)});
        }}
    },

    {"top",{true,
        [](Element &e, string s) {
            e.setAttribute(objectTop{doubleNF(s)});
        }}
    },

    {"objectleft",{true,
        [](Element &e, string s) {
            e.setAttribute(objectLeft{doubleNF(s)});
        }}
    },

    {"left",{true,
        [](Element &e, string s) {
            e.setAttribute(objectLeft{doubleNF(s)});
        }}
    },

    {"objectheight",{true,
        [](Element &e, string s) {
            e.setAttribute(objectHeight{doubleNF(s)});
        }}
    },

    {"height",{true,
        [](Element &e, string s) {
            e.setAttribute(objectHeight{doubleNF(s)});
        }}
    },

    {"objectwidth",{true,
        [](Element &e, string s) {
            e.setAttribute(objectWidth{doubleNF(s)});
        }}
    },

    {"width",{true,
        [](Element &e, string s) {
            e.setAttribute(objectWidth{doubleNF(s)});
        }}
    },

    {"coordinates",{true,
        [](Element &e, string s) {
            auto coords=parseQuadCoordinates(s);

            e.setAttribute(objectTop{std::get<0>(coords)});
            e.setAttribute(objectLeft{std::get<1>(coords)});
            e.setAttribute(objectHeight{std::get<2>(coords)});
            e.setAttribute(objectWidth{std::get<3>(coords)});
        }}
    },

    {"scrolltop",{true,
        [](Element &e, string s) {
            e.setAttribute(scrollTop{doubleNF(s)});
        }}
    },

    {"scrollleft",{true,
        [](Element &e, string s) {
            e.setAttribute(scrollLeft{doubleNF(s)});
        }}
    },

    {"background",{true,
        [](Element &e, string s) {
            e.setAttribute(background{colorNF(s)});
        }}
    },

    {"opacity",{true,
        [](Element &e, string s) {
            e.setAttribute(opacity{s});
        }}
    },

    {"textface",{true,
        [](Element &e, string s) {
            e.setAttribute(textFace{s});
        }}
    },

    {"textsize",{true,
        [](Element &e, string s) {
            e.setAttribute(textSize{doubleNF(s)});
        }}
    },

    {"textweight",{true,
        [](Element &e, string s) {
            e.setAttribute(textWeight{s});
        }}
    },

    {"weight",{true,
        [](Element &e, string s) {
            e.setAttribute(textWeight{s});
        }}
    },
    {"textcolor",{true,
        [](Element &e, string s) {
            e.setAttribute(textColor{colorNF(s)});
        }}
    },

    {"color",{true,
        [](Element &e, string s) {
            e.setAttribute(textColor{colorNF(s)});
        }}
    },
    {"textalignment",{true,
        [](Element &e, string s) {
            e.setAttribute(textAlignment{s});
        }}
    },

    {"left",{false,
        [](Element &e, string s) {
            e.setAttribute(textAlignment::left);
        }}
    },
    {"center",{false,
        [](Element &e, string s) {
            e.setAttribute(textAlignment::center);
        }}
    },
    {"right",{false,
        [](Element &e, string s) {
            e.setAttribute(textAlignment::right);
        }}
    },
    {"justified",{false,
        [](Element &e, string s) {
            e.setAttribute(textAlignment::justified);
        }}
    },

    {"textindent",{true,
        [](Element &e, string s) {
            e.setAttribute(textIndent{doubleNF(s)});
        }}
    },

    {"indent",{true,
        [](Element &e, string s) {
            e.setAttribute(textIndent{doubleNF(s)});
        }}
    },

    {"tabsize",{true,
        [](Element &e, string s) {
            e.setAttribute(tabSize{doubleNF(s)});
        }}
    },

    {"tab",{true,
        [](Element &e, string s) {
            e.setAttribute(tabSize{doubleNF(s)});
        }}
    },

    {"lineheight",{true,
        [](Element &e, string s) {
            e.setAttribute(lineHeight{s});
        }}
    },

    {"normal",{false,
        [](Element &e, string s) {
            e.setAttribute(lineHeight::normal);
        }}
    },

    {"numeric",{false,
        [](Element &e, string s) {
            e.setAttribute(lineHeight::numeric);
        }}
    },


    {"margintop",{true,
        [](Element &e, string s) {
            e.setAttribute(marginTop{doubleNF(s)});
        }}
    },

    {"marginleft",{true,
        [](Element &e, string s) {
            e.setAttribute(marginLeft{doubleNF(s)});
        }}
    },

    {"marginbottom",{true,
        [](Element &e, string s) {
            e.setAttribute(marginBottom{doubleNF(s)});
        }}
    },

    {"marginright",{true,
        [](Element &e, string s) {
            e.setAttribute(marginRight{doubleNF(s)});
        }}
    },

    {"margin",{true,
        [](Element &e, string s) {
            auto coords=parseQuadCoordinates(s);

            e.setAttribute(marginTop{std::get<0>(coords)});
            e.setAttribute(marginLeft{std::get<1>(coords)});
            e.setAttribute(marginBottom{std::get<2>(coords)});
            e.setAttribute(marginRight{std::get<3>(coords)});
        }}
    },

    {"paddingtop",{true,
        [](Element &e, string s) {
            e.setAttribute(paddingTop{doubleNF(s)});
        }}
    },

    {"paddingleft",{true,
        [](Element &e, string s) {
            e.setAttribute(paddingLeft{doubleNF(s)});
        }}
    },

    {"paddingbottom",{true,
        [](Element &e, string s) {
            e.setAttribute(paddingBottom{doubleNF(s)});
        }}
    },

    {"paddingright",{true,
        [](Element &e, string s) {
            e.setAttribute(paddingRight{doubleNF(s)});
        }}
    },

    {"padding",{true,
        [](Element &e, string s) {
            auto coords=parseQuadCoordinates(s);

            e.setAttribute(paddingTop{std::get<0>(coords)});
            e.setAttribute(paddingLeft{std::get<1>(coords)});
            e.setAttribute(paddingBottom{std::get<2>(coords)});
            e.setAttribute(paddingRight{std::get<3>(coords)});
        }}
    },

    {"borderstyle",{true,
        [](Element &e, string s) {
            e.setAttribute(borderStyle{s});
        }}
    },

    {"borderwidth",{true,
        [](Element &e, string s) {
            e.setAttribute(borderWidth{doubleNF(s)});
        }}
    },

    {"bordercolor",{true,
        [](Element &e, string s) {
            e.setAttribute(borderColor{colorNF(s)});
        }}
    },

    {"borderradius",{true,
        [](Element &e, string s) {
            e.setAttribute(borderRadius{s});
        }}
    },

    {"focusindex",{true,
        [](Element &e, string s) {
            e.setAttribute(focusIndex{s});
        }}
    },
    {"focus",{true,
        [](Element &e, string s) {
            e.setAttribute(focusIndex{s});
        }}
    },
    {"zindex",{true,
        [](Element &e, string s) {
            e.setAttribute(zIndex{s});
        }}
    },

    {"liststyletype",{true,
        [](Element &e, string s) {
            e.setAttribute(listStyleType{s});
        }}
    }};

/**
\internal
\brief the colorFactory is a static lookup map to translate the
textual color name to the 24bit rgb value.
color names from https://www.w3schools.com/colors/colors_names.asp
*/
const colorMap colorNF::colorFactory = {
    { "aliceblue", 0xF0F8FF },      { "antiquewhite", 0xFAEBD7 },   { "aqua", 0x00FFFF },
    { "aquamarine", 0x7FFFD4 },     { "azure", 0xF0FFFF },          { "beige", 0xF5F5DC },
    { "bisque", 0xFFE4C4 },         { "black", 0x000000 },          { "blanchedalmond", 0xFFEBCD },
    { "blue", 0x0000FF },           { "blueviolet", 0x8A2BE2 },     { "brown", 0xA52A2A },
    { "burlyWood", 0xDEB887 },      { "cadetblue", 0x5F9EA0 },      { "chartreuse", 0x7FFF00 },
    { "chocolate", 0xD2691E },      { "coral", 0xFF7F50 },          { "cornflowerblue", 0x6495ED },
    { "cornsilk", 0xFFF8DC },       { "crimson", 0xDC143C },        { "cyan", 0x00FFFF },
    { "darkblue", 0x00008B },       { "darkcyan", 0x008B8B },       { "darkgoldenrod", 0xB8860B },
    { "darkgray", 0xA9A9A9 },       { "darkgrey", 0xA9A9A9 },       { "darkgreen", 0x006400 },
    { "darkkhaki", 0xBDB76B },      { "darkmagenta", 0x8B008B },    { "darkolivegreen", 0x556B2F },
    { "darkorange", 0xFF8C00 },     { "darkorchid", 0x9932CC },     { "darkred", 0x8B0000 },
    { "darksalmon", 0xE9967A },     { "darkseagreen", 0x8FBC8F },   { "darkslateblue", 0x483D8B },
    { "darkslategray", 0x2F4F4F },  { "darkslategrey", 0x2F4F4F },  { "darkturquoise", 0x00CED1 },
    { "darkviolet", 0x9400D3 },     { "deeppink", 0xFF1493 },       { "deepskyblue", 0x00BFFF },
    { "dimgray", 0x696969 },        { "dimgrey", 0x696969 },        { "dodgerblue", 0x1E90FF },
    { "firebrick", 0xB22222 },      { "floralwhite", 0xFFFAF0 },    { "forestgreen", 0x228B22 },
    { "fuchsia", 0xFF00FF },        { "gainsboro", 0xDCDCDC },      { "ghostwhite", 0xF8F8FF },
    { "gold", 0xFFD700 },           { "goldenrod", 0xDAA520 },      { "gray", 0x808080 },
    { "grey", 0x808080 },           { "green", 0x008000 },          { "greenyellow", 0xADFF2F },
    { "honeydew", 0xF0FFF0 },       { "hotpink", 0xFF69B4 },        { "indianred", 0xCD5C5C },
    { "indigo", 0x4B0082 },         { "ivory", 0xFFFFF0 },          { "khaki", 0xF0E68C },
    { "lavender", 0xE6E6FA },       { "lavenderblush", 0xFFF0F5 },  { "lawngreen", 0x7CFC00 },
    { "lemonchiffon", 0xFFFACD },   { "lightblue", 0xADD8E6 },      { "lightcoral", 0xF08080 },
    { "lightcyan", 0xE0FFFF },      { "lightgoldenrodyellow", 0xFAFAD2 },
    { "lightgray", 0xD3D3D3 },      { "lightgrey", 0xD3D3D3 },      { "lightgreen", 0x90EE90 },
    { "lightpink", 0xFFB6C1 },      { "lightdalmon", 0xFFA07A },    { "lightseagreen", 0x20B2AA },
    { "lightskyblue", 0x87CEFA },   { "lightslategray", 0x778899 }, { "lightslategrey", 0x778899 },
    { "lightsteelblue", 0xB0C4DE }, { "lightyellow", 0xFFFFE0 },    { "lime", 0x00FF00 },
    { "limegreen", 0x32CD32 },      { "linen", 0xFAF0E6 },          { "magenta", 0xFF00FF },
    { "maroon", 0x800000 },         { "mediumaquamarine", 0x66CDAA },
    { "mediumblue", 0x0000CD },     { "mediumorchid", 0xBA55D3 },   { "mediumpurple", 0x9370DB },
    { "mediumseagreen", 0x3CB371 }, { "mediumslateblue", 0x7B68EE },{ "mediumspringgreen", 0x00FA9A },
    { "mediumturquoise", 0x48D1CC },{ "mediumvioletred", 0xC71585 },{ "midnightblue", 0x191970 },
    { "mintcream", 0xF5FFFA },      { "mistyrose", 0xFFE4E1 },      { "moccasin", 0xFFE4B5 },
    { "navajowhite", 0xFFDEAD },    { "navy", 0x000080 },           { "oldlace", 0xFDF5E6 },
    { "olive", 0x808000 },          { "olivedrab", 0x6B8E23 },      { "orange", 0xFFA500 },
    { "orangered", 0xFF4500 },      { "orchid", 0xDA70D6 },         { "palegoldenrod", 0xEEE8AA },
    { "palegreen", 0x98FB98 },      { "paleturquoise", 0xAFEEEE },  { "palevioletred", 0xDB7093 },
    { "papayawhip", 0xFFEFD5 },     { "peachpuff", 0xFFDAB9 },      { "peru", 0xCD853F },
    { "pink", 0xFFC0CB },           { "plum", 0xDDA0DD },           { "powderblue", 0xB0E0E6 },
    { "purple", 0x800080 },         { "rebeccapurple", 0x663399 },  { "red", 0xFF0000 },
    { "rosybrown", 0xBC8F8F },      { "royalblue", 0x4169E1 },      { "saddlebrown", 0x8B4513 },
    { "salmon", 0xFA8072 },         { "sandybrown", 0xF4A460 },     { "seagreen", 0x2E8B57 },
    { "seashell", 0xFFF5EE },       { "sienna", 0xA0522D },         { "silver", 0xC0C0C0 },
    { "skyblue", 0x87CEEB },        { "slateblue", 0x6A5ACD },      { "slategray", 0x708090 },
    { "slategrey", 0x708090 },      { "snow", 0xFFFAFA },           { "springgreen", 0x00FF7F },
    { "steelblue", 0x4682B4 },      { "tan", 0xD2B48C },            { "teal", 0x008080 },
    { "thistle", 0xD8BFD8 },        { "tomato", 0xFF6347 },         { "turquoise", 0x40E0D0 },
    { "violet", 0xEE82EE },         { "wheat", 0xF5DEB3 },          { "white", 0xFFFFFF },
    { "whitesmoke", 0xF5F5F5 },     { "yellow", 0xFFFF00 },         { "yellowgreen", 0x9ACD32 } };

// clang-format on

/**
\brief a constructor that takes a string and sets the options.
*/
viewManager::doubleNF::doubleNF(const string &sOption) {
  static unordered_map<string, u_int8_t> annotationMap = {
      {"px", numericFormat::px},
      {"pt", numericFormat::pt},
      {"em", numericFormat::em},
      {"percent", numericFormat::percent},
      {"pct", numericFormat::percent},
      {"%", numericFormat::percent},
      {"autocalculate", numericFormat::autoCalculate},
      {"auto", numericFormat::autoCalculate}};

  // default to auto calculate
  option = numericFormat::autoCalculate;
  std::regex r("[\\s,_]+");
  std::string sTmp = std::regex_replace(sOption, r, "");

  u_int8_t opt;
  tie(value, opt) = strToNumericAndEnum("doubleNF", annotationMap, sOption);
  option = static_cast<numericFormat>(opt);
}

/**
\brief The routine convert from the stored unit to pixel values. This is a
simple convertion using the ratio 1_em = 16px;
*/
double viewManager::doubleNF::toPx(void) {
  double dRet = 0.0;
  switch (option) {
  case numericFormat::em:
    dRet = 16.0 * value;
    break;
  case numericFormat::pt:
    dRet = 1.333 * value;
    break;
  case numericFormat::px:
    dRet = value;
    break;
  }

  return dRet;
}

/**
\brief The routine convert from the stored unit to point values. This is a
simple convertion using the ratio 1_em = 16px;
*/
double viewManager::doubleNF::toPt(void) {
  double dRet = 0.0;
  switch (option) {
  case numericFormat::em:
    dRet = value * 16.0 * .75;
    break;
  case numericFormat::pt:
    dRet = value;
    break;
  case numericFormat::px:
    dRet = value * .75;
    break;
  }

  return dRet;
  return dRet;
}
/**
\internal
\brief  a function that returns a tuple of the four coordinates specified in a
doubleNF object. this routine is used by the attributes that accept four at a
time, that is the short hand versions of coordinates, margin and padding
*/
tuple<doubleNF, doubleNF, doubleNF, doubleNF>
viewManager::parseQuadCoordinates(const string _sOptions) {
  regex re("^[\\s]*[\\{\\(]?([\\+\\-]?[\\d]+[.,]?[\\d]*[\\%]?[\\w]{0,7})"
           "(?:[\\s]*[,]?[\\s]*)([\\+\\-]?[\\d]+[.,]?[\\d]*[\\%]?[\\w]{0,7})"
           "(?:[\\s]*[,]?[\\s]*)([\\+\\-]?[\\d]+[.,]?[\\d]*[\\%]?[\\w]{0,7})"
           "(?:[\\s]*[,]?[\\s]*)([\\+\\-]?[\\d]+[.,]?[\\d]*[\\%]?[\\w]{0,7})"
           "(?:[\\s]*[,]?[\\s]*)[\\s]*[\\}\\)]?");
  smatch coords;

  if (regex_search(_sOptions, coords, re)) {
    if (coords.size() == 5) {
      auto ret =
          std::make_tuple(doubleNF(coords.str(1)), doubleNF(coords.str(2)),
                          doubleNF(coords.str(3)), doubleNF(coords.str(4)));
      return ret;
    }
  }

  std::string info = "Could not parse attribute string option : ";
  info += _sOptions;

  throw std::invalid_argument(info);
}

/**
\brief colorNF::colorIndex(const std::string &_colorName)
 The function accepts a name that may have spaces and can have camel case
 within the color name spelling. the function transforms the name and removes
 the spaces. It returns an iterator to the colorMap. This saves a find
 operation on the map when checking for the validity of a color name within
 the colorMap.
*/
colorMap::const_iterator colorNF::colorIndex(const std::string &_colorName) {
  std::regex r("\\s+");
  std::string sKey = std::regex_replace(_colorName, r, "");
  std::transform(sKey.begin(), sKey.end(), sKey.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  auto it = colorNF::colorFactory.find(sKey);

  return it;
}

/**
\brief The constructor provides a string lookup of a passed color name.
*/
viewManager::colorNF::colorNF(const string &_sOption) {
  option = colorFormat::name;
  auto it = colorIndex(_sOption);

  unsigned long color = 0;

  if (it != colorFactory.end())
    color = it->second;

  value[0] = static_cast<double>((color & 0xFF0000) >> 16);
  value[1] = static_cast<double>((color & 0x00FF00) >> 8);
  value[2] = static_cast<double>((color & 0x0000FF));
  value[3] = 1.0;
}

/**
\brief A constructor for creating the color object from a color name iterator.
 at times when the parser looks up a color name, this uses the iterator
which came from the name

\param colorMap::const_iterator it
*/
viewManager::colorNF::colorNF(colorMap::const_iterator it) {
  option = colorFormat::name;
  unsigned long color = it->second;

  value[0] = static_cast<double>((color & 0xFF0000) >> 16);
  value[1] = static_cast<double>((color & 0x00FF00) >> 8);
  value[2] = static_cast<double>((color & 0x0000FF));
  value[3] = 1.0;
}
/**
\brief create a colorNF object using a 24bit rgb value

\param const unsigned long &color
*/
viewManager::colorNF::colorNF(const unsigned long &color) {
  value[0] = static_cast<double>((color & 0xFF000000) >> 24);
  value[1] = static_cast<double>((color & 0x00FF0000) >> 16);
  value[2] = static_cast<double>((color & 0x0000FF00) >> 8);
  value[3] = 1.0;
}

/**
\brief rotates the color for a lighter shade

\param const double &step
*/
void viewManager::colorNF::lighter(const double &step) {}

/**
\brief rotates the color for a darker shade

\param const double &step
*/
void viewManager::colorNF::darker(const double &step) {}

/**
\brief creates a monochromatic shade of the color

\param const double &step - amount to wash 0 - 10, 10 being complete grey
*/
void viewManager::colorNF::monochromatic(const double &step) {}

/**
\brief hsl rotate 120
*/
void viewManager::colorNF::triad(void) { /*hsl rotate 120*/
}

/**
\brief hsl rotate -30
*/
void viewManager::colorNF::neutralCooler(void) { /* hsl rotate -30 */
}

/**
\brief hsl rotate 30
*/
void viewManager::colorNF::neutralWarmer(void) { /* hsl rotate 30 */
}

/**
\brief hsl rotate 180
*/
void viewManager::colorNF::complementary(void) {}

/**
\brief hsl rotate 150
*/
void viewManager::colorNF::splitComplements(void) { /*hsl rotate 150 */
}

/**
\internal
\brief strToEnum a function that accepts a unordered map of string and numeric
values. the function removes invalid characters and applies a toLower case
transform

\param const string_view &sListName
\param const unordered_map<string,uint8_t> &optionMap
\param const string &_sOption
*/
uint8_t viewManager::strToEnum(const string_view &sListName,
                               const unordered_map<string, uint8_t> &optionMap,
                               const string &_sOption) {
  uint8_t ret = 0;

  std::regex r("\\s+");
  std::string sTmpKey = std::regex_replace(_sOption, r, "");
  std::transform(sTmpKey.begin(), sTmpKey.end(), sTmpKey.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  auto it = optionMap.find(sTmpKey);

  if (it != optionMap.end()) {
    ret = it->second;
  } else {
    std::string info(sListName);
    info += " attribute string option not found: ";
    info += _sOption;

    throw std::invalid_argument(info);
  }
}

/**
\internal

\brief strToNumericAndEnum

returns: tuple<double, u_int8_t>

The routine provides a translation from a string format to a
c++ enumeration. The expected input type for the enumeration is a
uint8_t. The c++ compiler automatically translates the options
during the list initializer. However the output must be statically cast
back to the enumeration value.

*/
tuple<double, u_int8_t> viewManager::strToNumericAndEnum(
    const string_view &sListName,
    const unordered_map<string, uint8_t> &optionMap, const string &_sOption) {

  std::regex r("[\\s,_]+");
  std::string sTmp = std::regex_replace(_sOption, r, "");
  std::transform(sTmp.begin(), sTmp.end(), sTmp.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  char *pEnd;
  double dRet = 0;
  u_int8_t ui8Ret = 0;

  dRet = strtod(sTmp.data(), &pEnd);

  if (pEnd) {
    auto it = optionMap.find(string(pEnd));
    if (it != optionMap.end())
      ui8Ret = it->second;
  }

  return make_tuple(dRet, ui8Ret);
}

/**
\internal
\brief display(string sOption)
transforms the textual input into the display options
*/
viewManager::display::display(const string &sOption) {
  static unordered_map<string, uint8_t> enumMap = {
      {"inline", in_line}, {"block", block}, {"none", none}};
  value =
      static_cast<display::optionEnum>(strToEnum("display", enumMap, sOption));
}

/**
\internal
\brief position(string sOption)
transforms the textual input into the position options
*/
viewManager::position::position(const string &sOption) {
  static unordered_map<string, uint8_t> enumMap = {{"absolute", absolute},
                                                   {"relative", relative}};
  value = static_cast<position::optionEnum>(
      strToEnum("position", enumMap, sOption));
}

/**
\internal
\brief textAlignment(string sOption)
 transforms the textual input into the textAlignment options
 */
viewManager::textAlignment::textAlignment(const string &sOption) {
  static unordered_map<string, uint8_t> enumMap = {{"left", left},
                                                   {"center", center},
                                                   {"right", right},
                                                   {"justified", justified}};
  value = static_cast<textAlignment::optionEnum>(
      strToEnum("textAlignment", enumMap, sOption));
}

/**
\internal
\brief lineHeight(string sOption)
transforms the textual input into the lineHeight options
*/
viewManager::lineHeight::lineHeight(const string &sOption) {
  static unordered_map<string, uint8_t> enumMap = {{"normal", normal},
                                                   {"numeric", numeric}};
  u_int8_t opt;
  tie(value, opt) = strToNumericAndEnum("lineHeight", enumMap, sOption);
  option = static_cast<lineHeight::optionEnum>(opt);
}

/**
\brief lineHeight(string sOption)
transforms the textual input into the lineHeight options
*/
viewManager::borderStyle::borderStyle(const string &sOption) {
  static unordered_map<string, uint8_t> enumMap = {
      {"none", none},   {"dotted", dotted},   {"dashed", dashed},
      {"solid", solid}, {"doubled", doubled}, {"groove", groove},
      {"ridge", ridge}, {"inset", inset},     {"outset", outset}};
  value = static_cast<borderStyle::optionEnum>(
      strToEnum("borderStyle", enumMap, sOption));
}

/**
\internal
\brief listStyleType
transforms the string input to the list of options
\param const string &_sOption is the option to translate
*/
viewManager::listStyleType::listStyleType(const string &sOption) {
  static unordered_map<string, uint8_t> enumMap = {
      {"none", none},     {"disc", disc},       {"circle", circle},
      {"square", square}, {"decimal", decimal}, {"alpha", alpha},
      {"greek", greek},   {"latin", latin},     {"roman", roman}};
  value = static_cast<listStyleType::optionEnum>(
      strToEnum("listStyleType", enumMap, sOption));
}

/**
\internal
\class Viewer
\brief
This is the viewing apparatus of the document object model. Within the
codebase, the platform object is allocated once per viewer object. The
platform object contains the implementation of the message queue present on
most message based graphics interfaces. That is the entry point for windows
message queue and the x windows message polling routine. These routines simply
create event objects and dispatch them to the element that has applicable
listeners attached.
*/

/**
\brief the viewer constructor opens a window and establishes a root document
object.
*/
viewManager::Viewer::Viewer(const vector<any> &attrs)
    : Element("Viewer", attrs) {
  setAttribute(indexBy{"_root"});

  documentState st;
  st.focusField = this;
  setAttribute<documentState>(st);
}

/**
/**
\internal
\brief deconstructor for the view manager object.
*/
viewManager::Viewer::~Viewer() {}

/**
  \internal
  \brief The function is a recursive one that calculates the
  items that could not be resolved previously. At the completetion
  of this functionality, all items that appear within the viewport
  should be calculated.

*/

/**
\brief The routine processes the list of elements such that the layout
and units are all expressed within the model as pixel units. After this
function is ran, each element will have a rectangle attached that expresses
it's pixel size on the viewing device.
*/
void viewManager::Viewer::computeLayout(Element &e) {
}

/**
\internal
\brief main entry point for the rendering subsystem. The head of
the recursive process.
*/
void viewManager::Viewer::render(void) {
  computeLayout(*this);

  /* the display list is a sorted entity providing a searchable list
  for the beginning and ending of a viewport clipping region. */
  for (auto n : m_displayList) {
    n->ptr->render(*m_device.get());
  }
}

/**
\internal
\brief
This is the only entry point from the platform for the event
dispatching system. The routine expects only certain types
of messages from the platform. The other events, that are computed,
are developed by this routine as needed. Each of these events, whether
passed through as the same message, or developed is placed into the
viewManager message queue. The background event dispatching fetches
messages from this queue, and calls the element's event processor
routines. The main thing to remember is that the information is
processed from a queue and using a background thread.
*/
void viewManager::Viewer::dispatchEvent(const event &evt) {
  switch (evt.evtType) {
  case eventType::paint:
    m_device->clear();
    render();
    m_device->flip();
    break;
  case eventType::resize:
    setAttribute<objectWidth>(
        {static_cast<double>(evt.width), numericFormat::px});
    setAttribute<objectHeight>(
        {static_cast<double>(evt.height), numericFormat::px});
    m_device->resize(evt.width, evt.height);
    break;
  case eventType::keydown: {
    auto &state = getAttribute<documentState>();
    state.focusField->dispatch(evt);
    dispatchEvent(event{eventType::paint});
  } break;
  case eventType::keyup: {
    auto &state = getAttribute<documentState>();
    state.focusField->dispatch(evt);
    dispatchEvent(event{eventType::paint});
  } break;
  case eventType::keypress: {
    auto &state = getAttribute<documentState>();
    state.focusField->dispatch(evt);
    dispatchEvent(event{eventType::paint});
  } break;
  case eventType::mousemove:
    break;
  case eventType::mousedown:
    break;
  case eventType::mouseup:
    if (evt.mouseButton == 1)
      m_device->fontScale++;
    else
      m_device->fontScale--;
    dispatchEvent(event{eventType::paint});
    break;
  case eventType::wheel:
    if (evt.wheelDistance > 0)
      m_device->fontScale += 1;
    else
      m_device->fontScale -= 1;
    dispatchEvent(event{eventType::paint});
    break;
  }
/* these events do not come from the platform. However,
they are spawned from conditions based upon the platform events.
*/
#if 0
eventType::focus
eventType::blur
eventType::mouseenter
eventType::click
eventType::dblclick
eventType::contextmenu
eventType::mouseleave
#endif
}
/**
\internal
\brief The entry point that processes messages from the operating
system application level services. Typically on Linux this is a
coupling of xcb and keysyms library for keyboard. Previous
incarnations of technology such as this typically used xserver.
However, XCB is the newer form. Primarily looking at the code of such
programs as vlc, the routine simply places pixels into the memory
buffer. while on windows the direct x library is used in combination
with windows message queue processing.
*/
void viewManager::Viewer::processEvents(void) {
  // setup the event dispatcher
  eventHandler ev =
      std::bind(&Viewer::dispatchEvent, this, std::placeholders::_1);
  m_device = std::make_unique<Visualizer::platform>(
      ev, getAttribute<objectWidth>().value,
      getAttribute<objectHeight>().value);

  m_device->openWindow(getAttribute<windowTitle>().value);

  m_device->messageLoop();
}

/**
\addtogroup udl User Defined Literals

User defined liters are created for the project to consolidate parameter
input.

When more information would be required in a C++ constructor creation, the
syntax provides the returning of the numerical format object in an easy to
read syntax,

For example:
    getElement("testDiv").setAttribute<objectTop>(10_px);

rather than
    getElement("testDiv").setAttribute<objectTop>(10, numericFormat::px);

@{
*/

/**
\brief enables labeling numeric literals as _pt. The operator returns a
doubleNF object.
*/
auto viewManager::operator""_pt(unsigned long long int value) -> doubleNF {
  return doubleNF{static_cast<double>(value), numericFormat::pt};
}

/**
\brief enables labeling numeric literals as _pt. The operator returns a
doubleNF object.
*/
auto viewManager::operator""_pt(long double value) -> doubleNF {
  return doubleNF{static_cast<double>(value), numericFormat::pt};
}

/**
\brief enables labeling numeric literals as _em. The operator returns a
doubleNF object.
*/
auto viewManager::operator""_em(unsigned long long int value) -> doubleNF {
  return doubleNF{static_cast<double>(value), numericFormat::em};
}

/**
 \brief enables labeling numeric literals as _em. The operator returns a
 doubleNF object.
*/
auto viewManager::operator""_em(long double value) -> doubleNF {
  return doubleNF{static_cast<double>(value), numericFormat::em};
}

/**
\brief enables labeling numeric literals as _px. The operator returns a
doubleNF object.
*/
auto viewManager::operator""_px(unsigned long long int value) -> doubleNF {
  return doubleNF{static_cast<double>(value), numericFormat::px};
}

/**
\brief enables labeling numeric literals as _px. The operator returns a
doubleNF object.
*/
auto viewManager::operator""_px(long double value) -> doubleNF {
  return doubleNF{static_cast<double>(value), numericFormat::px};
}

/**
\brief enables labeling numeric literals as _percent. The operator returns a
doubleNF object.
*/
auto viewManager::operator""_percent(unsigned long long int value) -> doubleNF {
  return doubleNF{static_cast<double>(value), numericFormat::percent};
}

/**
\brief enables labeling numeric literals as _percent. The operator returns a
doubleNF object.
*/
auto viewManager::operator""_percent(long double value) -> doubleNF {
  return doubleNF{static_cast<double>(value), numericFormat::percent};
}

/**
\brief enables labeling numeric literals as _pct. The operator returns a
doubleNF object.
*/
auto viewManager::operator""_pct(unsigned long long int value) -> doubleNF {
  return doubleNF{static_cast<double>(value), numericFormat::percent};
}

/**
\brief enables labeling numeric literals as _pct. The operator returns a
doubleNF object.
*/
auto viewManager::operator""_pct(long double value) -> doubleNF {
  return doubleNF{static_cast<double>(value), numericFormat::percent};
}

/**
\brief enables labeling numeric literals as _normal. The operator returns a
doubleNF object.
*/
auto viewManager::operator""_normal(unsigned long long int value)
    -> lineHeight {
  return lineHeight{static_cast<double>(value), lineHeight::normal};
}

/**
\brief enables labeling numeric literals as _normal. The operator returns a
doubleNF object.
*/
auto viewManager::operator""_normal(long double value) -> lineHeight {
  return lineHeight{static_cast<double>(value), lineHeight::normal};
}

/**
\brief enables labeling numeric literals as _numeric. The operator returns a
doubleNF object.
*/
auto viewManager::operator""_numeric(unsigned long long int value)
    -> lineHeight {
  return lineHeight{static_cast<double>(value), lineHeight::numeric};
}

/**
\brief enables labeling numeric literals as _numeric. The operator returns a
doubleNF object.
*/
auto viewManager::operator""_numeric(long double value) -> lineHeight {
  return lineHeight{static_cast<double>(value), lineHeight::numeric};
}
/** @}*/

/**
  \addtogroup API Global Document API
  @{
*/

/**
\brief given the string id, the function returns
the element.

jquery shows that handling large document models can be
effectively managed using searching and iterators. Here,
elements or groups of elements can be accessed through query strings.
#, or *, or partial matches. Change attributes?
@ for style,

*/
auto viewManager::query(const std::string &queryString) -> ElementList {
  ElementList results;
  if (queryString == "*") {
    for (const auto &n : elements) {
      results.push_back(std::ref(*(n.second.get())));
    }
  } else {
    std::regex matchExpression(queryString.data(),
                               std::regex_constants::ECMAScript |
                                   std::regex_constants::icase);
    for (const auto &n : elements) {
      if (std::regex_match(n.second->getAttribute<indexBy>().value.data(),
                           matchExpression))
        results.push_back(std::ref(*(n.second.get())));
    }
  }
  return results;
}

/**
\brief This version of the query interface provides a
syntax whereby a lambda or a function may be used to provide matching.
The function is simply passed an element within the traversal.
The function is expected to return a true or false value.
*/
auto viewManager::query(const ElementQuery &queryFunction) -> ElementList {
  ElementList results;
  for (const auto &n : elements) {
    if (queryFunction(std::ref(*(n.second.get()))))
      results.push_back(std::ref(*(n.second.get())));
  }
  return results;
}

/**
\brief The hasElement function returns a true or false value if the
index is found within the index. This may be used to avoid possible
exceptions.
*/
bool viewManager::hasElement(const std::string &key) {
  auto it = indexedElements.find(key);
  return it != indexedElements.end();
}
/** @}*/

Element::iterator &Element::iterator::operator=(Element *pNode) {
  this->m_pCurrentNode = pNode;
  return *this;
}

// Prefix ++ overload
Element::iterator &Element::iterator::operator++() {
  if (m_pCurrentNode)
    m_pCurrentNode = m_pCurrentNode->m_nextSibling;
  return *this;
}

// Postfix ++ overload
Element::iterator Element::iterator::operator++(int) {
  iterator it = *this;
  ++*this;
  return it;
}

// Prefix ++ overload
Element::iterator &Element::iterator::operator--() {
  if (m_pCurrentNode)
    m_pCurrentNode = m_pCurrentNode->m_previousSibling;
  return *this;
}

bool Element::iterator::operator!=(const Element::iterator &it) {
  return m_pCurrentNode != it.m_pCurrentNode;
}

Element &Element::iterator::operator*() { return *m_pCurrentNode; }

Element::iterator Element::iterator::begin() {
  return Element::iterator(m_pCurrentNode->m_firstChild);
}

Element::iterator Element::iterator::end() {
  return Element::iterator(nullptr);
}

/**
\internal
\brief copy constructor
*/
viewManager::Element::Element(const Element &other) {

  m_self = other.m_self;
  m_parent = other.m_parent;
  m_firstChild = other.m_firstChild;
  m_lastChild = other.m_lastChild;
  m_nextChild = other.m_nextChild;
  m_previousChild = other.m_previousChild;
  m_nextSibling = other.m_nextSibling;
  m_previousSibling = other.m_previousSibling;
  m_childCount = other.m_childCount;
  attributes = other.attributes;
  styles = other.styles;
}

/**
\internal
\brief move constructor
*/
viewManager::Element::Element(Element &&other) noexcept {

  m_self = other.m_self;
  m_parent = other.m_parent;
  m_firstChild = other.m_firstChild;
  m_lastChild = other.m_lastChild;
  m_nextChild = other.m_nextChild;
  m_previousChild = other.m_previousChild;
  m_nextSibling = other.m_nextSibling;
  m_previousSibling = other.m_previousSibling;
  m_childCount = other.m_childCount;
  attributes = std::move(other.attributes);
  styles = std::move(other.styles);
}

/**
\internal
\brief copy assignment operator
*/
Element &viewManager::Element::operator=(const Element &other) {

  // Self-assignment detection
  if (&other == this)
    return *this;
  m_self = other.m_self;
  m_parent = other.m_parent;
  m_firstChild = other.m_firstChild;
  m_lastChild = other.m_lastChild;
  m_nextChild = other.m_nextChild;
  m_previousChild = other.m_previousChild;
  m_nextSibling = other.m_nextSibling;
  m_previousSibling = other.m_previousSibling;
  m_childCount = other.m_childCount;
  attributes = other.attributes;
  styles = other.styles;
  return *this;
}

/**
\internal
\brief move assignment operator
*/
Element &viewManager::Element::operator=(Element &&other) noexcept {

  if (&other == this)
    return *this;
  m_self = other.m_self;
  m_parent = other.m_parent;
  m_firstChild = other.m_firstChild;
  m_lastChild = other.m_lastChild;
  m_nextChild = other.m_nextChild;
  m_previousChild = other.m_previousChild;
  m_nextSibling = other.m_nextSibling;
  m_previousSibling = other.m_previousSibling;
  m_childCount = other.m_childCount;
  attributes = std::move(other.attributes);
  styles = std::move(other.styles);
  return *this;
}

/**
  \brief
  The function will parse the string as input searching for document tags.
  These elements are added as children of the element for which the function
  is invoked.

  \param sMarkup a std::string containing the markup.
  \return Element& returns the referenced element for continuation syntax.

  Example
  -------
  \snippet examples.cpp appendChild_markup

  \ref markupInputFormat

*/
auto viewManager::Element::appendChild(const std::string &sMarkup)
    -> Element & {
  return (ingestMarkup(*this, sMarkup));
}

/**
  \brief The function will append the given document element within
  the parameter as a child.

  \param newChild a new child element that was previously created.
  \return Element& returns the referenced element for continuation syntax.

  Example
  -------
  \snippet examples.cpp appendChild_element
*/
auto viewManager::Element::appendChild(Element &newChild) -> Element & {
  newChild.m_parent = this;
  newChild.m_previousSibling = m_lastChild;

  if (!m_firstChild)
    m_firstChild = newChild.m_self;

  if (m_lastChild)
    m_lastChild->m_nextSibling = newChild.m_self;

  m_lastChild = newChild.m_self;
  m_childCount++;

  return (newChild);
}

/**
  \brief The function will append the given document elements within
  the ElementList parameter as children.

  \param elementCollection an ElementList of new child element that was
  previously created.

  \return Element& returns the referenced element for continuation syntax.

  Example
  -------
  \snippet examples.cpp appendChild_elementlist
*/
auto viewManager::Element::appendChild(const ElementList &elementCollection)
    -> Element & {
  for (auto e : elementCollection) {
    appendChild(e.get());
  }
  return (*this);
}

/**
  \brief The function will append the given markup content as a sibling.

  \param elementCollection an ElementList of new child element that was
  previously created.

  \return Element& returns the referenced element for continuation syntax.

  Example
  -------
  \snippet examples.cpp append_markup

  \ref markupInputFormat


*/
auto viewManager::Element::append(const std::string &sMarkup) -> Element & {
  Element *base = this->m_parent;
  if (base == nullptr)
    base = this;
  return (ingestMarkup(*base, sMarkup));
}

/**
  \brief The function will append the given element as a sibling.

  \return Element& returns the referenced element for continuation syntax.

  Example
  -------
  \snippet examples.cpp append_element

*/
auto viewManager::Element::append(Element &sibling) -> Element & {
  m_nextSibling = sibling.m_self;
  sibling.m_parent = this->m_parent;
  sibling.m_previousSibling = this;

  if (!this->m_parent->m_firstChild)
    this->m_parent->m_firstChild = sibling.m_self;

  this->m_parent->m_lastChild = sibling.m_self;

  this->m_parent->m_childCount++;
  return (sibling);
}

/**
  \brief The function will append the collection of elements as a
  siblings.

  \param elementCollection an ElementList of new child element that was
  previously created.

  \return Element& returns the referenced element for continuation syntax.

  Example
  -------
  \snippet examples.cpp append_elementlist
*/
auto viewManager::Element::append(ElementList &elementCollection) -> Element & {
  for (auto &e : elementCollection)
    append(e);
  return (*this);
}

/**
\brief The function sets the given attribute inside the elements indexed
map. Settings are filtered on specific types to determine if it is a true
attribute or one that is filtered to be a compound. Compound attributes
require other operations such as data insertion into the data property or
using an official attribute object where only an enumeration value is given.

\param
setting an attribute.

The following are supported filtered types:
- char
- double
- float
- int
- std::string
- const char *
- std::vector<char>
- std::vector<double>
- std::vector<float>
- std::vector<int>
- std::vector<std::string>
- std::vector<std::vector<std::string>>
- std::vector<std::vector<std::pair<int, std::string>>>
- std::vector<std::vector<std::pair<int, std::string>>>

Example
-------
\snippet examples.cpp setAttribute_base

*/
Element &viewManager::Element::setAttribute(const std::any &paramSetting) {

  std::any setting = paramSetting;
  /**
  \internal
  \enum _enumTypeFilter
  */
  enum _enumTypeFilter {
    dt_char,
    dt_double,
    dt_float,
    dt_int,
    dt_std_string,
    dt_const_char,
    dt_vector_char,
    dt_vector_double,
    dt_vector_float,
    dt_vector_int,
    dt_vector_string,
    dt_vector_vector_string,
    dt_vector_pair_int_string,
    dt_indexBy,
    dt_display_enum,
    dt_position_enum,
    dt_textAlignment_enum,
    dt_borderStyle_enum,
    dt_listStyleType_enum,

    dt_nonFiltered
  };
  // filter map
  static std::unordered_map<size_t, _enumTypeFilter> _umapTypeFilter = {
      {std::type_index(typeid(char)).hash_code(), dt_char},
      {std::type_index(typeid(double)).hash_code(), dt_double},
      {std::type_index(typeid(float)).hash_code(), dt_float},
      {std::type_index(typeid(int)).hash_code(), dt_int},
      {std::type_index(typeid(std::string)).hash_code(), dt_std_string},
      {std::type_index(typeid(const char *)).hash_code(), dt_const_char},
      {std::type_index(typeid(std::vector<char>)).hash_code(), dt_vector_char},
      {std::type_index(typeid(std::vector<double>)).hash_code(),
       dt_vector_double},
      {std::type_index(typeid(std::vector<float>)).hash_code(),
       dt_vector_float},
      {std::type_index(typeid(std::vector<int>)).hash_code(), dt_vector_int},
      {std::type_index(typeid(std::vector<std::string>)).hash_code(),
       dt_vector_string},
      {std::type_index(typeid(std::vector<std::vector<std::string>>))
           .hash_code(),
       dt_vector_vector_string},
      {std::type_index(
           typeid(std::vector<std::vector<std::pair<int, std::string>>>))
           .hash_code(),
       dt_vector_pair_int_string},
      {std::type_index(typeid(indexBy)).hash_code(), dt_indexBy},
      {std::type_index(typeid(display::optionEnum)).hash_code(),
       dt_display_enum},
      {std::type_index(typeid(position::optionEnum)).hash_code(),
       dt_position_enum},
      {std::type_index(typeid(textAlignment::optionEnum)).hash_code(),
       dt_textAlignment_enum},
      {std::type_index(typeid(borderStyle::optionEnum)).hash_code(),
       dt_borderStyle_enum},
      {std::type_index(typeid(listStyleType::optionEnum)).hash_code(),
       dt_listStyleType_enum}

  };
  // set search result defaults for not found in filter
  _enumTypeFilter dtFilter = dt_nonFiltered;
  bool bSaveInMap = false;
  auto it = _umapTypeFilter.find(setting.type().hash_code());
  if (it != _umapTypeFilter.end())
    dtFilter = it->second;

  /* filter these types specifically and do not store them in the map.
  these items change the dataAdaptor. This creates a more usable
  syntax for population of large and small data within the
  simple initializer list format given within the attribute list.*/
  switch (dtFilter) {
  case dt_char: {
    auto v = std::any_cast<char>(setting);
    data<char>() = std::vector<char>{v};
  } break;
  case dt_double: {
    auto v = std::any_cast<double>(setting);
    data<double>() = std::vector<double>{v};
  } break;
  case dt_float: {
    auto v = std::any_cast<float>(setting);
    data<float>() = std::vector<float>{v};
  } break;
  case dt_int: {
    auto v = std::any_cast<int>(setting);
    data<int>() = std::vector<int>{v};
  } break;
  case dt_const_char: {
    auto v = std::any_cast<const char *>(setting);
    data<std::string>() = std::vector<std::string>{v};
  } break;
  case dt_std_string: {
    auto v = std::any_cast<std::string>(setting);
    data<std::string>() = std::vector<std::string>{v};
  } break;
  case dt_vector_char: {
    auto v = std::any_cast<std::vector<char>>(setting);
    data<char>() = v;
  } break;
  case dt_vector_double: {
    auto v = std::any_cast<std::vector<double>>(setting);
    data<double>() = v;
  } break;
  case dt_vector_float: {
    auto v = std::any_cast<std::vector<float>>(setting);
    data<float>() = v;
  } break;
  case dt_vector_int: {
    auto v = std::any_cast<std::vector<int>>(setting);
    data<int>() = v;
  } break;
  case dt_vector_string: {
    auto v = std::any_cast<std::vector<std::string>>(setting);
    data<std::string>() = v;
  } break;
  case dt_vector_vector_string: {
    auto v = std::any_cast<std::vector<std::vector<std::string>>>(setting);
    data<std::vector<std::string>>() = v;
  } break;
  case dt_vector_pair_int_string: {
    auto v = std::any_cast<std::vector<std::pair<int, std::string>>>(setting);
    data<std::pair<int, std::string>>() = v;
  } break;
  // attributes stored in map but filtered for processing.
  case dt_indexBy: {
    updateIndexBy(std::any_cast<indexBy>(setting));
    bSaveInMap = true;
  } break;
  case dt_display_enum: {
    setting = display{std::any_cast<display::optionEnum>(paramSetting)};
    bSaveInMap = true;
  } break;
  case dt_position_enum: {
    setting = position{std::any_cast<position::optionEnum>(paramSetting)};
    bSaveInMap = true;
  } break;
  case dt_textAlignment_enum: {
    setting =
        textAlignment{std::any_cast<textAlignment::optionEnum>(paramSetting)};
    bSaveInMap = true;
  } break;
  case dt_borderStyle_enum: {
    setting = borderStyle{std::any_cast<borderStyle::optionEnum>(paramSetting)};
    bSaveInMap = true;
  } break;
  case dt_listStyleType_enum: {
    setting =
        listStyleType{std::any_cast<listStyleType::optionEnum>(paramSetting)};
    bSaveInMap = true;
  } break;

  // other items are not filtered, so just pass through to storage.
  case dt_nonFiltered: {
    bSaveInMap = true;
  } break;
  }

  if (bSaveInMap)
    attributes[std::type_index(setting.type())] = setting;
  return *this;
}

/**
\internal
\brief The attribute being set can be contained in an array of std::any
Typically the caller does not use this function but relies on the
varodic template version.
*/
Element &
viewManager::Element::setAttribute(const std::vector<std::any> &attribs) {
  for (auto n : attribs)
    setAttribute(n);
  return *this;
}

/**
\internal

\brief updates the id within the index if the item has changed.

*/
void viewManager::Element::updateIndexBy(const indexBy &setting) {
  // changing id just changes
  // the key in elementById
  // map
  std::string oldKey = "";
  const std::string &newKey = setting.value;
  auto it = attributes.find(std::type_index(typeid(indexBy)));

  // get the key of the old id
  if (it != attributes.end()) {
    oldKey = std::any_cast<indexBy>(it->second).value;
  }

  // case a. key is not blank,
  // yet it is the same value
  // as the old key therefore
  // there is no change.
  if (!oldKey.empty() && oldKey == newKey) {
    return;
    // case b. remap just the
    // key
  } else if (!oldKey.empty() && !newKey.empty()) {
    auto nodeHandler = indexedElements.extract(oldKey);
    nodeHandler.key() = newKey;
    indexedElements.insert(std::move(nodeHandler));
    // case c. remove key from
    // map
  } else if (!oldKey.empty() && newKey.empty()) {
    indexedElements.erase(oldKey);
    // case d. did not exist
    // before, add key to map
  } else if (!newKey.empty()) {
    indexedElements.insert({newKey, std::ref(*this)});
  }
  return;
}

/**
\brief inserts the given element before the named second parameter.
The version of the function is useful when the element is indexed by a
string and a reference to it does not exist.

\param Element &newChild

\param std::string sID

Example
-------
\snippet examples.cpp insertBefore_string
*/
auto viewManager::Element::insertBefore(Element &newChild, std::string &sID)
    -> Element & {
  return insertBefore(newChild, getElement(sID));
}

/**
\brief inserts the given element before the named second parameter.

\param Element &newChild

\param Element &existingElement

Example
-------
\snippet examples.cpp insertBefore
*/
auto viewManager::Element::insertBefore(Element &newChild,
                                        Element &existingElement) -> Element & {
  Element &child = newChild;
  // maintain tree structure
  child.m_parent = existingElement.m_parent;
  child.m_nextSibling = existingElement.m_self;
  child.m_previousSibling = existingElement.m_previousSibling;
  existingElement.m_previousSibling = child.m_self;
  // provide linkage
  if (child.m_previousSibling)
    child.m_previousSibling->m_nextSibling = child.m_self;
  if (child.m_nextSibling)
    child.m_nextSibling->m_previousSibling = child.m_self;
  // case where insert is at the first
  if (existingElement.m_self == m_firstChild) {
    m_firstChild = child.m_self;
  }
  m_childCount++;
  return child;
}

/**
\brief inserts the given element after the named second parameter element.
The version of the function is useful when the element is indexed by a
string and a reference to it does not exist.

\param Element &newChild

\param std::string sID

Example
-------
\snippet examples.cpp insertAfter_string
*/
auto viewManager::Element::insertAfter(Element &newChild, std::string &sID)
    -> Element & {
  return insertAfter(newChild, getElement(sID));
}

/**
\brief inserts the given element after the named second parameter element.

\param Element &newChild

\param Element &existingElement

Example
-------
\snippet examples.cpp insertAfter
*/
auto viewManager::Element::insertAfter(Element &newChild,
                                       Element &existingElement) -> Element & {

  // maintain tree structure
  newChild.m_parent = existingElement.m_parent;
  newChild.m_nextSibling = existingElement.m_previousSibling;
  newChild.m_previousSibling = existingElement.m_self;
  if (existingElement.m_nextSibling)
    existingElement.m_nextSibling->m_previousSibling = newChild.m_self;

  existingElement.m_nextSibling = newChild.m_self;

  // case where insert is at the end
  if (existingElement.m_self == m_lastChild) {
    m_lastChild = newChild.m_self;
  }
  m_childCount++;
  return newChild;
}

/**
\brief replaces the child with the new one specified.
\details The function replaces the reference child with the new one
selected. The ne child should be within the first parameter while the second
parameter should contain an existing child. When the oldChild is replaced,
it is removed from the indexBy list and its memory is freed.

\param Element& newChild a newly created child.
\param std::string& sID an existing child that is to be replaced.

Example
-------
\snippet examples.cpp replaceChild_string
*/
auto viewManager::Element::replaceChild(Element &newChild, std::string &sID)
    -> Element & {
  return replaceChild(newChild, getElement(sID));
}

/**
\brief replaces the child with the new one specified.
\details The function replaces the reference child with the new one
selected. The new child should be within the first parameter while the
second parameter should contain an existing child. When the oldChild is
replaced, it is removed from the indexBy list and its memory is freed.

\param Element& newChild a newly created child.
\param Element& oldChild an existing child that is to be replaced.

Example
-------
\snippet examples.cpp replaceChild
*/
auto viewManager::Element::replaceChild(Element &newChild, Element &oldChild)
    -> Element & {

  // unattach the old one and insert the new one
  if (oldChild.m_parent->m_firstChild == oldChild.m_self)
    oldChild.m_parent->m_firstChild = newChild.m_self;

  if (oldChild.m_parent->m_lastChild == oldChild.m_self)
    oldChild.m_parent->m_lastChild = newChild.m_self;

  if (oldChild.m_previousSibling)
    oldChild.m_previousSibling->m_nextSibling = newChild.m_self;

  if (oldChild.m_nextSibling)
    oldChild.m_nextSibling->m_previousSibling = newChild.m_self;

  newChild.m_parent = oldChild.m_parent;

  // remove reference from string id indexed list
  try {
    indexedElements.erase(oldChild.getAttribute<indexBy>().value);

  } catch (const std::exception &e) {
    // std::cout << " Exception: " << e.what() << "\n";
  }

  // remove the element smart pointer
  auto it = elements.find((std::size_t)oldChild.m_self);
  if (it != elements.end())
    elements.erase(it);

  return *this;
}

/**
\brief moves the element to the specified location.
\details The method provides a shortened call to move both coordinates
at the same time. The objectTop and objectLeft are set. The method accepts
numerical values and only sets the value of the attribute. It does not
change the numerical format of the underlying attribute values.

Example
-------
\snippet examples.cpp move
*/
auto viewManager::Element::move(const double t, const double l) -> Element & {
  getAttribute<objectTop>().value = t;
  getAttribute<objectLeft>().value = l;
  return *this;
}

/**
\brief resizes the element
\details The method provides a shortened call to resize an element.
The objectWidth and objectHeight are set at the same time. The method
accepts numerical values and only sets the value of the attribute. It does
not change the numerical format of the underlying attribute values.

Example
-------
\snippet examples.cpp resize
*/
auto viewManager::Element::resize(const double w, const double h) -> Element & {
  getAttribute<objectWidth>().value = w;
  getAttribute<objectHeight>().value = h;
  return *this;
}

/**
\brief removes the element from the document tree and free the memory
associated.

\details The remove method provides an easy method to delete an
object from the document hierarchy. The method does not provide continuation
syntax as after the call is complete, all memory associated with the object
will be freed. The indexBy list is also modified to update the change.

Example
-------
\snippet examples.cpp remove
*/
void viewManager::Element::remove(void) {
  // recursively remove all children
  removeChildren();

  // update tree linkage
  if (m_parent && m_parent->m_firstChild == m_self)
    m_parent->m_firstChild = m_nextSibling;

  if (m_parent && m_parent->m_lastChild == m_self)
    m_parent->m_lastChild = m_previousSibling;

  if (m_nextSibling)
    m_nextSibling->m_previousSibling = m_previousSibling;

  if (m_previousSibling)
    m_previousSibling->m_nextSibling = m_nextSibling;

  // remove reference from string id indexed list
  try {
    indexedElements.erase(getAttribute<indexBy>().value);

  } catch (const std::exception &e) {
    // std::cout << " Exception: " << e.what() << "\n";
  }

  // free smart pointer
  auto it = elements.find((std::size_t)m_self);
  if (it != elements.end())
    elements.erase(it);

  return;
}

/**
\brief removes a child element from the list and free the associated memory.
\param std::string& isID is an existing child of the referenced element to
remove.

\details The removeChild destroys an existing child element of a document
tree. After the function completes, all associated reference within the
system will be discontinued. This includes the smart pointer and the indexBy
list.

\exception std::invalid_argument may be thrown if the element is not found
by the given id or the referenced element is not a child.

Example
-------
\snippet examples.cpp removeChild_string
*/
auto viewManager::Element::removeChild(std::string &sID) -> Element & {
  return removeChild(getElement(sID));
}

/**
\brief removes a child element from the list and free the associated memory.
\param Element& oldChild is an existing child of the referenced element to
remove.

\details The removeChild destroys an existing child element of a document
tree. After the function completes, all associated reference within the
system will be discontinued. This includes the smart pointer and the indexBy
list.

\exception std::invalid_argument may be thrown if the element is not a
child. Example
-------
\snippet examples.cpp removeChild
*/
auto viewManager::Element::removeChild(Element &oldChild) -> Element & {
  // only remove children that are attached to the object
  if (oldChild.m_parent != m_self) {
    std::string info = "Referenced element is not a child.";
    throw std::invalid_argument(info);
  }

  // recursively remove children
  auto pItem = oldChild.m_firstChild;
  while (pItem) {
    pItem->removeChild(*pItem);
    pItem = pItem->m_nextSibling;
  }

  // modify tree linkage
  if (m_firstChild == oldChild.m_self) {
    m_firstChild = oldChild.m_nextSibling;
  }

  if (m_lastChild == oldChild.m_self) {
    m_lastChild = oldChild.m_previousSibling;
  }

  if (oldChild.m_previousSibling)
    oldChild.m_previousSibling->m_nextSibling = oldChild.m_nextSibling;

  if (oldChild.m_nextSibling)
    oldChild.m_nextSibling->m_previousSibling = oldChild.m_previousSibling;

  // update string index list
  try {
    indexedElements.erase(oldChild.getAttribute<indexBy>().value);

  } catch (const std::exception &e) {
    // std::cout << " Exception: " << e.what() << "\n";
  }

  // free memory
  auto it = elements.find((std::size_t)oldChild.m_self);
  if (it != elements.end())
    elements.erase(it);

  m_childCount--;
  return *this;
}

/**
\brief removes all children from the document tree associated with the given
element and free the memory.
\details The removeChild is a bulk operation function in which all
child document elements of the referenced element is freed. After the
function completes, all associated references will not longer be tracked
within the system.

Example
-------
\snippet examples.cpp removeChildren

*/
auto viewManager::Element::removeChildren(void) -> Element & {

  auto pItem = m_firstChild;
  while (pItem) {
    std::size_t storageKey = (std::size_t)pItem;
    if (pItem->m_childCount)
      pItem->removeChildren();

    // update string index list
    try {
      indexedElements.erase(pItem->getAttribute<indexBy>().value);

    } catch (const std::exception &e) {
      // std::cout << " Exception: " << e.what() << "\n";
    }

    // free memory
    pItem = pItem->m_nextSibling;
    auto it = elements.find(storageKey);
    if (it != elements.end())
      elements.erase(it);
  }

  // update linkage
  m_firstChild = nullptr;
  m_lastChild = nullptr;
  m_childCount = 0;

  return *this;
}

/**
\brief The function removes all children and data from the
the element. All memory for each of the elements is freed.

\details The clear method is a bulk operation that removes
all associated data within the public data members as well as
all manually document elements. It should be noted that
all of the data() adapters are erased.

Example
-------
\snippet examples.cpp clear
*/
auto viewManager::Element::clear(void) -> Element & {
  // delete all items in the dat vector
  auto n = m_usageAdaptorMap.begin();
  while (n != m_usageAdaptorMap.end())
    n = m_usageAdaptorMap.erase(n);

  removeChildren();
  return *this;
}

/**
\internal

\brief The function maps the event id to the appropriate vector.
This is kept statically here for resource management.

\param eventType evtType
*/
vector<eventHandler> &viewManager::Element::getEventVector(eventType evtType) {
  static unordered_map<eventType, vector<eventHandler> &> eventTypeMap = {
      {eventType::focus, onfocus},
      {eventType::blur, onblur},
      {eventType::resize, onresize},
      {eventType::keydown, onkeydown},
      {eventType::keyup, onkeyup},
      {eventType::keypress, onkeypress},
      {eventType::mouseenter, onmouseenter},
      {eventType::mouseleave, onmouseleave},
      {eventType::mousemove, onmousemove},
      {eventType::mousedown, onmousedown},
      {eventType::mouseup, onmouseup},
      {eventType::click, onclick},
      {eventType::dblclick, ondblclick},
      {eventType::contextmenu, oncontextmenu},
      {eventType::wheel, onwheel}};
  auto it = eventTypeMap.find(evtType);
  return it->second;
}
/**
\internal
\brief
The function will return the address of a std::function for the purposes
of equality testing. Function from
https://stackoverflow.com/questions/20833453/comparing-stdfunctions-for-equality

*/
template <typename T, typename... U>
size_t getAddress(std::function<T(U...)> f) {
  typedef T(fnType)(U...);
  fnType **fnPointer = f.template target<fnType *>();
  return (size_t)*fnPointer;
}

/**
\brief adds a new event handler to the element.
\param eventType - the type of event to associate the handler with.
\param eventHandler - the std::function to invoke when the event occurs
within the system.

\details The addListener function provides an method for attaching
an event handler with a event of the referenced element. The
method accepts a function as its eventHandler. This is a std::function
which may be a lambda, or a function pointer. The following events
are accepted:

\copydoc viewManager::eventType

Example
-------
\snippet examples.cpp addListener

*/
auto viewManager::Element::addListener(eventType evtType,
                                       eventHandler evtHandler) -> Element & {
  getEventVector(evtType).push_back(evtHandler);
  return *this;
}

/**

\brief The function is invoked when an event occurrs. Normally this occurs
from the platform device. However, this may be invoked by the soft
generation of events.

*/
void viewManager::Element::dispatch(const event &e) {
  auto &v = getEventVector(e.evtType);
  for (auto &fn : v)
    fn(e);
}

/**
\brief removes dispatching of an event to the caller.
<summary>The function will remove an event listener from the list of
events to receive messages.</summary>

\param evtType is the type of event to remove.</param>
\param evtHandler is the event to remove.?</param>

Example
-------
\snippet examples.cpp removeListener

*/
auto viewManager::Element::removeListener(eventType evtType,
                                          eventHandler evtHandler)
    -> Element & {
  auto eventList = getEventVector(evtType);
  auto it = eventList.begin();
  while (it != eventList.end()) {
    if (getAddress(*it) == getAddress(evtHandler))
      it = eventList.erase(it);
    else
      it++;
  }
  return *this;
}


/**
\internal
\brief This is the main function which invokes drawing of the item and
its children. It is called recursively when painting needs to occur.
This function is used internally and is not necessary to invoke. That
is, system already invokes this as part of the processing stack. The
work performed by this routine is accomplished using the surface image.
*/
void viewManager::Element::render(Visualizer::platform &device) {
}

/**
\brief Uses the standard printf function to format the given
parameters with the format string. When the Boolean member
ingestStream is set to true, the API inserts the named
elements within the markup into the document along with any
text.

\param fmt is a printf format string. It should be a literal
string.
\param ...  is a variable argument parameter passed to the standard
  printf function.

\code
  vector<string> movies={"The Hulk",
                        "Super Action Hero",
                        "Star Invader Eclipse"};

  auto& e=createElement();
  e.ingestStream=true;
  e.printf("The movie theatre is <blue>opened</blue> today for matinee.");
  e.printf("Here is a list of movies: <ul>");

  for(auto n : movies)
    e.prinf("<li>%s</li>",n.c_str());
  e.printf("</ul>");

\endcode

\note If a literal is not used for the first parameter, a warning will
be issued. This warning is effective because at times, it reminds the
developer that if the format string comes from a foreign source
and is not controlled, the stack may be violated.
\endnote


\ref markupInputFormat


*/
void viewManager::Element::printf(const char *fmt, ...) {
#if defined(__linux__)
  va_list ap;
  va_start(ap, fmt);
  char *buffer = nullptr;
/* These are checked with the __attribute__ setting on the function
 * declare above. Turning them off here makes it only report warnings to
 * calls of this member function and not the asprintf call. As well,
 * buffer is passed as a double pointer and is used to note the allocated
 * memory. It is also freed within this routine. */
#pragma clang diagnostic ignored "-Wformat-security"
#pragma clang diagnostic ignored "-Wformat-nonliteral"
  vasprintf(&buffer, fmt, ap);
#pragma clang diagnostic warning "-Wformat-security"
#pragma clang diagnostic warning "-Wformat-nonliteral"

  // if stream ingestion is on, interprets the markup as it arrives.
  if (ingestStream)
    ingestMarkup(*this, buffer);
  else
    data().push_back(buffer);

  free(buffer);
  va_end(ap);
#elif defined(_WIN64)
  va_list ap;
  va_start(ap, fmt);
  char *buffer = nullptr;
  int len;

  len = _vscprintf_l(fmt, NULL, ap) + 1;
  buffer = (char *)malloc(len * sizeof(char));
  len = vsprintf_s(buffer, len, fmt, ap);

  // if stream ingestion is on, interprets the markup as it arrives.
  if (ingestStream)
    ingestMarkup(*this, buffer);
  else
    data().push_back(buffer);

  free(buffer);
  va_end(ap);
#endif
}

/**
\internal
\brief The ingestMarkup function provides a method to parse markup that is
similar to HTML. The format is more restrictive in that the parser is not as
forgiving for errors.

\details
The routine is called by the functions that allow a markup string.
This routine uses the object factory and color map to query the
contents of the maps.

The parser context applies memory to successive calls to the function.
This is important for functions like printf or the stream insertion
operators so that markup gets interpreted correctly. Since there is one of
these contexts per element, each element operates independently.

The parser acts in a two phase operation, first locating each of the tags
as markup and those that appears as tags but are not markup elements. The
second phase builds the elements and applies the attributes to the
elements. Since document fragments can be nested, the parser function
maintains a stack of created elements.

\ref markupInputFormat

*/
Element &viewManager::Element::ingestMarkup(Element &node,
                                            const std::string &markup) {

  static parserContext pc;

  if (pc.elementStack.size() == 0)
    pc.elementStack.push_back(node);

  // pointer to the input buffer.
  const char *p = markup.data();

  // tokenize the markup string
  for (auto ch : markup) {
    switch (ch) {
    case '<':
      if (pc.sText.size() != 0) {
        pc.parsedData.emplace_back(textData, false, pc.sText);
        pc.sText = "";
      }
      pc.bAttributeList=false;
      pc.bAttributeListValue=false;
      pc.bSignal = true;
      pc.bSkip = true;
      break;
    case ' ':
      if (pc.bSignal && (!pc.bToken || pc.bAttributeList)) {
        pc.bQuery = true;
        pc.bSkip = true;
      }
      break;
    case '=':
      if (pc.bAttributeList) {
        pc.bQuery = true;
        pc.bSkip = true;
      }
      break;
    case '>':
      if (pc.bSignal) {
        pc.bSignal = false;
        pc.bToken = false;
        pc.bSkip = true;
        pc.bQuery = true;
      }
      break;
    case '/':
      if (pc.bSignal) {
        pc.bTerminal = true;
        pc.bSkip = true;
      }
      break;
    }

    // the query flag is on when a item has been tokenized after a signal
    // has been found.
    if (pc.bQuery)
      processParseContext(pc);

    if (!pc.bSkip)
      if (pc.bSignal)
        pc.sCapture += ch;
      else
        pc.sText += ch;

    pc.bSkip = false;
  }

  // if text exists, add as a textdata element.
  if (pc.sText.size() != 0) {
    pc.parsedData.emplace_back(textData, false, pc.sText);
    pc.sText = "";
  }

  // second phase, iterate over the parsed context and develop the elements,
  // color text nodes, and set attributes for the items on the stack. once
  // items are processed, they are removed from the stack using the delete
  // range operator, For a complete tag to exist, the end tab must also
  // exist.
  auto item = pc.parsedData.begin();
  while (item != pc.parsedData.end()) {

    // if the item is processed
    if (get<1>(*item))
      continue;

    switch (get<0>(*item)) {
    case element: {
      Element &e = get<factoryLambda>(get<2>(*item))({});
      pc.elementStack.back().get().appendChild(e);
      pc.elementStack.push_back(e);
      get<1>(*item) = true;
    } break;

    case elementTerminal: {
      pc.elementStack.pop_back();
      // mark as processed
      get<1>(*item) = true;
    } break;

    // the attribute and value are handled here together
    case attribute: {
      auto itAttributeValue = std::next(item, 1);
      if (itAttributeValue != pc.parsedData.end() &&
          get<0>(*itAttributeValue) == attributeValue) {
        get<attributeLambda>(get<2>(*item))(
            pc.elementStack.back(), get<string>(get<2>(*itAttributeValue)));
        get<1>(*itAttributeValue) = true;
        // mark as processed
        get<1>(*item) = true;
        item++;
      }

    } break;

    case attributeSimple: {
      get<attributeLambda>(get<2>(*item))(pc.elementStack.back(), "");
      // mark as processed
      get<1>(*item) = true;
    } break;

    case color: {
      auto &e = pc.elementStack.back().get().appendChild<textNode>(
          textColor{get<colorNF>(get<2>(*item))});
      pc.elementStack.push_back(e);
      get<1>(*item) = true;
    } break;

    case textData: {
      pc.elementStack.back().get().data().push_back(get<string>(get<2>(*item)));
      get<1>(*item) = true;
      break;
    }
    }

    // goto next item
    item++;
  }

  // if all items have been terminated, and only one element is on the stack
  // it should be the node, so pop it off.
  if (pc.elementStack.size() == 1) {
    Element &eRet = pc.elementStack.back().get();
    if (eRet.m_self == node.m_self)
      pc.elementStack.pop_back();
  }

  // erase processed items when marked,
  pc.parsedData.erase(std::remove_if(pc.parsedData.begin(), pc.parsedData.end(),
                                     [](auto &n) { return get<1>(n); }),
                      pc.parsedData.end());

  return node;
}

/**
\internal
\brief The function processes one query of a parse context.
\details The first process of the function is to transform the
input to lowr case to ensure case insensitive comparisons. The
pc parserContext structure operates on a stream basis. Therefore
the logic within this function provides the pass through and control
break logic to implement the functionality. An intersting effect
is that at times a token must be completely found before it may be
processed. For example the ID of a element should be sent within one
context.

*/
void viewManager::Element::processParseContext(
    viewManager::Element::parserContext &pc) {

  string sKey = pc.sCapture;
  std::transform(sKey.begin(), sKey.end(), sKey.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  if (pc.bAttributeList && !pc.bAttributeListValue) {

    // store iterator to the function
    auto it = attributeFactory.find(sKey);
    if (it != attributeFactory.end())

      // if the attribute is a series of two tokens
      if (get<0>(it->second)) {
        pc.parsedData.emplace_back(attribute, false, get<1>(it->second));
        pc.bAttributeListValue = true; // value is expected to follow.

      } else {
        pc.parsedData.emplace_back(attributeSimple, false, get<1>(it->second));
        pc.bAttributeListValue = false;
      }
    pc.sCapture = "";
    pc.bQuery = false;
    if (!pc.bSignal)
      pc.bToken = false;

  } else if (pc.bAttributeList && pc.bAttributeListValue) {
    pc.parsedData.emplace_back(attributeValue, false, pc.sCapture);
    pc.sCapture = "";
    pc.bQuery = false;

    if (!pc.bSignal) {
      pc.bAttributeList = false;
    }
    pc.bAttributeListValue = false;

  } else {

    auto it = objectFactoryMap.find(sKey);
    if (it != objectFactoryMap.end()) {

      if (pc.bTerminal) {
        pc.parsedData.emplace_back(elementTerminal, false, "");
        pc.bToken = false;
        pc.bTerminal = false;
        pc.bAttributeList = false;
        pc.bAttributeListValue = false;

      } else {
        // store lambda for the element factory
        pc.parsedData.emplace_back(element, false, it->second);
        pc.bToken = true;
        pc.bAttributeList = true;
        pc.bAttributeListValue = false;
      }

      pc.sCapture = "";
      pc.bQuery = false;

    } else {
      // store the color object within the parser payload
      auto it = colorNF::colorIndex(sKey);
      if (it != colorNF::colorFactory.end()) {
        pc.parsedData.emplace_back(color, false, colorNF(it));
      }

      // illegal match found, pipe contents into ?
      pc.bQuery = false;
    }
  }
}

/**
\internal
\var nodes contains a list of the elements and their coordinates.
*/
std::unordered_map<std::size_t, std::reference_wrapper<Element>> nodes;

std::size_t viewManager::Visualizer::allocate(Element &e) {
  static std::size_t token = 0;
  std::size_t ret = token;
  nodes.emplace(ret, std::ref<Element>(e));
  token++;
  return ret;
}
void viewManager::Visualizer::deallocate(const std::size_t &token) {}

