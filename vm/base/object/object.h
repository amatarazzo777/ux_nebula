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
#pragma once

/*

Object type for all system connections such as image files, image codecs, audio codecs.
A base wrapper for databases, external .so, program source code to the compiled, index or checked 
for validity. As a method that requires other properties such as querying an interface 
and performing initialization to that interface. Most object types have aliased
pointers that hold context while an outer shell can be manulipated to expose specitif types 
of work loads, parameters, or functions. For example, an object code such as the main image top level,
nodes inside the main image provide linkages to codecs that read it. Partially, fully, decoding.
The main image codec may have five interfaces. The design of codecs, are buffered oriented at times.


As an object to work for multiple languages in a way that is useful, has a step process
that can be requested to be non automatic as some languages must have, and also
polymorphic. The problem of state, context to next becomes useful as an abstraction
of processing usage. For example, a date inline converted to a string type. The string 
type should be alsociated with a date after string operations occur that affect
the internal data. Various precious editing can be saved rather than parsing the date
back into a large numeric value stuch as a "long long" or uint64_t. A language patchup
for processor bandwidth, oversite in orginal language. float, double. double has no basic
interpretation as a fraction type. long double, using processor specific fpu operations.
Value comes in naming the bit size and relevance of the decimal point. Rational numbers
and irrational numbers are not represented in the digital world appropiately
and hence are always appromixately. Libraries are built to mimic the types to
provide output of computations.  

To resolve object, or pointers to the multiple interfaces, and translation map
between types with formatting for numeric, and also floating point. Types that are advanced
such as container formats may also be labeled with multiple traversal structures preceeding
the pointer. The pointer always remains the same yet the invocation changes. A one step misdirection
where parameters are not affected. One aspect, a byte code preceeds the object pointer to note 
states of operation. Not connected, or connected for example.The byte preceeding a bitcode,
to check to see if loading needs to occur. 

Object of these strucutures combined with the usage of llvm parameter unions across the parameter 

stack, registers can provide input for merge object contexts. Objects that have threads running 
within in them, have data storage pointers to contexts of data. If data is numeric, mutex enabled,
after placed into registers, the mutex can be unlocked as a call site. Pointers to structures
are numeric integer according to the CPU.

Object, file loading and format traversal using dlsym,and process starting are functional. Yet
the ability to expand on the format is necessary for bc code and library functions of an object 
nature. Many times an object is also accompliaied by multiple objects. Communication of 
datatypes and c++ functions in process or out of process through shared mmemory.
As well as a functional llvm component for algorithm use, this can be a process of 
higher usage because it is integrated with the language stack. Pipes, all of the nice linux features
dreampt up not available on other kernels. pointers are random access to files, os provided.

some aspects can increase, sound card. pathways to device drivers.


an important function is partially reading the file as a random access object. 
For example, how to load one codec at a time with a dependency graph. Provide
language providisons for modules, of this sort, to compile and relocate the code.
Dynamically load other codecs and link with existing dependencies and loading
others and relocating them. Unloading components of the graph, decreasing and managing 
the share count. Reorganzing blocks on program data memory after
types of fragmentation exists.

*/