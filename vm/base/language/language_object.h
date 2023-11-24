/*
 * This file is part of the ux_nebula distribution
 * (https://github.com/amatarazzo777/ux_gui_stream).
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


/*

The base language object, all parser derrive from this functionality to 
have much less code within their source tree. For example, all parsers
for every language can use the file input, memory input, token to ast node,
Generalized AST nodes, such as function call, object call, import modules,
text rendering, document building, file system, time formating, user interface,
network protocols, databases, etc can use the same or functional base. The 
ability to functionally operate on calling objects and calling conventions 
using the ABI. Supporting template typed inlined algorithms for building block
application requirements, vector, array, searching, sorting and memory management 
as an inlined resource. There are better and more efficient means to utilize 
the connections, no error checking at all can be faster. This is one reason
null was placed into the world. If a CPU could advance index position, 
repeat a number of times faster than checking for the condition each time.
Automatic advancing by after use signaling is a type of circuit design. The 
processor only mimics this. If the logical gates between the layers of memory,
bit with carry ALU, compare happened because of their known status next, decision,
as hinted by the previous instuction known at compiler time, the comparrison already can 
be completed. Therefore a hinting series on statement context changes from
programming languages can also instruct the flow of machine operation better. 

Many times the workings of algorithms and the styled language offer poor performance.
Even as a programmer, people would not want to design things this way because of 
best practices and maintain ability solutions. Yet For example, many types of thread 
signaliing against a list can increase searching work, where some of the participants
waiting for the signal are near within the current search. By dispatching to neighbors
this information, some types of searching speed can be increased. 

Mutex and multithreaded programming with memory management and UI, database etc. Thread 
pool and interface abstraction to using this concept is easy. Thread pool manager has a 
metric for balance, low and high. The low number of threads is known to be available.
The high number is limit before signal wait. Each algorithm step needing work is added
to the queue of the thread pool manager. It has the abstract interface and within the 
c++ class has the function filled with multitasking. Often types of objects perform
certain types of work. One called PDF, Dta, Report, etc. As parameters, the constructor
adopts the object to utilizing those resources. The resources must be locked while 
reading or writing to them. Mutex provides this functionality, while signal wait provides the 
fastness of immediately starting after an update. For example the thread pool manager would 
continuing looping and then wait until there is no work being requested in the queue. Advancements
in system processes of thread pools can even tie two together before proceeding to the next.
 Logic processing is a described, modeled and then generalized.

*/

namespace viewManager {
  enum_algorithm_t {
    string,
    date,
    time,
    vector_array,
    list_array,
    queue,
    mutex,
    unordered_map,
    ordered_map,
    partial_map,
    sort,
    sort_with_compare,
    thread,
    filesystem,
    numericFormat,

    base_function_call
  };

class computer_language_abstract_t {
  std::vector<std::string> lines_of_code;
  ASTNodes *node;
  std::vector<std::string> grammer;

  // ast nodes with inline genetic algorithm
  void emit_algorithm_inline(ASTNode *node, enum_algorithm_t a);
  void emit_document_object_inline(ASTNode *node);
  std::size_t emit_create_memory(unsigned char *b, std::size_t size, bool bmutex);
  std::size_t emit_create_object(unsigned char *b, std::size_t size, bool bmutex);
  void emit_free_memory(size_t id);

  /*
  This function is filled out in the language defintiion, One long
  switch statment that emits the tree node. It is called 
  each node visit. The walking process, reading, and parsing process 
  are taken care of by this system. The one function, needs to be filled out.
  Some functions for expressions can even be copied. Giving the large list a list
  already made.
  */
  virtual void fn_visit(ASTNode *node, LLVM *block) = 0;
};

}