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
#pragma once

/**
@author Anthony Matarazzo
@file window_interface.h
@date 10/15/20
@version 1.0
@brief
*/

namespace viewManager {



/**
 *
 */
struct generic_os_interface_t {

  ///@brief abstract class for os interface capabilities.
  /*
  The ability to utilize window technology of existing operating systems, using
  link library is a great definition for layered technology. The capabilities
  of the standard library are starting to connect with operating systems in 
  multiple ways. The library is famous for getting things off the ground.
  As one dives futher, some aspects of the technology can be grouped 
  functionally differnt. The parrelle process, thread, memory management, and signal
  functionality are after thoughts in langauage summary. Yet designing a comprehensive 
  language requires development resources trained. Parsers, parsing technology, lexing,
  and assembly. The largest functional part of compiler designs is the expression evaluator that
  utilizes even basic math, accessing variables, memory locations, sign extending, modulus rounds 
  with magic numbers, float point, double. Translating between native micro processor data types.
  There are even more enhanced optomizations of instruction output compression than I know. 
  Cross processor assemby is rare, what an oppurtunty to use direct BC. The types of parrelle
  process instructions are effective in its assembly, as it has vector types of specific 
  data types.

  https://releases.llvm.org/2.6/docs/LangRef.html#i_malloc

  llvm assembly, the documentation says system heap. So, what about items
  such as share dmemory access at the VM layer. There is work it seems on specific types
  of memory, I am unsure if this is consumer based yet.
  
  */

  /**
   * @fn void fn_initialize(void)
   * @brief
   *
   */
  virtual void fn_initialize(void) = 0;


  /**
   * @fn void fn_terminate(void)
   * @brief
   *
   */
  virtual void fn_terminate(void) = 0;
  
  /**
   * @fn void open_window(const coordinate_list_t&, const std::string&,
   * const painter_brush_t&, const event_handler_t&)=0
   * @brief
   *
   */
  virtual void fn_open_window() = 0;

  /**
   * @fn void close_window(void)=0
   * @brief
   *
   */
  virtual void fn_close_window(void) = 0;

  /**
   * @fn void flush_window(void)=0
   * @brief
   *
   */
  virtual void fn_flush_window(void) = 0;

  /**
   * @internal
   * @fn fn_set_window_title
   * @brief The function sets the window title, should be implemented within
   * the resulting OS implementation.
   *
   */
  virtual void fn_set_window_title(const std::string &stitle) = 0;

