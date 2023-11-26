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

Some interesting aspects of knowledge to think about is how does a system wide floating
point representation change this except during driver communication. Does it change the 
quality, and errors?


Connecting these objects to the generic os abstract class in desireable. 
Keeping the code base with few audio codes. .flac seems good for losless, and mp3 higher bitrate. 
mp3 is a licenses form, while ogg vorbis has a public domain version. Perhaps go with ogg source.


The possiblity to control music daw structures for tracks, midi playback, and rendering mixdown.
Automating some types of signal processing for balancing is useful. 

The sound system at the OS system layer at the OS layer should have the capability to mix audio
in chains, provide this service to multiple clients perhaps, yet the effects system dsp elements,
should transpire running per application process space, or on a different ring.

The necessity of object oriented design for a language specific for
dsp plugins is the most effective. As a base, the plugin has some distict input and output
functions.Providing for UI description is a better decision at another software layer. while
the audio object with states and memory be applied as a specific general purpose programming language.
Function interface visitor prototypes for calling events. Midi vs Audio. 
A sampler with velocity mixture, ADSR. Enevelope and automation. Rates, osculators, timing
functions, noises. FM, wave form producing language with algorithic editing of 
chunk audio. Live verses real time.


Text to speech engines are prized. I gather investments is in more dynamic modeling
of the voice and pronouncements. Most, even great sounding, seem in effective. Yet often
when providing such obsecurities to voice, it may make them un intelligellible because of the amount
of variance. The capability to be enticed is better.

The magesty of acting, and other types of forward body actions create a one line story. 
You could have a program laugh very loud, but the movements of the mouth and bones
do not match on live entertainment visually. So an accurate system would be 
compelled to tie these together, suited for daft play. Games and media would make the 
best canidate action for this type. Simply applying that it is turned off, is a matter of tts
engine sound design.

There are many problems to be enticed to solve which are held in other sound engines. 
Web oriented. Some source code does exist. Newer methods have been made. Computer 
voices that even mimic characterizations. Provided with an input of like software,
can be useful. Most likely not a system level compoent however. No reason the CPU
needs to talk. For application layer, a third party tts is almost necessary.


Some notible audio can be connected to usb. USB of multiple types and multiple ports.
Lucikly the format is very universal for audio card, and digital microphones. 


Using the generic operating system object, to work with basic audio output
and control the volume. Mixing multiple audio together and stop start.

Timing syncronization can occur using the same event systems used by animation.


These classes attach to the main generic_os_t function implemention of class.

https://xiph.org/ao/
Alsa
libasound
<alsa/asoundlib.h>



*/
namespace viewManager {
    enum class sampleRate {
        
    };

    class audio_t  {
        audio_t() =0;;
        audio_t(std::shared_ptr<os_interface_manager_t> _os) : m_os(_os) {};
        std::shared_ptr<os_interface_manager_t> m_os;
        
        void play(unsigned char *data, std::size_t _size);
        void stop();
        void pause();
        void setVolume();
    }
}