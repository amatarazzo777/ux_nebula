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

/**
 * @author Anthony Matarazzo
 * @file textual_render_storage.h
 * @date 9/19/20
 * @version 1.0
 * @brief
 */

#pragma once

namespace uxdevice {

/**
 * @class textual_render_storage_t
 * @brief class used to store parameters and options for a textual render. The
 * object is created as the side effect of inserting text, char *, std string or
 * a std::shared_ptr<std::string>. The class inherits from display_visual_t
 * which notes the ink rectangle of the object. The display_visual_t class also
 * exposes an intersection method for the render system to decide which function
 * to invoke, a standard draw or a clipped draw.
 */
class textual_render_storage_t : virtual public hash_members_t,
                                 virtual public system_error_t,
                                 virtual public display_visual_t,
                                 virtual public pipeline_memory_t {
public:
  textual_render_storage_t();

  virtual ~textual_render_storage_t();

  /// @brief move constructor
  textual_render_storage_t(textual_render_storage_t &&other) noexcept;

  /// @brief copy constructor
  textual_render_storage_t(const textual_render_storage_t &other);

  /// @brief copy assignment
  textual_render_storage_t &operator=(const textual_render_storage_t &other);

  /// @brief move assignment
  textual_render_storage_t &
  operator=(const textual_render_storage_t &&other) noexcept;

  void pipeline_acquire(void);
  bool pipeline_has_required_linkages(void);
  std::size_t hash_code(void) const noexcept;

};
} // namespace uxdevice
UX_REGISTER_STD_HASH_SPECIALIZATION(uxdevice::textual_render_storage_t)