  /**
   * @internal
   * @fn fn_copy_canvas
   * @brief 
   *
   */
  virtual void fn_copy_canvas(const canvas_t *c) = 0;

/*
   object types that have memory relocation specifiers
   and requested parameter invocation, allowing
   for inheritance at runtime. The plugins that comprise the 
   internal network of routines, or 
   other objects it utilizes provides runtime change
   capability. The object promotes communication to native
   parsers of languages. Allowing for easy component and syntax
   yeilds. The YACC interface, is such a procedural method
   for doing this. As well BISON. A one system runs all approach
   to language as a implementation is the llvm approach.
   
    The temptation to start a 
   program utility to functionally accept language definitions
   and also provide easy adoption of languages, but reworking
   for interface GUI connectivity. 

   Another very pertient work is providing for the plethora of
   change over as research continues, after providing the module.

   The stdio, cout, cin, functional gear of the command world 
   is priceless in elevating the platform initially. The ability
   can be initially summarized by providing a class implementation,
   that ties the console style io, monofonts, ncurses, color text, etc
   to a change over code case. Providing a new object loading
   format enables multiple entry starting points. The load object
   also provides a compatible layer for data structure only. The 
   methods of parameter communication protocol, and return data
   optomized for std compatibility.

   The objects as information portals can become desktop trinklets,
   such as even providing an input interface via stylish GUI, and 
   component controls. The necessity to remove unused logic can 
   become an update pattern for select objects. Historical context
   and other state information can also become an integral part
   of application framework inclusions. 

   The provisions of object databases are a fine inclusion for the 
   c++ language. However often, the various formats becomes a 
   difficult problem to support. A combination of priciples lies
   in wake for database structure storage. There is a reason to create
   a database format for the c++ language, integrated with its 
   API structure. Providing for the data storage of types that are compact
   and technically aligned gives the insite to database advancements. 

   In reality, a database should store information from multiple formats,
   and allow advanced indexing. The corner stone of the technology 
   was to give a select type of administrator the ability to summarize
   data from queries. In text, the language has a means to do this.
   Yet no active developer ever uses a DBA. To ensure a reference point
   for why data is stored. How much data is stored. And how it is going to be used
   in a type of search are very keane problems to solve. The ability to also know
   that most can even reside in memory or partially by todays standards.

   Hard press databases exist such as requires actual long term storage size vs
   memory size. Banking databases are this size in account record keeping. The 
   the intricate problem solved using a massive storage size reference perhaps.
   Yet this places algorithm burden planning system. In a code reduction facility such
   as programming natures have, recursion notes that code is reduced. In this, data
   storage complexity can be reduced for the unit. That is for banking, each customer has 
   their own database. The problems of system integrity are majorly reduced, considering
   the amount of customers a global company would have. Each customer can even have their
   own native access object, for down to block byte location hard coded. Transactions 
   rarely change, and with electronic money will not.

   So the ability to functionally plan information systems, is primarily entered around 
   indexing, editing, and program visual interface. Solving these systems to
   an elegant payload size, and enhancing data storage editing with LLVM as a
   useful upgrade path system can be an ultimate solution. The ability
   to design database of this nature can be rooted in size requirements 
   and storage location. As a running process service, database engines require
   many types of facilities far reaching to a user editing process actually requires.
   That is to say, parsers, indexers, and record level locking. 
   
   Many times today's available system memory provides an easy size gap for a two 
   gigabyte database. In text, numerical data, structures and pointers, that is a
   hugh vast array of data. For a corporate business perspective, data models of 
   CRM systems,  store sales, catalog, health systems, insurance company clients,
   grocery store product listing, super mall areas, car part catalog. Many of these 
   database informations are naturally geared for human sized listings. It is the detailed 
   views that primarily affect cache and memory balancing performat as blob loading.
   
    
   This memory number upgrades quickly over time, and has, but the amount of 
   human readible, numerical, data has slightly increased, most likely a 
   function of population, databases are filled. Therefore, merely the reference
   to big data codec objects (BLOBs) such as textures, graphics, programs, can also be operative
   as the next generation storage mechanic. To supply this data, as a operative stream
   hidden, is also knowning of its large nature size. BLOB is typically what it is 
   reffered to as. Therefore reference generation is a type of facility, operating a streaming layer from
   orginal disk data. A select post loading that can run as part of the data access, 
   while engaging the 2GBsize for effective query times. Types of cache limiting algorithms 
   may provide unlinking of storage data to remove it and its siblings from memory, 
   without as diagrammingad or write but simply refer to to as a symlink to NVME storage.
   The engagement of the pointer and node target as a defined function of storage is important.
   For the storage of them a relocation to offset within the database strcture to redevelop
   the pointer is needed. Yet one argues that the entire 2gb of database in memory is
   ineffective for multiple computers. There are methods to utilize interface linking
   with BC code to form linking and database operations. 

   One of the most pertient yet untied through multiple corporations existing 
   in many areas of the world, in their own country, is storage of
   common  worldly things and their signifigance as a number, money amount, 
   name, address, measurements, as a database extra storage that requires definition
   in editing, display, and should be linked to the database field if editing.
   Other  attributes that signify relations may not become the experience 
   in other countries. For example, one may wish to open the "World Data and Entry Book reader"
   interface they have with "ohm". Some aspects of their new OS experience for world 
   culture integration should include world image contexts, font vector code page, 
   computer properties, and content age already compiled on the right start menu. 
   Can you envision the beloved Arabic
   fade ins and soft sound of "Ohm". Perhaps from the black state to the orginal screen
   before close, with a precise image operation that caused it to spiral and blue. 
   It is somewhat recognizable, and "Ohm", appears for three seconds, the unspiral and open 
   can be a object nately compiled as a lid_event_t object for example. The text letters ever
   enveloped in goodness, with the delicate fade and sound. The sound may fad and echo two
   more times. A gamer may have tactile feedback in the joystick or mouse, system features
   provide soft communication to the new buterfly device. Perhaps with operating tts voice models
   a guru voice model can enliven a short interlude of music, and the desktop and prior
   work fade in. Butterflys round the curves to show where it was you left off in writing.
  Or Fireworks. of a select detail with ultimate control in new almost formed experimental
  sparsely lit words, limited to five letters at a time. The letters do not line up all the time,
  and are sparkling at various life rates. The letters on the screen show reaction as objects by shadow
  direction and also coloring of face and bevels. Inner trinkets of the UI also remark. 
  Some prefer many other introductions.

    The c++ OS with llvm and 
   BISON language import. Forget about security in version 1, compile easy precise
   languages with amazing interfaces, and languages existing. then developers
   will lock users out. Only users write viruses and malware. I am glad I do not.


   The most effective compression algorithms are often on language, or high level object data
   such diagramming, where language, shape selection and language operate. For language,
   types of strategic indexes for partial before and after on words, and also inner words exist.
   The indexing of the parts of strategic word and paragraph
    The data storage
   type, and record format type is a requirement of storage already, hence providing
   logic for compression is by data type. The memory, and also storage process, should
   provide a type of versitile storage where it is effective at choosing the size
   chunk operation for compression.

   The ability for the system, as a database, to functionally use the cross platform library
   of c++ is perfect. The database should store the format of its data, starting point.

   The formal database process names that schema should be provided, often this leaves out
   the node relationship. In database, the formal name is modernly known as tuple. A self contained
   entity. Providing for a way to know this can increase storage capacity. The knowledge of heiracry
   or heirarchical databases, is the next generation of the index lookup. The actual storage
   form of relational databases truncates this entire speedup facility with functionality
   that is rarely used. Then encompasses this inside the parsible easly indexed and updateable
   record format. The ability for previous programs compiled to use this data can be planned
   to work if the fields are set to nullable as default. Yet most likely the user will need the 
   new data because now major interfaces are provided by web servers and do not need to
   be compiled or redistributed again. 

   To solve these types of oversite problems in C++, can provide easier development perhaps,
   but users can be addressed to their data by just a better planned data architecture. One that 
   grows from network, to local, and even to replace the legacy SQL style. Database storage formats,
   IE relational are secure because of their composite data storage and box storage mechanics. Yet
   OOP data types that provide secure editors is exactly what is needed to edit. Todays modern
   information editing provides that a thousand boxes of programming and data sets be 
   behind the data system to use it. To simply solifidy this in the base architecture of 
   c++ can save a hidious amount of computer programs.

   Knowledge of data systems architecture from a trainspot to encompass the usage and requirement
   only has given way to bad behaving computer programmers. As an instution the 
   system is reactionionary and behaved box boxing all systems to show archtectures
   requireing legacy work. The security knowledge in the modern C++ age can tie these
   together to solved these problems of editing. It is the finance and data storage
   systems that need a functional separate security to humans. Identity, security,
   all of the known network natures have been designed into subsequent systems
   such as the web server. The client and network server as a unique connection solves
   these types of issues, that is every client has a unique encryption algorithm.With llvm
   in the chain the options are limitless. The solving of program archiecture
   for editing in a consolidated form is solved. This type of change over
   offers a completely new oppurtinty to update data storage. Putting price on 
   the back end network, that can operate as a functional financial data center.
   The modern usage of just a lite SSL, has been superceded because people know
   the algorithm. A had in the past wrote a demostration program of encryption in c++
   that totaly surprised unrelated technology people. They thought that it was illegal
   to write, a simple 3d bit box. But using the standard library of transforms, data 
   became unrecognizeable. The "Hello World, How are you doing today?" message in 
   text. The password to the data "THEPASSWORD". Yet knowledge of writing this
   for the user is senseless. A user should not even care about passwords, other than 
   logging in to their machine, game box, phone, tablet, television or watch.

C++ can be used to store currency, or links to currency accounted for by an FDIC, instution
provided both parties establish a type of customer agreement, the bank can install an 
protected software object and reserve account space on the machine. Simply an easy mechanic
can tell you that a flat tire does not kill the engine. The same leverage is used in finance
and technology. To identify finance operations as a consumer, a specific ring pattern 
would be subtle. To the user, an effort to hold a designed card that establishes 
and integrated chip, data strip with a known format for all cards ties itself to
the user's financial identity. Providing the device with low level accountability, such
as a wallet has to be developed at the protected identity layer for the device. Making it
tied to a distinct device operation. A money spend mode, or light. The user must feel 
persionalized to it as wealth. The data type as a c++ data type has to support 
control of spend amounts, or frequency for usage environment. This leaves the process
of financial theft very thin, other than one taking the device.

The field of hacking at the machine layer is the view of object code, machine code 
using various dissassembly techniques, many of the public ones are not extensive.
 That is the finance and back software are protected. Yet ones ability to see illegal 
 data mainly comes from one instruction currently in the Low Level community -;, 
 providers of sandboxes. Committed to hiding because who can compile the OS? Typically 
consumer models of all available cpus have this instruction turned on. Int 3 on intell for example
allows one to stop the code and enter the system into debug mode.
 Simply, invoked the system appears to freeze. Therefore
disableing low level debugging facilities for consumer microprocessor is an upgrade path.
The development of OS systems at ring levels could be provided for by supplying 
limited hardware for system debugging. Reliance on the OS for finance data types and spending
is incorporated at the versitile LLVM layer yeilds results in data security, to
the device. This does have to be a protected software and hardware OS design, perhaps a type
of BIOS functionality. 

Reduction in assembly in in forms of data type as well. Meaning that the decoder model of the 
CPU circuit design is antiquated, such that design for data types and data type recognition
for numerical, string, integer, floating, are conceived as communicated through language
as a program and reintroduced with a few mixups of previous legacy ALU. As well,
typically a program will have knowledge of the types it uses, even functional 
code memory pointers. Integration for cpu register usage and even name types are
misrepresented by the hardened memnonic style. All logic instruction sets of the CPU
have to accept a variable redefined register set for the CPU context. This context
can be changed inline. This redefines the bottleneck of this type of memory access
to be identified through one indirection context per instruction. And finally one 
mov instruction will be capible of the entire register bank, to one location. Removing
the bottleneck of current memory access to the entire cpu pipeline of < 4k perhaps. Smaller 
floating point sizes, that round up. This changes the throughput of the entire
risc instruction set. The instruction set advances on the bit level.

The advancement is found perhaps in two types of advancements simple and more 
far reaching. In the simple abstractions,
a methodology does exist for signel calling of routines, accessing the namespace
BIOS. These set of routines as a microprocessor composition aligns itself
ans an unused work of GUI design work, or native nvme work. The purpose for the 
event of using the device. The design of the function set has been compromised and 
has to change to meet demand of even a instruction set for the application. Or the instructionset
for the operating system. Both the systems are ran on the same microprocessor. It 
much simpler in the C++ lower level to use the GUI projection as an os component.
Incorpration of BIOS functionality for the instruction reduces the necessity of 
an extreme large code base. The device drivers may have to use port in and out, but 
by changing the instruction set context to the ring layer provides an attached byte 
code for the cpu instruction decoder. In the hardware planning layer, this ultimately leaves
questions of CISC or BIOS to CPU call. Therefore, the updating of the BIOS,
as a provider for these extended functions or driver communication. Typically
universal expansions has been serialized into plugs and ports. The methods
of PCI necessity are for select corporate environments. They have to have more
deticated power and processing requirements for types of computing tasks.
The best designs to hardware are by providing a more complex pointer in the machine code.
The methods of keeping binary pointers large and a set size, rather than variabled sized,
has much to do that encompassese legacy segmentation and just a number approach
to finding a block of memory. A microprocessor instructionset can advance
to adaptively manage symbols that reorganize automatically as a program
requirement. That is, if a program has only three pointers, the highest memory address
is 3.The address can be stable in as little as three bits as well. The dynamic naming
of registers, and their mathematical usage as a single block of memory. The context change
aligns itself with the model of the necessity of the program. From low level
to a high level, per application, or sub system. The adoption of the basic RISC promise
is modified by a variance in the register name to be relative to the processing context.
The microprocessor and ALU adopt a bit schema such as one, zero, run patterns reflect ALU
or memory address pattern within the instruction set. Usage of the instruction at the 
application layer or low level per executing instruction schema change instruction
provides a delicate way for more formation of routines. Perhaps a new pathway of cacheing 
will have to exist for these schema bit patterns. Yet an exciting surprise is SOC designs
integrating as a part of the layered instruction set is register to finance device. These
instruction set operations can be modeled in software. The dynamic format for parrelle
maths have their use in both integer and floating point. Typically the CISC instructionset
advances in speed due to register inclusion at the operation layer. At that, what was being 
called for and then fashioned was speed. The ability to incorporate this transformation 
allows a necessary memory access to be loaded into the operating field of the cpu, and gpu.

Adoption of context change for instruction set size, limits the instruction set to per 
processing context, with an allowed known number of calls. Simply the decoder might
batch dispatch to the service table pin connector before instruction execution. The process 
at the hardware layer, provides faster execution capabilities. The adopting of hinting
per CPU cache size, and historical instruction flow as per instruction site, can be tagged 
as a specialized instruction. 


The more far reaching advancements, as mentioned earlier, are in print and SOC designs.
 However by minimizing 
SOC is by integration knowlegde of its usage to BIOS. That is, modern computers,
adopted the driver model. Yet most computers have a set number of devices, even
set and cannot be upgraded. The BIOS functions are not programmed for the 
complete system, and do not function as a part of the running instruction 
set per instruction code context. To simply know how multiple processes work
running on one machine was the technology path that led the current implementation.

Solving the problem in currnet form was being able to boot in a staged process
for versitility. Yet more appropiate is relocatable streaming footprints. The order
is changed to functionally show the before the lid close quicker. So for example,
a new install is already considered. The install is a web server app or could start 
as a installer that takes a long time. Gentoo for example, can take up to five days
for people. Automating the buld process, and image writing to boot sector. As an
onboard image to pass through UEFI, just requires accepting third party keys, GPT
the new set and providing direct to the boot.  

The inclusion of object should entail complex entities such as foundation level GUI
stream binary models, retrieved from the network stack or file, memory and 
added for projection, vbrush data files, and database objects. Adding remote resources, 
network, xml, image formats, html, html translators to display objects, with events attached,
game network worlds, office documents in headless integrated storage stream editor, enhanced PDF
through integrated book reading viewer. XSL, XML, and XSLT are powerful existing
formats that can be applied. JSON has specific properties that introduce data
translation from a network source and other program data. The jdbc library provides
an interface that may be established. CSV, data, gui element, or reformated. ODBC,
postgress, mysql, and other common database implemententations have an implementation
that may function better as an LLVM enabled technology. Typically many types of databases
of these categories can be tied together. The credentials of logging in is typical of 
network. The applicable formats are plentiful, and as a server, network technology,
many offer advanced data types and programming language support. But I feel that my fifty 
thousand record data limit, is fine. As a reflection of growth pattern, the indexing and start
of the database to in memory tollerances.

The ability to control adaptively these database sources to utilize the vector storage of data
is present. Yet often the communication of the buffer bin binary form is better. The engine supports
a high level description through STL, and provides data and data schema creation and storage
stream operations from the c++ perspective. The secondary issue to dynamic growth is
the standard methods of push_back();

Or rather the database should contain  the schema walk definition through type alias 
deduced at compile time. The best model could contain a c++ stream input. The type
input gathered and does not provide structure and data misalignment with the 
internal vector. The additional method of fetch is important in context of having 
data requested in a stream manner. For example, if there are fifty thousand
matches, perhaps only the first hundred records are given in the network 
or even file model. A tollerance setting that is difficult to control without 
contextual information.

The database implementation should allow display and edit of formula, artifical
intelligence data, sensor data, data to be read by high frequency. Voice models,
artifical brains of select knowledge base, and character rendering. Course information
and presentation.

Types of data interfaces are needed at the blob layer.
To propose a standard would be unlikely to be coherent for long. The ever 
conversion from string and implement not leaving the c++ syntax standard.
The easiest forms of object usage tieing language input, provides an optimum design
layer. If the program can adaptively learn languages, and apply contexts that shine
at ring layers with integrated tailored easy GUI, dom and object ui. A focus on tailored
approaches often applies the context of how string data is utilized, and internal 
memory representation available to systems typically designed on the exterior.
By adaptive integrating the features and language compiling together, expert
runtime performances can be attained. Whereby currently multiple transposed systems of
operation are boxed for portability. To approach current language implementations
requires definite input to the number languages. The BISON and YACC system supports the most 
advanced and complete forms of modern language.

examples that are scientific, allowed to be used with the license. And expect residues
later for the company companionship of corporate funds. That is most scientific defintions
are handshake (c), and therefore later can apply foundation funds for software payment 
platform usage.

Python, a very popular technique in computer programming that is said to require emensive
code to support. But as you will see, the grammer file, of a BISON parser is specialized, 
like a magic tool. 

https://docs.python.org/3/reference/grammar.html

For data processing and layout, the mixing of the data layout mechanisms of template oriented
dialects like xslt, xml and css to the native system of layout is adaptive. Limiting the amount 
of actual elements and also simplifing the usage to c++ data structures when necessary, That is
the ability to use a data transform, via text input on a vector data type, containing a tuple,
is effective for transform and textual language description. Transfering some knowledge of the 
system of language to a complete binary implementation for multiple languages to address and 
use allows optomization in the memory organization. Typically the modern method relys on a
component that is refined at catching errors, or not being compromised. These systems
make be designed much more effectively using centralized compiling techniques and in 
memory linking. 

XML, XSLT are forms of data and interface separation that are direct. Often a type
of record for or iterator approach and also database scale offer better implementations
as an analyzed language input. With LLVM utilizing the XSLT and a object code producer
that creates a C++ Document object model, formatting it as so the template desires.
Luckily the best features of language are often obscured by the used new back tick quote,
the one under the tilde. I guess it was a last resort to go ahead an incorporate it.
Yet the modern c++ allows a dangerious input of raw binary or text data into
its buffer. As a literal string, inside a editor, it provides a nice comprimise to
alternate language inclusion when short types of languages are needed as input.
And then also external file input, translated as a unit inside the binary as a formed
unit. 

https://en.wikipedia.org/wiki/BASIC
basic is a generalized computing language that many can read and flow
through to close the gap. The inclusion of centralized systems of visualization
and also database, and object usage at the memory layer is important. 

https://en.wikipedia.org/wiki/Go_(programming_language)

https://en.wikipedia.org/wiki/R_(programming_language)

https://github.com/twitter-forks/mysql/blob/master/sql/sql_yacc.yy



The functional aspects of Java and also C# remark of a processing type. The provisions
of language and base features are often find in the base feature arena. They offer
remarked and standard formats. Yet as a base system for UI, these two will need updating.
Yet these languages need updating and wer invented as a battle arrangement. Often they
do have great ideas, but leave out some other liked traits.

UI elevations to streamline the use of nativ ecomponent and a versitle interface description
was a design root of java. It survives as a generalized computing language. 
Yet the interface is often triggered as a pixel render, when the DOM advancements can achieve
greater native platform usage. So mixign the new forms of native rendering, with advanced 
format input.


*/
  u_int32_t fn_open_object(std:string);
  


};
} // namespace VM