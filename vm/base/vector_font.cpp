/*
  vector_font.cpp
 
   Created on: Nov 7, 2023
       Author: anthonym
 */

/*
  Many have tried before and simply decided to increase complexity. Yet as a font object, can more intelligent decisions be
  made by the system as a group. Typically the infustructure of font systems, as a granular focus, offer pop, push and stack instructions
  The effectiveness of rendering nicely solved by vector data and pure code on the other side seems inviting. As a tailored approach using
  less data, intelligent processed letter, word, and advanced quick raster data moves. Often details of this nature might be three pixels for
  normal reading texts.
 
  New designs that provide automated effects, shadow, ligature, types of paragraph style.
 
  Because all font systems in current form have a copyright, the c++ language does not have its
  very own. rendering of graphical texts with an abstracted framework is about the
  closet native that will happen.
 
  To start simply from the drawing constructs of pure vector to raster layer encompasses allocating resources for
  	storing the rendering.
 
  	what to draw at what location or code is strictly left up to the design, yet to encompass data transfer,
  	using the unicode table for ascii, or other.
  	To simplify existing font system data and use it, ones that are free by license to start, and then
  	when sales hit a royalty for their protected asset. The font data, hopefully vector coordinate data for
  	drawing functions, can be magnified as a source for input. using the system data in a one call text render with
  	a buffer, stride etc for traversal, and color mixing.
 
  	As an engine with data only, analyzing the vector data, textual input, raster and fill the block with integrity,
  	readability, and performance for optium color or shading. Utilizing the space, aware of language, with minimal
  	data such as vector data, Within most data sets for the glyph, data exists such that informs the box adjustment
  	to actually blit at, the base line.
 
 
  	 a rendering speed up is the focus is using the next and previous character within the routine rendering's scope.
  	 Typically a large context of data, or perhaps consolidated in large nested loops works even better with the
  	 added complexity of another loop on the outside. The data is composed to form a outline and an image.
 
  	 The ability to reuse the font data, once a medium surface has been found to transform the geometry makes
  	 the font engine powerful to develop multiple other font variations. The font glyph object itself can have more data
  	 associated with it to utilze a system of movement. For  example, on the capital letter A, one can see multiple
  	 position where a font designer or algorithm would want to modify the shape. The cap, top point can be
  	 more pointed or rounded. The middle bar can be raised or lowered. As well, raising one side higher. And the angle of the
  	 of the two vertical slopes. One can easily establish a variance detail for the shape of each letter.
 
 
  	 The ability to use the vectors to apply deformations to characters based on analysis of the path data set,
  	 and measurements of beautification points. The middle, the top half, etc. Corners. The problem that is trying to
  	 be solved is font variation based upon metrics, and even word meaning.
 
  	 To captivate audiences with subtle produced surfaces that envelop the characteristics of a letter shape, english
  	 is a form that remarks. To use contextual meaning, letters, and other attributes, analysis of the context for
  	 the document status has to be known. The type of application, where the text is being rendered, a type of genre
  	 for externalized bitmaps. Using 3d transforms on the letters
 
  	 The textures placed on the modified to convey subtle 3d characteristics and also lighting.
 
  	 effects that are vector based yet apply analyze data from character, word or selection for effect. Procedurally
  	 reduce effects to data input for rendering engine enhanced fonts. That is effect one word. Effect a list with ten ul elements.
    compact animation necessities, sprite, sprite paths, particle system, animation timing functions, texture input. Particle
    positioning can be related to glyph rendering attributes and edges.
 
 	  Another study could be performed to analyze the difference between font styles that are of a distinct quality.
 	  I presume that the readibility of the character could be defined to vary  amongst the points where family
 	  font vary.
 
 	  A specific proposal for vines and types of patters that work well with some types of writing, or letter styles.
 	  To use fine curls on tips or letters such as J, making the inner curve loop is a remark relating to the letter
 	  shape.
 
  	  Provide frame buffer export.
 
  	  shape carving from 2d.
 
  	  To logically analyze the uses of 3d rendering of text for approximation of use. The variance of
  	  blending and background shadow, and texture versus screen real estate and pixel dpi.
 
  	  Using small storage and initial load rendering is fashionable to encompass font engine technology.
 
  	  The ability to strategically use statistical data from the shapes and form natural flowing
  	  meaning for baseline is fine. Although a simplification in data storage.
 
  	  Creating new fonts from a template and applying specialized and well though out deformations. The ability
  	  to construct the letter is present, yet a default exists that provides building. A dedicated model for
  	  transformation. For example the thickness and thinness across the group. The height at various points, stretched.
  	  A radius expansion, etc. The ability to adaptively weight  the zig zag effect around the edges. So with a refined focus
  	  of software transformation to the glyph the uses intercede having an extreme amount of font data.
 
  	  Embedding the font data within the binary executable is very possible considering the small size of vfont data. 
     The program creates new fonts from the selected base standard.
 
  	  Application icon library. Material icons are at times for the web. Developing a natural professional function icon set
  	  for The engine to utilize as grey scale icons for user communication. the folder, file, picture, tree icons,
 
  	  Flow charting and logical definition font with editor.
  	  To store a process flow visually and use design and plug in code from other authors.
  	  	some points are textual and others schematic computer code.
 
 
 		So, the new format will do away with loading new font files. Simply this base font
 	will be modified to note where components of fonts should be turned on or off. 
 	Rendering enhancements in glyph pixel enhancements mark curve spots to show weighted direction
   by using length measurement and comparision. Computers of yesteryear are supported by 
   most font systems because of these facets, yet modern computer laptops offer a large resolution.
   This make the possibility of adding a little more readibility to each character as an onboard 
 	dynamic processing convention making certain to envelop user creativity in font tailoring. That is
   a writer may control the output elequotely. Often several tasteful ways as standard, controlled by numerical weight 
 for strength such as tailored limited range.

  a 3d beveling system tailored for software visual interface production is the consolidated component of the color_t base
 object to supply. Essentially reducing the problem to a tailored domain offers simplicity, and efficiency. Simplifying 
 the domain to a small range of exposure from an embedded surface, that also has a vertex or a raster image must not be
 attenuated from readibability. The inset object is the polygon panel of text. Can provide organic compositions that 
 alieviate the background. Controlled and namwd types of resizing papers. Parameters sent to the object utilize components 
 and effects, embedded art, to apply as a ready appeal for background pixel lighting. 

 Adding polygon aligning text to automatically align to images that are transparently imposed. 
 Providing for nice overlay. Gradient and swashes that appear under the text to match the organic 
 paper. Colors imposed are at times triggered by design naturalist that form image compositions.
 Or the like of readible texts. Providing nice software development of lines are under the title
 forming underline. Yet not formall seen as an underline in term, a specific invocation of an irregular
 space taking large swash, striped, etc. Developed with a consolidated form in descriptive transfer utilizing.
 Specialized lines, boxes, and forms for text and information. Blending transfers, title clipping, text path,
 and rotation. Many new possibilities exist using the c++ standard model as a base window system.

 A font system that is encapsolated, removing data, readible at small sizes, and progressively available as 
 wire stencled hairs that gracefully add mood, or other types of augmentations named. To impose types of adjectives 
 and keane character novalties can rely upon its view space and pixel space. To show that range adjustment
 in default technology defaults for what is colored, a size range that is detailed and sizes that can be applied 
 in color. Make font size usage and control a focus. There are types of font metrics that relate to the operations
 necessary. Viewing distance may also reflect some types of usage contexts.

 The usage of the system as a BIOS or computer hardware controller is also a possibility with system control. Specific
 to the operation is a type of video card device driver that is used for the purpose. For example, along with system 
 composistion, a specific device controller for the video card, touch pad, keyboard controller, and perhaps wifi network
 within the BIOS can supply newer types of laptops.


 
 */

