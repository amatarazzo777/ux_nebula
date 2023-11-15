/*
 * vector_font.cpp
 *
 *  Created on: Nov 7, 2023
 *      Author: anthonym
 */

/*
 * Many have tried before and simply decided to increase complexity. Yet as a font object, can more intelligent decisions be
 * made by the system as a group. Typically the infustructure of font systems, as a granular focus, offer pop, push and stack instructions
 * The effectiveness of rendering nicely solved by vector data and pure code on the other side seems inviting. As a tailored approach using
 * less data, intelligent processed letter, word, and advanced quick raster data moves. Often details of this nature might be three pixels for
 * normal reading texts.
 *
 * New designs that provide automated effects, shadow, ligature, types of paragraph style.
 *
 * Because all font systems in current form have a copyright, the c++ language does not have its
 * very own. rendering of graphical texts with an abstracted framework is about the
 * closet native that will happen.
 *
 * To start simply from the drawing constructs of pure vector to raster layer encompasses allocating resources for
 * 	storing the rendering.
 *
 * 	what to draw at what location or code is strictly left up to the design, yet to encompass data transfer,
 * 	using the unicode table for ascii, or other.
 * 	To simplify existing font system data and use it, ones that are free by license to start, and then
 * 	when sales hit a royalty for their protected asset. The font data, hopefully vector coordinate data for
 * 	drawing functions, can be magnified as a source for input. using the system data in a one call text render with
 * 	a buffer, stride etc for traversal, and color mixing.
 *
 * 	As an engine with data only, analyzing the vector data, textual input, raster and fill the block with integrity,
 * 	readability, and performance for optium color or shading. Utilizing the space, aware of language, with minimal
 * 	data such as vector data, Within most data sets for the glyph, data exists such that informs the box adjustment
 * 	to actually blit at, the base line.
 *
 *
 * 	 a rendering speed up is the focus is using the next and previous character within the routine rendering's scope.
 * 	 Typically a large context of data, or perhaps consolidated in large nested loops works even better with the
 * 	 added complexity of another loop on the outside. The data is composed to form a outline and an image.
 *
 * 	 The ability to reuse the font data, once a medium surface has been found to transform the geometry makes
 * 	 the font engine powerful to develop multiple other font variations. The font glyph object itself can have more data
 * 	 associated with it to utilze a system of movement. For  example, on the capital letter A, one can see multiple
 * 	 position where a font designer or algorithm would want to modify the shape. The cap, top point can be
 * 	 more pointed or rounded. The middle bar can be raised or lowered. As well, raising one side higher. And the angle of the
 * 	 of the two vertical slopes. One can easily establish a variance detail for the shape of each letter.
 *
 *
 * 	 The ability to use the vectors to apply deformations to characters based on analysis of the path data set,
 * 	 and measurements of beautification points. The middle, the top half, etc. Corners. The problem that is trying to
 * 	 be solved is font variation based upon metrics, and even word meaning.
 *
 * 	 To captivate audiences with subtle produced surfaces that envelop the characteristics of a letter shape, english
 * 	 is a form that remarks. To use contextual meaning, letters, and other attributes, analysis of the context for
 * 	 the document status has to be known. The type of application, where the text is being rendered, a type of genre
 * 	 for externalized bitmaps. Using 3d transforms on the letters
 *
 * 	 The textures placed on the modified to convey subtle 3d characteristics and also lighting.
 *
 * 	 effects that are vector based yet apply analyze data from character, word or selection for effect. Procedurally
 * 	 reduce effects to data input for rendering engine enhanced fonts. That is effect one word. Effect a list with ten ul elements.
 *   compact animation necessities, sprite, sprite paths, particle system, animation timing functions, texture input. Particle
 *   positioning can be related to glyph rendering attributes and edges.
 *
 *	  Another study could be performed to analyze the difference between font styles that are of a distinct quality.
 *	  I presume that the readibility of the character could be defined to vary  amongst the points where family
 *	  font vary.
 *
 *	  A specific proposal for vines and types of patters that work well with some types of writing, or letter styles.
 *	  To use fine curls on tips or letters such as J, making the inner curve loop is a remark relating to the letter
 *	  shape.
 *
 * 	  Provide frame buffer export.
 *
 * 	  shape carving from 2d.
 *
 * 	  To logically analyze the uses of 3d rendering of text for approximation of use. The variance of
 * 	  blending and background shadow, and texture versus screen real estate and pixel dpi.
 *
 * 	  Using small storage and initial load rendering is fashionable to encompass font engine technology.
 *
 * 	  The ability to strategically use statistical data from the shapes and form natural flowing
 * 	  meaning for baseline is fine. Although a simplification in data storage.
 *
 * 	  Creating new fonts from a template and applying specialized and well though out deformations. The ability
 * 	  to construct the letter is present, yet a default exists that provides building. A dedicated model for
 * 	  transformation. For example the thickness and thinness across the group. The height at various points, stretched.
 * 	  A radius expansion, etc. The ability to adaptively weight  the zig zag effect around the edges. So with a refined focus
 * 	  of software transformation to the glyph the uses intercede having an extreme amount of font data.
 *
 * 	  Embedding the font data within the binary executable is very possible considering the small size of vfont data. The program
 * 	  creates new fonts from the selected base standard.
 *
 * 	  Application icon library. Material icons are at times for the web. Developing a natural professional function icon set
 * 	  for The engine to utilize as grey scale icons for user communication. the folder, file, picture, tree icons,
 *
 * 	  Flow charting and logical definition font with editor.
 * 	  To store a process flow visually and use design and plug in code from other authors.
 * 	  	some points are textual and others schematic computer code.
 *
 *
 *
 *
 */

class glyph_t {
public:
	class point_t {
		float x;
		float y;
	};
	using path_t = std::vector<point> class;

public:
	unsigned int offset_x;
	unsigned int offset_y;
	unsigned int width;
	unsigned int height;

	void raster_glyph(float point_size);
	void blend(unsigned int x, unsigned int y, raster_t *r);

private:
	raster_t *img;

	uint32_t character;
	uint16_t glyph_index;
	uint16_t advance_width;
	uint16_t left_side_bearing
	int16_t bounding_box[4];

	std::vector<glyph_t::path_t> paths;


};

class vector_font {
private:
	void load_font(void);
	std::vector<std::string> font_names;
};

