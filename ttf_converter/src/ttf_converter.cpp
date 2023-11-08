//============================================================================
// Name        : ttf_converter.cpp
// Author      : Anthony Matarazzo
// Version     :
// Copyright   : (c) 2023 Anthony Matarazzo
// Description : ttf to vector font, Ansi-style
//============================================================================

#include <iostream>
using namespace std;


#include <stdio.h>
#include <cwchar>
#include <chrono>
#include <thread>
#include <cstring>

#define TTF_FONT_PARSER_IMPLEMENTATION
#include "ttfParser.h"


//Change to a valid font location
const char* font_path = "/home/anthonym/source/fontData/Lato-Regular.ttf";

void font_parsed(void* args, void* _font_data, int error) {
	if (error) {
		*(uint8_t*)args = error;
		cout << "Unable to parse font " << font_path << std::endl;
	}
	else {
		TTFFontParser::FontData* font_data = (TTFFontParser::FontData*)_font_data;

	    std::string filename = "Test.b";
	    {
	        std::ofstream ostrm(filename, std::ios::binary);
	        double d = 3.14;
	        ostrm.write(reinterpret_cast<char*>(&d), sizeof d); // binary output
	        ostrm << 123 << "abc" << '\n';                      // text output
	        uint16_t	count;

	        // file format for the vfont file system,
		    ostrm << "vfont 1.0";
		    for(auto n : font_data->font_names) {

		    	// number of characters in the name and the text.
		    	count = font_data->font_names.size();
		    	ostrm.write(count, sizeof uint16_t);
		    	ostrm.write(font_data->font_names.c_str(), font_data->font_names.size());

		    	ostrm.write(font_data->encodingID, sizeof uint16_t);
		    	ostrm.write(font_data->languageID, sizeof uint16_t);

		    	ostrm.write(font_data->meta_data.unitsPerEm, sizeof uint16_t);
		    	ostrm.write(font_data->meta_data.Ascender, sizeof uint16_t);
		    	ostrm.write(font_data->meta_data.Descender, sizeof uint16_t);
		    	ostrm.write(font_data->meta_data.Descender, sizeof uint16_t);

		    	// number of glyphs
		    	count = font_data->glyphs.size();
		    	ostrm.write(count, sizeof uint16_t);

		    	for (const auto& glyph_iterator : font_data->glyphs) {
		    		Glyph &gl=glyph_iterator.second;
		    		count = gl->size();

			    	ostrm.write(count, sizeof uint16_t);

			    	for (const auto& path_list : gl.path_list) {

			    		ostrm.write(gl.character, sizeof uint32_t);
			    		ostrm.write(gl.glyph_index, sizeof uint16_t);
			    		ostrm.write(gl.advance_width);
			    		ostrm.write(gl.left_side_bearing);
			    		ostrm.write(gl.bounding_box, 4 * sizeof int16_t);


			    		count = path_list.geometry.size();
			    		ostrm.write(count, sizeof uint16_t);

						for (const auto& geometry : path_list.geometry) {
							ostrm.write(geometry.p0.x,sizeof float);
							ostrm.write(geometry.p0.y,sizeof float);
							ostrm.write(geometry.p1.x,sizeof float);
							ostrm.write(geometry.p1.y,sizeof float);
							ostrm.write(geometry.c.x,sizeof float);
							ostrm.write(geometry.c.y,sizeof float);
\
						}
		    		}
		    	}

		    }
	    }


		//step through glyph geometry
		{
			for (const auto& glyph_iterator : font_data->glyphs) {
				uint32_t num_curves = 0, num_lines = 0;
				for (const auto& path_list : glyph_iterator.second.path_list) {
					for (const auto& geometry : path_list.geometry) {
						if (geometry.is_curve)
							num_curves++;
						else
							num_lines++;
					}
				}
				wprintf(L"glyph 0x%x %lc: %d quadratic curves and %d lines\n", glyph_iterator.first, glyph_iterator.first, num_curves, num_lines);
			}
		}

	    }

		*(uint8_t*)args = 1;
	}
}

int main() {
	cout << "TTF to vector_font" << endl; // prints TTF to vector_font

	uint8_t condition_variable = 0;

	TTFFontParser::FontData font_data;
	int8_t error = TTFFontParser::parse_file(font_path, &font_data, &font_parsed, &condition_variable);

	while (!condition_variable) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	getchar();

	return 0;
}
