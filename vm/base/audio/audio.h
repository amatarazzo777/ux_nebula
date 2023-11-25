/*
 * This file is part of the ux_nebula distribution
 * (https://github.com/amatarazzo777/ux_gui_stream).
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
The ability to create an emmersive audio foundation that will be reused
does require many functions of design plan. To list the types of features present 
in context, musical structure,  DAW capabilities and sound for stereo and surround
has a known series of primatives in architecture. Planning implementation
from existing linux code has its platform awareness and downfalls. The positives
are there is a working system that can be studied. Audio mixing, chain loading.
The sound card provisions, are not direct but catalog a mountain of cards
to support. Changing thre port status, etc. The ability to link directly
the sound card, as a function system compoent, exists in the same light
as video. Displaying text, or even playing notes. Extensive amounts 
of code exists to form ideas. As a system linux resource, the main instance of the driver
for sound should be programmed  from for sound. 

Supporting multiple drivers for sound, sound boards, and other aspects 
becomes a tedious model for some technology. Yet sound remains
embarked upon as a select programming protocol. A layer will exist,
and providing the planned mixing capabilities inline. As data
structures most types of processing can be compiled, and reformed.
The effectiveness of BitWig does seem enticing. Yet internally,
too much complexity exists. Because it is a complete application.
It has to provide support for many formats. Using
LLVM in conjunction with language and UI can be advanced.

Sound production in digital form is simply a series of numbers, integer even.
16bit audio is a 16bit integer with a range beteen -32767 and +32767. This integer is 
expects to vary over time to create wave patterns. This number directly changes
the position of the woofer. example, the square wave is simply both range
numbers repeated a certain number of times.Since the information is consumed at 
a particular rate, it must be continually produced to change. 

Some interesting aspects of knwoeldge to think about is how does a system wide floating
point representation change this except during driver communication. Does it change the 
quality, and errors?

*/