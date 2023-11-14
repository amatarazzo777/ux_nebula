/*
 * This file is part of the ux_gui_stream distribution
 * (https://github.com/amatarazzo777/ux_gui_stream).
 * Copyright (c) 2020 Anthony Matarazzo.
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

/**
 * @author Anthony Matarazzo
 * @file display_list.h
 * @date 10/22/20
 * @version 1.0
 * @brief display list using mutex for storage
 */

#pragma once

// using the object form with templates made more complexity than necessary
// to simply make adding platforms easier, one must make it easy to fill in the template
// Providing the os files within the os directory, even for system, is easy using the form below.
// a one object layer.
// the main ingredient is that in the header file, the names are aliased to the name of the os specific
// this is accomplished with the using c++ keyword.
// os_keyboard_device_t, os_window_manager, 
#if defined(__linux__)
#include <os/linux/os.h>
#include <os/linux/os_interface.h>

#elif defined(_WIN64)

#endif


#include <base/ViewManager.h>
