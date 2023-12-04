
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
The timeline object serves as a method of receiving calls at a specific
rate or in the future. Objects are inserted into the timeline, and 
expect to trigger from that position once the transport is rolling.
The main acquisition is each object accomplishing complete work before
overrun. Processing overrun in a system can be a problem if the timeline
is going to be used for real time purposes. The usefulness and central
positioning of timing functions, and pointer dispatch, is accuracry, 
management and reusability. 

Perhaps as a template oriented design for c++ users yet having a inner system design
to be reused. The linux system has a timing function base, create_timer, and also sig_alarm.
Yet the ability to receive high performance timers, fractions of a second is unknown 
from these api. Or if another one is required. There is a tick per second
count as well. The frequency of scan can also be increased depending on settings in the kernel.
Typically base settings such as measured in Hz, set this in menu_config.

*/