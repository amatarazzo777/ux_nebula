
class display_node_t {
public:

};

// line options
class antialias_t : public display_node_t {

};

class coordinate_t : public display_node_t {
};


// paths
class rectangle_t : public display_node_t {
public:
  rectangle_t();
  rectangle_t(double _x, double _y, double _width, double _height);
  virtual ~rectangle_t();

  double x = {};
  double y = {};
  double width = {};
  double height = {};
};

class arc_t : public display_node_t {
public:
  arc_t();
  arc_t(double _xc, double _yc, double _radius, double _angle1,
                double _angle2);
  virtual ~arc_t();

  double xc = {};
  double yc = {};
  double radius = {};
  double angle1 = {};
  double angle2 = {};
};

class close_path_t : public display_node_t {

};

class curve_t : public display_node_t {
public:
  curve_t();
  curve_t(double _x1, double _y1, double _x2, double _y2, double _x3,
                  double _y3);

  double x1 = {};
  double y1 = {};
  double x2 = {};
  double y2 = {};
  double x3 = {};
  double y3 = {};
};

class line_t : public display_node_t {
public:
  line_t();
  line_t(double _x, double _y);
  virtual ~line_t();

  double x = {};
  double y = {};
};

class fill_path_t: public display_node_t {
};

class stroke_path_t: public display_node_t {
};

// font and text
class text_alignment_t    : public display_node_t {


};

class text_ellipsize_t: public display_node_t {
   
};

class text_colot_t : public display_node_t {

};

class text_font_t: public display_node_t {
 
};

class text_indent_t: public display_node_t {
    
};

class text_line_space_t: public display_node_t {

};


class text_render_normal_t: public display_node_t {
    
};

class text_outline_t: public display_node_t {

};

class text_tab_stops_t: public display_node_t {

};

class image_block_t : public display_node_t { };

