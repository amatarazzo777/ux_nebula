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


};
} // namespace VM