void vector_font::load_font(void) {
	std::ifstream istrm(filename, std::ios::binary);
	uint16_t count;
	char szstring[255];

	std::string filename = "/home/anthonym/source/Lato-Regular.vfont";

	// file format for the vfont file system,
	// "vfont 1.0";
	istrm.read(szstring,10);

	// number of characters in the name and the text.
	istrm.read(reinterpret_cast<char*>(&font_count), sizeof(uint16_t));

	// set for multiple fonts, change later to use compression and file name directory
	for (uint16_t n=0;n<fount_count;n++) {
		ostrm.read(reinterpret_cast<char*>(&count), sizeof(uint16_t));

		istrm.read(szstring, count);
		font_names.push_back(szstring);

		istrm.read(reinterpret_cast<char*>(&encodingID), sizeof(uint16_t));
		istrm.read(reinterpret_cast<char*>(&languageID), sizeof(uint16_t));

		/*
		 ostrm.write(reinterpret_cast<char *>(&n. meta_data.unitsPerEm), sizeof(uint16_t));
		 ostrm.write(reinterpret_cast<char *>(&n.meta_data.Ascender), sizeof(uint16_t));
		 ostrm.write(reinterpret_cast<char *>(&n.meta_data.Descender), sizeof(uint16_t));
		 */


		// number of glyphs
		istrm.read(reinterpret_cast<char*>(&count), sizeof(uint16_t));
		glyph_count = count;

		for (uint16_t cnt = 0; cnt <= glyph_count; cnt++) {
			glyph_t gl;

			istrm.read(reinterpret_cast<const char*>(&gl.character),
					sizeof(uint32_t));
			istrm.read(reinterpret_cast<const char*>(&gl.glyph_index),
					sizeof(uint16_t));
			istrm.read(reinterpret_cast<const char*>(&gl.advance_width),
					sizeof(uint16_t));
			istrm.read(reinterpret_cast<const char*>(&gl.left_side_bearing),
					sizeof(uint16_t));
			istrm.read(reinterpret_cast<const char*>(&gl.bounding_box),
					4 * sizeof(int16_t));


			uint16_t path_cnt;
			istrm.read(reinterpret_cast<char*>(&path_cnt), sizeof(uint16_t));

			for (uint16_t cnt2 = 0; cnt2 < path_cnt; cnt2++) {
				uint16 point_count;

				ostrm.read(reinterpret_cast<char*>(&point_count), sizeof(uint16_t));

				for (uint16_t cnt3 = 0; cnt3 < point_cnt; cnt3++) {
 					glyph_t::path_t points;
					for (uint16_t cnt4 = 0; cnt4 < 3; cnt4++) {

						glyph_t::point_t point;

						ostrm.read(reinterpret_cast<const char*>(&point.x),
								sizeof(float));
						ostrm.read(reinterpret_cast<const char*>(&point.y),
								sizeof(float));
						points.push_back(point);
					}

					paths.push_back(points);
				}

			}

		}

	}

}
