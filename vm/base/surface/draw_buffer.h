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
@file draw_buffer.h
@date 9/19/20
@version 1.0
@brief off screen cairo complete buffer

*/

namespace uxdevice {

/**
 * @internal
 * @enum draw_buffer_format_t
 * @brief
 */
enum class draw_buffer_format_t {
  none,
  svg,
  png,
  inline_png,
  inline_svg,

};

/**
 * @class draw_buffer_t
 * @brief offscreen buffer wrapping cairo
 */
class draw_buffer_t : public abstract_emit_cr_a_t<order_render>,
                      virtual public system_error_t,
                      virtual hash_members_t {
public:
  draw_buffer_t();

  draw_buffer_t(double _width, double _height);

  draw_buffer_t(int _width, int _height);

  draw_buffer_t(std::string &description);
  draw_buffer_t(std::string &description, int _width, int _height);
  draw_buffer_t(std::string &description, double _width, double _height);
  ~draw_buffer_t();

  /// @brief move constructor
  draw_buffer_t(draw_buffer_t &&other) noexcept;

  /// @brief  copy constructor
  draw_buffer_t(const draw_buffer_t &other);

  /// @brief copy assignment
  draw_buffer_t &operator=(const draw_buffer_t &other);

  /// @brief move assignment
  draw_buffer_t &operator=(const draw_buffer_t &&other) noexcept;

  operator bool() const;

  std::size_t hash_code(void) const noexcept;

  void emit();
  void emit(coordinate_t *a);
  void flush(void);
  bool is_valid(void);

  draw_buffer_format_t format = {};
  double width = {};
  double height = {};

public:
  void read_image(std::string &data, const double w, const double h);

private:


  void image_surface_SVG(const bool bDataPassed, std::string &info,
                         const double width, const double height);

#if defined(USE_STACKBLUR)
  /// Stack Blur Algorithm by Mario Klingemann <mario@quasimondo.com>
  /// Stackblur algorithm by Mario Klingemann
  /// Details here:
  /// http://www.quasimondo.com/StackBlurForCanvas/StackBlurDemo.html
  /// C++ implemenation base from:
  /// https://gist.github.com/benjamin9999/3809142
  /// http://www.antigrain.com/__code/include/agg_blur.h.html
  /// This version works only with RGBA color
public:
  void blur_image(const unsigned int radius);

#elif defined(USE_SVGREN)
  // box blur by Ivan Gagis <igagis@gmail.com>
  // svgren project.
public:
  void blur_image(const unsigned int radius);

private:
  cairo_surface_t *build_blur_image(const unsigned int radius);
  void box_blur_horizontal(std::uint8_t *dst, const std::uint8_t *src,
                           unsigned dstStride, unsigned srcStride,
                           unsigned width, unsigned height, unsigned boxSize,
                           unsigned boxOffset, unsigned channel);

  void box_blur_vertical(std::uint8_t *dst, const std::uint8_t *src,
                         unsigned dstStride, unsigned srcStride, unsigned width,
                         unsigned height, unsigned boxSize, unsigned boxOffset,
                         unsigned channel);

  cairo_surface_t *cairo_image_surface_blur(cairo_surface_t *img,
                                            std::array<double, 2> stdDeviation);

#endif // defined

}; // namespace uxdevice

} // namespace uxdevice
