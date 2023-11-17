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
	gothic, and script. If we disect the problem from a harvested nature, simply the engine of 
	vector storage supplies the rendering pipeline together with functions that can utilize 2d 
	geometry, and work with algorithms that are scientific. With the very few routines already 
	borrowed, it seems that a mountain of code is gone. Now it is time to add more.

	Looking through the character rendering of various Latin fonts listed on the google page,
	a program that analyzes the font files extracting the glyph measurements and organizing by 
	name seems natural. An input of perhaps 1500 font vectors as a base for statisical study of
	font names. Aligning each glyph and storing in a master database measurements that describe 
	the rendering differences. This is one form of a database that can be stored or used to organize
	a feature set for a glyph according to language.

	Expanding on the methods currently in use, most fonts seem to be categorized about specific in width, 
	reading, Form alteration in sections particular to a letter. The letters different in sans, serif. The
	font varies on effect of curls, square now, Capital letters, and some curls below the Decender line
	can be variable control. The signature explicit for each time rendering, single character change for
	a particular font to take into account a jitter movement. Natural variances in some texts can be 
	fortifide in also helping focus perhaps. 

	So disecting the characters in language from a meta perspective, one logic alteration area, and 
	rendering pipeline change. The provisions of knowing the segment paths where the tick forms on the 
	capital W, a labeling system defines itself in addition to official terms perhaps. As a range of 
	controlling the sub gymph vector path can be object oriented. 
	
	A system of dynamically creating fonts by name is a modern feature set in monochrome color. Yet fonts
	as a vector system, monochrome, offer the ability to reintroduce the font nameing convention with more
	pleasing user desire by controlling the strength of twenty types of gylph settings at a various strength 
	than knowning a name that fits the criteria. The ability to craft the size and utilize a conformat 
	convention is inviting. Color, and many other new features affect the name of the font. 
	
	To provide advanced font features will power the browser. The family of technology in use now is the 
	true type system, an advanced working font system with every language. The dynamic backbone of the GUI
	industry. Yet often connecting the emotion, desire, personal or commercial desire of a font comes from 
	a range board selection of font names, perhaps types of advanced pet names. Users know of the massive 
	amount of fonts, perhaps they desire less fonts when the font browser appears. So dynamically designing
	a font with normalized parameters accross the glymph range, characters that have a global contextual 
	knowledge of the style settings across the board, numerically set once, form their curve path, deformation, 
	expansion, wire hashes, to mimic the style of font. 
	
	for each letter, a large definition will exist that drives the rendering of the character set. Offering
	that these settings together names a font, a branded level of font texture and effects thought of 
	as a base for C++ app central usage. Ultimately the variance on types of settings, with a known
	amount of them as a byte signature, with a byte parameter. Makes font sizes very small, fifty bytes,
	plus the name. So rather than load vector data as font data, makes the engine very small. As well, effects
	and mood of characters developed by artists, can now be transfered to other languages through their engine.
	


	
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