#include "vm/vm.h"

using namespace std;
using namespace viewManager;


void testview(viewer_t &vm);

/****************************************************************************************************
***************************************************************************************************/
#if defined(__linux__)
int main(int argc, char **argv) {
  // handle command line here...
#elif defined(_WIN64)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /* hPrevInstance */,
                   LPSTR lpCmdLine, int /* nCmdShow */) {
  // command line
#endif

  // create the main window area. This may this is called a Viewer object.
  // The main browsing window. It is an element as well.
  auto &vm = createElement<viewer_t>(
      windowTitle{"Examples"}, objectTop{10_pct}, objectLeft{10_pct},
      objectHeight{640_px}, objectWidth{800_px}, textFace{"arial"},
      textSize{16_pt}, textWeight{400}, textIndent{2_em}, lineHeight::normal,
      textAlignment::left, position::relative, paddingTop{5_pt},
      paddingLeft{5_pt}, paddingBottom{5_pt}, paddingRight{5_pt},
      marginTop{5_pt}, marginLeft{5_pt}, marginBottom{5_pt}, marginRight{5_pt});

  testview(vm);

  vm.processEvents();
}

/************************************************************************
showing off the object wall paper formats. glyphs rendered for the
text have some stars sticking out, trinkets of moons, planets, solar models,
in lumience bitmap. Depending upon the vbrush contents, multiple areas
of the font can be colored, layered as a glyph operation.
astro,vbrush contains a database of vector trinkets related to astronomy.
Sets may be combined. when a brush is in the color definition it can effect all
of the background and rendering surroundng the characters, in color.

these are subtley integrated into the font. A separate layer fitting the same
identity coordinates, with the group is spread. the parameters, provide a
seed input. Variance is produced according to the seed and strength.
astro.owallpaper is suited for gylphs.

the mars vbrush provides painting and coverage image blending showing
space and planets shaded and faded to white around the text. The brush
can contain base_line path information and also the drawing of intricate
graphics within the text pattern.

the vbrush format does not apply to specific characters of a set of words,
it contains the vector, color bitmap graphics, as a database of visual
information. Color bitmaps are not applied to to glyphs but to the color
areas.

************************************************************************/
void testview(viewer_t &vm) {
  vm.ingestStream = true;
  vm << "<h1 textFace=arial,astro.vbrush)  textsize=30pt "
        "color=brush(mars.vbrush)>Hello Earth, high "
        "yags</h1>";
  vm << "<h2 textFace=britannic color=darkgrey >Subearth low jumps</h2>";
  vm << "<p textcolor=orange>Got to be a pretty day upside and underneath.</p>";
  vm << "<p textcolor=red>Yet sometimes when evil lerks, days may be more "
        "creative than usual. Angels must strive. Whales slap against the "
        "light house.</p>";
  vm << "<p color=green>green</p><p color=lime,20,purple>lime</p>"
        "<shape star(199).gradient(blue,purple,orange)>"
        "<p color=brush.stripes(2,green,orange,violet,darkpurple)>beautiful "
        "zebra style organic stripes, mode 199</p>"
        "<p color=brush.spots(1,blue,red,grey, .3)"
        ".shadows(5_px,.3),gradient(yellow,pink,green)> "
        "on the text, looking nice by the seed and mode input. "
        "Patterns inset as a layer atop the glyphs under.  "
        "<span textFace{astro.vbrush},18pt> Text face inherited, "
        "vbrush applied, text is organically placed within the shape,"
        "above the shape, or distributed in a fragmented way"
        ".</ span>The 199 literal parameter in the star fun call is a pattern "
        "seed."
        ".More parameters can be given.The shape tag.</ p> < / shape >";
}

/*
        e.getAttribute<textIndent>().value = randomDouble(0.0, 10.5);
    e.getAttribute<objectTop>().value = randomDouble(0.0, 300);
    e.setAttribute(objectTop{randomDouble(0.0, 300), numericFormat::percent});
    e.getAttribute<objectLeft>().value = randomDouble(0.0, 300);
    e.setAttribute(objectLeft{randomDouble(0.0, 300), numericFormat::percent});
    e.getAttribute<objectWidth>().value = randomDouble(0.0, 300);
    e.setAttribute(objectWidth{randomDouble(0.0, 300), numericFormat::percent});
    e.getAttribute<objectHeight>().value = randomDouble(0.0, 300);
    e.setAttribute(
        objectHeight{randomDouble(0.0, 300), numericFormat::percent});
    e.getAttribute<textFace>().value = randomString(10);
    e.getAttribute<textWeight>().value = randomDouble(0.0, 1000.0);
    e.getAttribute<tabSize>().value = randomDouble(0.0, 10.0);
    e.getAttribute<focusIndex>().value = randomDouble(0.0, 1000.0);
    e.getAttribute<lineHeight>().value = randomDouble(0.0, 20.0);
    e.getAttribute<paddingTop>().value = randomDouble(0.0, 20.0);
    e.getAttribute<paddingBottom>().value = randomDouble(0.0, 20.0);
    e.getAttribute<paddingLeft>().value = randomDouble(0.0, 20.0);
    e.getAttribute<paddingRight>().value = randomDouble(0.0, 20.0);
    e.getAttribute<marginTop>().value = randomDouble(0.0, 50.0);
    e.getAttribute<marginBottom>().value = randomDouble(0.0, 50.0);
    e.getAttribute<marginLeft>().value = randomDouble(0.0, 50.0);
    e.getAttribute<marginRight>().value = randomDouble(0.0, 50.0);
    e.getAttribute<borderWidth>().value = randomDouble(0.0, 50.0);
    e.getAttribute<borderRadius>().value = randomDouble(0.0, 10.5);

*/
