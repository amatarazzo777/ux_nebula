/*
 * This file is part of the ux_nebula distribution
 * (https://github.com/amatarazzo777/ux_nebula).
 * Copyright (c) 2023 Anthony Matarazzo.
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

/*
There are multiple image formats, most are published formats. The expectation
that only decoding is being done can be functional. The system layer would not
make visual images and encode them. Or include it? 

The process of color changes, and hue, contrast, blur, convolution matrix operations
resizing operations, resampling from one color space to the other, are necessary for OS
and raster operations.

These classes contains the library functions, source provided in tree for easy compilation.
Most code base algorithms will simply be translated to this library yet remain labeled by license.
Codecs. png, is the notible form for raster and networks. Libraries exist that are extensive.
Is there a one routine codec per image file format? using only the memory to memory sources
to an color space. The library for color space mapping has been utilized and be used by the 
entire system. There should be macros or something for applying two function pointers.
In iterator, and out iterator, with the translation and order math between and applying 
it to the storage.Using the stride method of buffer advancement, in a secondary call, or 
can be interalized allows sub components of the buffer to be translated.

Most likely a system summary and even short language would allow permutation of it as routines.
Imageing the RGB, 256 color, and BGR, being able to be translated with much easier array
access, looping. 
*/