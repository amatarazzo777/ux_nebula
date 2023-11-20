/*
  vector_font.cpp

   Created on: Nov 7, 2023
       Author: anthonym
 */

/*
  Many have tried before and simply decided to increase complexity. Yet as a
  font object, can more intelligent decisions be made by the system as a group.

 */
#include "../vm.h"

void viewManager::vector_font::load_font(void) {
  std::ifstream istrm(filename, std::ios::binary);
  uint16_t count;
  char szstring[255];

  std::string filename = "/home/anthonym/source/Lato-Regular.vfont";

  // file format for the vfont file system,
  // "vfont 1.0";
  istrm.read(szstring, 10);

  // number of characters in the name and the text.
  istrm.read(reinterpret_cast<char *>(&font_count), sizeof(uint16_t));

  // set for multiple fonts, change later to use compression and file name
  // directory
  for (uint16_t n = 0; n < font_count; n++) {
    ostrm.read(reinterpret_cast<char *>(&count), sizeof(uint16_t));

    istrm.read(szstring, count);
    font_names.push_back(szstring);

    istrm.read(reinterpret_cast<char *>(&encodingID), sizeof(uint16_t));
    istrm.read(reinterpret_cast<char *>(&languageID), sizeof(uint16_t));

    /*
     ostrm.write(reinterpret_cast<char *>(&n. meta_data.unitsPerEm),
     sizeof(uint16_t)); ostrm.write(reinterpret_cast<char
     *>(&n.meta_data.Ascender), sizeof(uint16_t));
     ostrm.write(reinterpret_cast<char *>(&n.meta_data.Descender),
     sizeof(uint16_t));
     */

    // number of glyphs
    istrm.read(reinterpret_cast<char *>(&count), sizeof(uint16_t));
    glyph_count = count;

    for (uint16_t cnt = 0; cnt <= glyph_count; cnt++) {
      glyph_t gl;

      istrm.read(reinterpret_cast<const char *>(&gl.character),
                 sizeof(uint32_t));
      istrm.read(reinterpret_cast<const char *>(&gl.glyph_index),
                 sizeof(uint16_t));
      istrm.read(reinterpret_cast<const char *>(&gl.advance_width),
                 sizeof(uint16_t));
      istrm.read(reinterpret_cast<const char *>(&gl.left_side_bearing),
                 sizeof(uint16_t));
      istrm.read(reinterpret_cast<const char *>(&gl.bounding_box),
                 4 * sizeof(int16_t));

      uint16_t path_cnt;
      istrm.read(reinterpret_cast<char *>(&path_cnt), sizeof(uint16_t));

      for (uint16_t cnt2 = 0; cnt2 < path_cnt; cnt2++) {
        uint16 point_count;

        ostrm.read(reinterpret_cast<char *>(&point_count), sizeof(uint16_t));

        for (uint16_t cnt3 = 0; cnt3 < point_cnt; cnt3++) {
          glyph_t::path_t points;
          for (uint16_t cnt4 = 0; cnt4 < 3; cnt4++) {

            glyph_t::point_t point;

            ostrm.read(reinterpret_cast<const char *>(&point.x), sizeof(float));
            ostrm.read(reinterpret_cast<const char *>(&point.y), sizeof(float));
            points.push_back(point);
          }

          paths.push_back(points);
        }
      }

      glyphs[gl.character] = gl;
    }
  }
}
