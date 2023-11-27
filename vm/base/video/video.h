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
Some playing video require a context. Some video is encrypted by private licensed methods. As well, 
the UDP vs local file can play a part in the algorithm. At times video can connect to multipel areas
of the system, background of a screen. Video also should be able to be stesiled, have 
transparency as well.

There are multiple methods to compress video data, mp4 for consumer seems to be the base format
most provide, yet mixed with different styles.

Video codes per frame can be rather small code fragments. An encoder is more extensive
usually, unsure. Yet as a visitor pattern, a frame buffer decode is usual. A common set of routines
can be employed to scale to function interface size, provide color convolusion filters
to change various aspects of the image quality.

Most formats are published.
The ability to create a new video format for raw buffer input so that the effects of time and audio
playback can be syncronized together.

There is a need for better and smarter compression due to macroblock size of the hd video pixel space.
Perhaps a dynamic one that fans out until a color tollerance in the coverage areas has been met.
How to mark the group to relate.There is a bounds. An area, a number of macro block pixels. They
have direction relative to each other. Together they comprise a percentage of the video. Together
they comprise a distance relative to the center.  


libvlc
https://code.videolan.org/videolan/libvlcpp/-/blob/master/examples/helloworld/main.cpp?ref_type=heads

ffmpeg

https://en.wikipedia.org/wiki/Libavcodec

the use of the libav codecs is most likely the suited based code. for video and audio.
the processing most likely in another system ring.

the facilities and temptation to write code
code processing and activating sound buffering is likely handled by the ffmpeg library.
At times the interface is so generalized, or there are multiple routines.
 Simply, to inform the decoder of where the memory buffer is and the size
 is the output.


 Most likely a full frame buffer with audio and video mixing. Specific of playing some types of 
 audio require audio equiptment. The range of audio effects is often simple of types of movies.
 Limiter. A system that uses the event and call back mechanism of the base system, file mapping
 memory can simplify the buffering system that syncronizes the audio and video image together.
 Most of these systems are built into the stream, that is the stream is already balanced.

*/
