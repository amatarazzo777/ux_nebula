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
   for doing this. As well BISON. The temptation to start a 
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
   the amount of customers a global company would have.

   So the ability to functionally plan information systems, is primarily entered around 
   indexing, editing, and program visual interface. Solving these systems to
   an elegant payload size, and enhancing data storage editing with LLVM as a
   useful upgrade path system can be an ultimate solution. The ability
   to design database of this nature can be rooted in size requirements 
   and storage location. As a running process service, database engines require
   many types of facilities far reaching to a user editing process actually requires.
   That is to say, parsers, indexers, and record level locking. Many times today's
   memory, even providing a size of a two gigabyte database, for storage is allowable
   for memory. This number upgrades quickly over time. Therefore, merely the reference
   to big data codec objects such as textures, graphics, programs, can also be operative
   as the next generation storage mechanic. To supply this data, as a operative stream
   hidden, is also knowning of its large nature size. BLOB is typically what it is 
   reffered to as. Therefore reference generation is a type of facility. A select
   post loading that can run as part of the data access, while engaging the 2GBsize
   for effective query times. Types of cache limiting algorithms may provide unlinking
   of storage data to remove it and its siblings from memory, without as diagrammingad or write
   but simply refer to to as a symlink to NVME storage.

   The most effective compression algorithms are often on language, or high level object data
   such diagramming, where language, shape selection and language operate. The data storage
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
Reduction in assembly in in forms of data type as well. Meaning that the decoder model of the 
CPU circuit design is antiquated, such that design for data types and data type recognition
for numerical, string, integer, floating, are conceived as communicated through language
as a program and reintroduced with a few mixups of previous legacy ALU. As well,
typically a program will have knowledge of the types it uses, even functional 
code memory pointers. Integration for cpu register usage and even name types are
misrepresented by the hardened memnonic style. The advancement is found perhaps
in two types of advancements simple and more far reaching. In the simple abstractions,
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
integrating as a part of the layered instruction set is register to finance device. 

The more far reaching advancements, as mentioned earlier, are in print and SOC designs.
 However by minimizing 
SOC is by integration knowlegde of its usage to BIOS. That is, modern computers,
adopted the driver model. Yet most computers have a set number of devices, even
set and cannot be upgraded. The BIOS functions are not programmed for the 
complete system, and do not function as a part of the running instruction 
set per instruction code context. To simply know how multiple processes work
running on one machine was the technology path that led the current implementation.



. That is the finance
and back software are protected. Yet ones ability to see illegal data mainly comes
from one instruction currently in the Low Level community, providers of sandboxes. Typically 
consumer models of all available cpus have this instruction turned on. Int 3 on intell for example
allows one to stop the code and enter the system into debug mode.
 Simply, invoked the system appears to freeze. Therefore
disableing low level debugging facilities for consumer microprocessor is an upgrade path.
The development of OS systems at ring levels could be provided for by supplying 
limited hardware of debugging. Reliance on the OS for finance data types and spending
is incorporated at the versitile LLVM layer yeilds results in data security, to
the device. This does have to be a protected software and hardware OS design, perhaps a type
of BIOS functionality. 

*/
  u_int32_t fn_load_object(std:string);
  


};
} // namespace VM