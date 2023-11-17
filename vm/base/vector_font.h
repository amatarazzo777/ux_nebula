/*
 * vector_font.cpp
 *
 *  Created on: Nov 7, 2023
 *      Author: anthonym
 */

namespace viewManager {
struct point_t {
	float x;
	float y;
};
using path_t = std::vector<point_t>;

struct glyph_t {
	unsigned int offset_x;
	unsigned int offset_y;
	unsigned int width;
	unsigned int height;

	void raster_glyph(float point_size);
	void blend(unsigned int x, unsigned int y, surface *r);

	std::unique_ptr<surface_t> img;

	uint32_t character;
	uint16_t glyph_index;
	uint16_t advance_width;
	uint16_t left_side_bearing;
	int16_t bounding_box[4];

	std::vector<glyph_t::path_t> paths;

	/* a problem of developing various fonts is 
	knowledge of advanced naming conventions for various parts in the technical range.
	Here is a grab bag full of words from the wikipedia.

	Ligature
	Letter-spacing
	Kerning
	Majuscule
	Minuscule
	Small caps
	Initial
	x-height
	Baseline
	Median
	Cap height
	Ascender
	Descender
	Diacritics
	Counter
	Textfigures
	Subscript 
	superscript
	Dingbat
	Glyph

	Much discussion on the meaning and impact of rendering measurements, control, and also 
	legacy understanding of font placement. Layout and justification with multiple text 
	flowing capabilities have to be known for the complete field of text layer to be rendered
	perhaps. For example, after and underneath effects, coloring and flow may depending upon
	size variations encapsolated in layout computation.

	Working with user space, a trinket of standard font names exist, yet naming beyond the 
	few known from corporate network writing, courier, arial, roman, bookman, san sherif, 
	gothic, and script.
	
	 */
};

struct vector_font_t {
	void load_font(void);
	std::vector<std::string> font_names;
	std::unordered_map<uint32_t,glyph_t> glyphs;

};

struct vector_font_manager_t {
	std::unordered_map<std::string, vector_font_t> fonts;
};


}