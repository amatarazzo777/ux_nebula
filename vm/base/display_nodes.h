
// a rendering engine
#include "canvas-ity.h" *
namespace viewManager {
using canvas_t = canvas_ity::canvas;

struct display_node_t {
  virtual void emit(canvas_t *c) = 0;
};

struct coordinate_t : display_node_t {
  float x = {};
  float y = {};
  bool bRelative = false;
  void emit(canvas_t *c) override { c->move_to(x, y); };
};

// paths
struct rectangle_t : display_node_t {

  float x = {};
  float y = {};
  float w = {};
  float h = {};

  void emit(canvas_t *c) { c->rectangle(x, y, w, h); };
};

struct arc_t : display_node_t {
  float xc = {};
  float yc = {};
  float radius = {};
  float angle1 = {};
  float angle2 = {};
  bool brev = false;

  void emit(canvas_t *c) { c->arc(xc, yc, radius, angle1, angle2, brev); };
};

struct close_path_t : display_node_t {
  void emit(canvas_t *c) { c->close_path(); };
};

struct curve_t : display_node_t {
  float x1 = {};
  float y1 = {};
  float x2 = {};
  float y2 = {};
  float x3 = {};
  float y3 = {};
  void emit(canvas_t *c) override {
    c->bezier_curve_to(x1, y1, x2, y2, x3, y3);
  };
};

struct move_to_t : display_node_t {
  float x = {};
  float y = {};
  void emit(canvas_t *c) override { c->move_to(x, y); };
};

struct line_t : display_node_t {
  float x = {};
  float y = {};
  void emit(canvas_t *c) override { c->line_to(x, y); };
};

struct fill_path_t : display_node_t {
  void emit(canvas_t *c) override { c->fill(); };
};

struct stroke_path_t : display_node_t {
  void emit(canvas_t *c) override { c->stroke(); };
};

// font and text
struct text_alignment_t : display_node_t {};

struct text_ellipsize_t : display_node_t {};

struct text_color_t : display_node_t {};

struct text_font_t : display_node_t {};

struct text_indent_t : display_node_t {};

struct text_line_space_t : display_node_t {};

struct text_render_normal_t : display_node_t {};

struct text_outline_t : display_node_t {};

struct text_tab_stops_t : display_node_t {};

struct image_block_t : display_node_t {};
} // namespace viewManager
