/*****************************************************************************
RozettiCore. Copyright 2015 Conrad Rozetti, crz@rozetti.org.
******************************************************************************
The MIT License (MIT)

Copyright(c) 2015 Conrad Rozetti

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*****************************************************************************/

#pragma once

#include <cmath>
#include <cfloat>

#include "rz_core_macros.h"

// crz: math

#include "rz_core_vector3.h"
#include "rz_core_vector2.h"
#include "rz_core_matrix.h"
#include "rz_core_bounding_box.h"
#include "rz_core_bounding_sphere.h"
#include "rz_core_rectangle.h"
#include "rz_core_plane.h"
#include "rz_core_ray.h"
#include "rz_core_quaternion.h"

#include "rz_core_matrix_factory.h"
#include "rz_core_vector3_factory.h"
#include "rz_core_vector2_factory.h"

#include "rz_core_interpolation.h"
#include "rz_core_angles.h"
#include "rz_core_math_templates.h"
#include "rz_core_random.h"

// crz: algorithm

#include "rz_core_range.h"

// crz: string

#include "rz_core_printf.h"
#include "rz_core_substr.h"
#include "rz_core_conversion.h"
#include "rz_core_indent.h"

// crz: dom

#include "rz_core_dom_document.h"
#include "rz_core_dom_node.h"

// crz: game

#include "rz_core_game.h"

// crz: time

#include "rz_core_clock.h"
#include "rz_core_lap_timer.h"

// crz: script

#include "rz_core_lua.h"
#include "rz_core_script_operations.h"
#include "rz_core_lua_scriptable_object_operation.h"

// crz: serialisation

#include "rz_core_serialisable.h"

// crz: object

#include "rz_core_object_interfaces.h"

// crz:patterns

#include "rz_core_finally_pattern.h"
#include "rz_core_visitor_pattern.h"

