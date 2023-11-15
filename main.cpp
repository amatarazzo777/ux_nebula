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
  vm << "<h1 textFace=arial textsize=30pt color=hotpink>Hello Earth, high "
        "yags</h1>";
  vm << "<h2 textFace=britannic color=darkgrey >Subearth low jumps</h2>";
  vm << "<p textcolor=orange>Got to be a pretty day upside and underneath.</p>";
  vm << "<p textcolor=red>Yet sometimes when evil lerks, days may be more "
        "creative than usual. Angels must strive. Whales slap against the light house.</p>";
  vm << "<p color=green>green</p><p color=lime,20,purple,>lime</p><p "
        "color=crimson>crimson</p>";

  /* forms of gradient definition within the color tag. Color should also support 
   image, etc. Perhaps the system buildup will include an object that simply encapsolates
   the entire engine as a stream context with a discrete focus on types of functionality
   that are plug in based. As a reusable object, with an encoded binary stream input 
   for function invocation breveity. A stream with graphic database file loading. Parts of the 
   stream exists to instruct the dynamic alteration
   of the graphic asset in multiple forms, even over time. For example, making a series of 2d curves
   shaped differently as its beautification attributes are used. 
    The ability to set up a rendering chain that is complex with
   multiple types of compositie graphics, and animation layers is a easily adopted figure.

   Especially within the color tag, gradient producer, or effects. As a friend class of the 
   nodes, inspecting the analyzed output from 2d vector queries, quadrant area signifigance, blending,
   and unification within the animation aestitcs provides effective display capabilities. 

   Provide smarter management of language rendering for English, Spanish to use the first 255 bytes during 
   character reading, writing and storage. Provide a flexible structure to utilize also rendering of all
   language characters. 
*/

/*
The use of exterior words apart from the standard c++ library often shows some modifications that may be well liked.
To utilize the push_back, delete, insert keywords and provide c++ algorithm support may be over design. 
These functions can be added to provide like STD syntax. Review and simplify if necessary. Adding  these routines in place of createElement.
One may also simply provide call through template classes named like the STD. Does it make the code more readible?
Downfalls?  Here is an example.

  auto e=vm.push_back<h1>({});


Evaluate system design complexity. Less code and more elegant algorithms. How much data should the system be able 
to handle, or expected to handle? The limits of a usable interface should be met well before processing nature
of the machine. Providing upper bounds is important, security of compositions within a window box. 

Because the font system is embedded without downloadable fonts, it depends on less unsecure data. The nature of
X11 transport is created here, as is the rudimentary stream type for information displays transposed from
html web page layouts to a rendering pipeline. Limiting the prospects of ever supporting all features of the 
browser, there can be some types of transfer support for native layout of books, with images, games, etc. Where the 
format is just loaded and displayed. Routines of components plugged in, and simple logic to handle all business needs.
Much more effective than the Javascript language for database entry applications. In fact language definition
and modern compiler design has to advance to support these technologies. The ability to craft simple computer 
language files, plug it into the system and utilize more summarization techniques, encapsolation, offers using
perhaps LLVM. The scope of producing efficient code is seen with c++, yet how much input is required to 
provide these types of results on object oriented designs is difficult to know. For example there are a hugh
number of options for call sites to know about, yet perhaps only a few of them will be used. Use use of AST
and recursion with a tokenizer is how modern expressions can be evaluated. The integrated comparisons and vector types,
memory allocation, rely on stack space. 

The linker must link to the OS libraries to utilize heap I believe. Yet
a feature to design is that linking of an object should be designed to be done completely in memory, such
that the program's internal memory management is mostly the user's choice. Gui memory and other object
data in some system designs can reside within another process space. It is of interest to maximize development of 
transfer options to invoke a container type of protocol to transfer the data without future changes. Yet it is known 
that the standard library is not within space. For example, templates can be designed with select template
query functions that test for constexpr that make allowable code path productions possible. One use is to tailor
the routine around this distinction. There are also other types of advanced template functions that provide
static code polymorphism, testing if a base type is within the inheirted stack.  So for example, testing if the 
container or element supports raw data transfer of its memory location as a size or structure allows it to be 
automatically transfered as a data type to the rendering process. The complete package of data elements within
a shared memory buffer as a whole is best. Parts of it locked and managed. 

So the testing of the STL version and capabilities are evident for some features, more projects in other departments
of system design. new componet systems for native c++, memory linking, container, vector storage. Other types of problem
solvers can utilize protocol style buffers to develop reall time call site mechanisms to versioned interface objects. One 
hugh problems with object growth style is too many interface changes, outdate functionality. The loading of a binary foot
print within the .so file that is selective while other parts are not needed is useful in updating linktime components.
Thereby agreeing to a level of depreciation.  Interfaces often grow to add support for functional updates in other industry
areas, and then are modified to technically be ineffective, and altered forms are adopted in the future. Simple changes that
can be described through comparrision and analysis to promote automatic updating of software is advanced. A C++ program 
that runs in the future, as adopts a liked interface portion, style, control pallette, has to be planned well. One remark is
that in such uncompromising circumstances where all cannot be provided, is that generalizations be in place. 

One focus of HTML brand is that within the group of writers, one expects ordinary writers to accomplish the tags. 
There are all sorts of tags flying around, yet as a writer's some do provide sense. The ability to more accurately 
define a useful layout language that also inheirits a names space such as academic MLA, or Universal Addresses, or 
Control Patterns makes better building block sense to expose the browser's layout technology. Therefore the mode
of the page tags should offer exciting possibilities. The usefulness of this supplied within this programs is to
test also if it would be able to be reutilized, add tags, and redefine styles. Element, reuse capabilities 
is essential. Offering a useul consolidated approach to audience style writing, and modes of writing can be useful
to many people. This method of template C++ provides this easily, enhancements to provide better inheiritance support
is useful.

Programs that try to crash the system with all types of obsecure work, some resulting from errors, invalid data,
 should be crafted. Building a system full of error message is execellent for business systems. Yet routines that 
 are within a domain of logic can be expected to operate without errors on input. In low level algorithm programming
 it is often necessary to skip error on input to achieve throughput. 

While the code is built based upon nomenclature HTML basic tags, to invoke. Modifying the c++ template to 
yeild placement into a raw pointer node tree can be useful. The task of pointer management of this kind has 
been solved manytimes before, problems do come again. As a enhancement, moving away from small token within
the function namespace to a well spell out method tends to offer programming companionship. Such as 
instead of createElement<H1> to using more of a c++ street legal academic terminology, to 
createElement<H1_t>({}), or createElement<heading_t<1>>({}). Moving away from some condensed forms to more structure.
These questions should be prized.

Booting from linux and designing an Application framework for items does have its direction. As well, traditionally
working with the elaborate and well known windows API has a winning combination. As a library that can be lifted to
place in other languages through parse invocation offers multiple running platforms. 

Designing edit components was a shift in methodology to craft them in the pure browser languages. Yet as a mixture,
native and new controls should rely on object oriented inheirtance. The work of entering a character, designing a wisiwig
document editor, and the like has become embedded solely in the javascript world. To build a system that can provide
extensive editing features, grammer, spelling, and the consumer versus business audience publishing is well deserved 
in designing as a base feature object. Therefore component engineering to supply the longevity should utilize the mix
component rendering technology. 


*/
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
