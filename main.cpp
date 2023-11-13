#include "vm/api/path/arc.h"
#include "vm/vm.h"

using namespace std;
using namespace viewManager;

void test0(Viewer &vm);

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
  auto &vm = createElement<Viewer>(
      windowTitle{"Examples"}, objectTop{10_pct}, objectLeft{10_pct},
      objectHeight{640_px}, objectWidth{800_px}, textFace{"arial"},
      textSize{16_pt}, textWeight{400}, textIndent{2_em}, lineHeight::normal,
      textAlignment::left, position::relative, paddingTop{5_pt},
      paddingLeft{5_pt}, paddingBottom{5_pt}, paddingRight{5_pt},
      marginTop{5_pt}, marginLeft{5_pt}, marginBottom{5_pt}, marginRight{5_pt});

  test0(vm);

  vm.processEvents();
}

/************************************************************************
************************************************************************/
void test0(Viewer &vm) {
  vm.ingestStream = true;
  vm << "<h1 textFace=arial textsize=30pt color=hotpink>Hello World, high "
        "yags</h1>";
  vm << "<h2 textFace=britannic color=darkgrey >Subearth low jumps</h2>";
  vm << "<p textcolor=orange>Got to be a pretty day upside and underneath.</p>";
  vm << "<p textcolor=blue>Yet sometimes when evil lerks, days may be more "
        "creative than usual.</p>";
  vm << "<p color=green>green</p><p color=lime>lime</p><p "
        "color=crimson>crimson</p>";

  vm << 
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
