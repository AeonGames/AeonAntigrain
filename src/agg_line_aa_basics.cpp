/*
Copyright (C) 2019 Rodrigo Jose Hernandez Cordoba

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
//----------------------------------------------------------------------------
// Anti-Grain Geometry - Version 2.4
// Copyright (C) 2002-2005 Maxim Shemanarev (http://www.antigrain.com)
//
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//
//----------------------------------------------------------------------------
// Contact: mcseem@antigrain.com
//          mcseemagg@yahoo.com
//          http://www.antigrain.com
//----------------------------------------------------------------------------

#include <cmath>
#include "agg_line_aa_basics.h"

namespace agg
{
    //-------------------------------------------------------------------------
    // The number of the octant is determined as a 3-bit value as follows:
    // bit 0 = vertical flag
    // bit 1 = sx < 0
    // bit 2 = sy < 0
    //
    // [N] shows the number of the orthogonal quadrant
    // <M> shows the number of the diagonal quadrant
    //               <1>
    //   [1]          |          [0]
    //       . (3)011 | 001(1) .
    //         .      |      .
    //           .    |    . 
    //             .  |  . 
    //    (2)010     .|.     000(0)
    // <2> ----------.+.----------- <0>
    //    (6)110   .  |  .   100(4)
    //           .    |    .
    //         .      |      .
    //       .        |        .
    //         (7)111 | 101(5) 
    //   [2]          |          [3]
    //               <3> 
    //                                                        0,1,2,3,4,5,6,7 
    std::array<const int8u,8> line_parameters::s_orthogonal_quadrant{ 0,0,1,1,3,3,2,2 };
    std::array<const int8u,8> line_parameters::s_diagonal_quadrant{ 0,1,2,1,0,3,2,3 };



    //-------------------------------------------------------------------------
    void bisectrix(const line_parameters& l1, 
                   const line_parameters& l2, 
                   int* x, int* y)
    {
        double k = double(l2.len) / double(l1.len);
        double tx = l2.x2 - (l2.x1 - l1.x1) * k;
        double ty = l2.y2 - (l2.y1 - l1.y1) * k;

        //All bisectrices must be on the right of the line
        //If the next point is on the left (l1 => l2.2)
        //then the bisectix should be rotated by 180 degrees.
        if(double(l2.x2 - l2.x1) * double(l2.y1 - l1.y1) <
           double(l2.y2 - l2.y1) * double(l2.x1 - l1.x1) + 100.0)
        {
            tx -= (tx - l2.x1) * 2.0;
            ty -= (ty - l2.y1) * 2.0;
        }

        // Check if the bisectrix is too short
        double dx = tx - l2.x1;
        double dy = ty - l2.y1;
        if((int)std::sqrt(dx * dx + dy * dy) < line_subpixel_scale)
        {
            *x = (l2.x1 + l2.x1 + (l2.y1 - l1.y1) + (l2.y2 - l2.y1)) >> 1;
            *y = (l2.y1 + l2.y1 - (l2.x1 - l1.x1) - (l2.x2 - l2.x1)) >> 1;
            return;
        }
        *x = iround(tx);
        *y = iround(ty);
    }

}
