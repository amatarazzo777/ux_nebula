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
@file ux_matrix.hpp
@date 9/7/20
@version 1.0
@brief
*/

namespace uxdevice {

/**
 * @class
 * @brief
 */
class matrix_t : virtual public hash_members_t {
public:
  matrix_t() { cairo_matrix_init_identity(&_matrix); }
  virtual ~matrix_t() {}
  void init_identity(void) { cairo_matrix_init_identity(&_matrix); };
  void init_translate(double tx, double ty) {
    cairo_matrix_init_translate(&_matrix, tx, ty);
  }
  void init_scale(double sx, double sy) {
    cairo_matrix_init_scale(&_matrix, sx, sy);
  }
  void init_rotate(double radians) {
    cairo_matrix_init_rotate(&_matrix, radians);
  }
  void translate(double tx, double ty) {
    cairo_matrix_translate(&_matrix, tx, ty);
  }
  void scale(double sx, double sy) { cairo_matrix_scale(&_matrix, sx, sy); }
  void rotate(double radians) { cairo_matrix_rotate(&_matrix, radians); }
  void invert(void) { cairo_matrix_invert(&_matrix); }
  void multiply(const matrix_t &operand, matrix_t &result) {
    cairo_matrix_multiply(&result._matrix, &_matrix, &operand._matrix);
  }
  void emit(cairo_t *cr) { cairo_set_matrix(cr, &_matrix); }
  void transform_distance(double &dx, double &dy) {
    double _dx = dx;
    double _dy = dy;
    cairo_matrix_transform_distance(&_matrix, &_dx, &_dy);
    dx = _dx;
    dy = _dy;
  }
  void transform_point(double &x, double &y) {
    double _x = x;
    double _y = y;
    cairo_matrix_transform_point(&_matrix, &_x, &_y);
    x = _y;
    y = _y;
  }
  std::size_t hash_code(void) const noexcept {
    std::size_t __value = {};
    hash_combine(__value, _matrix.xx, _matrix.yx, _matrix.xy, _matrix.yy,
                 _matrix.x0, _matrix.y0);
    return __value;
  }

  cairo_matrix_t _matrix = {0, 0, 0, 0, 0, 0};
};
} // namespace uxdevice
UX_REGISTER_STD_HASH_SPECIALIZATION(uxdevice::matrix_t)
