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
#ifndef AGG_PATTERN_FILTERS_RGBA8_INCLUDED
#define AGG_PATTERN_FILTERS_RGBA8_INCLUDED

#include "agg_basics.h"
#include "agg_line_aa_basics.h"
#include "agg_color_rgba.h"


namespace agg
{

    //=======================================================pattern_filter_nn
    template<class ColorT> struct pattern_filter_nn
    {
        using color_type = ColorT;
        static unsigned dilation() { return 0; }

        static void AGG_INLINE pixel_low_res(color_type const* const* buf, 
                                             color_type* p, int x, int y)
        {
            *p = buf[y][x];
        }

        static void AGG_INLINE pixel_high_res(color_type const* const* buf, 
                                              color_type* p, int x, int y)
        {
            *p = buf[y >> line_subpixel_shift]
                    [x >> line_subpixel_shift];
        }
    };

    using pattern_filter_nn_rgba8 = pattern_filter_nn<rgba8> ;
    using pattern_filter_nn_rgba16 = pattern_filter_nn<rgba16>;


    //===========================================pattern_filter_bilinear_rgba
    template<class ColorT> struct pattern_filter_bilinear_rgba
    {
        using color_type = ColorT;
        using value_type = typename color_type::value_type;
        using calc_type = typename color_type::calc_type;


        static unsigned dilation() { return 1; }

        static AGG_INLINE void pixel_low_res(color_type const* const* buf, 
                                             color_type* p, int x, int y)
        {
            *p = buf[y][x];
        }

        static AGG_INLINE void pixel_high_res(color_type const* const* buf, 
                                              color_type* p, int x, int y)
        {
            calc_type r, g, b, a;
            r = g = b = a = 0;

            calc_type weight;
            int x_lr = x >> line_subpixel_shift;
            int y_lr = y >> line_subpixel_shift;

            x &= line_subpixel_mask;
            y &= line_subpixel_mask;
            const color_type* ptr = buf[y_lr] + x_lr;

            weight = (line_subpixel_scale - x) * 
                     (line_subpixel_scale - y);
            r += weight * ptr->r;
            g += weight * ptr->g;
            b += weight * ptr->b;
            a += weight * ptr->a;

            ++ptr;

            weight = x * (line_subpixel_scale - y);
            r += weight * ptr->r;
            g += weight * ptr->g;
            b += weight * ptr->b;
            a += weight * ptr->a;

            ptr = buf[y_lr + 1] + x_lr;

            weight = (line_subpixel_scale - x) * y;
            r += weight * ptr->r;
            g += weight * ptr->g;
            b += weight * ptr->b;
            a += weight * ptr->a;

            ++ptr;

            weight = x * y;
            r += weight * ptr->r;
            g += weight * ptr->g;
            b += weight * ptr->b;
            a += weight * ptr->a;

            p->r = (value_type)color_type::downshift(r, line_subpixel_shift * 2);
            p->g = (value_type)color_type::downshift(g, line_subpixel_shift * 2);
            p->b = (value_type)color_type::downshift(b, line_subpixel_shift * 2);
            p->a = (value_type)color_type::downshift(a, line_subpixel_shift * 2);
        }
    };

    using pattern_filter_bilinear_rgba8 = pattern_filter_bilinear_rgba<rgba8> ;
    using pattern_filter_bilinear_rgba16 = pattern_filter_bilinear_rgba<rgba16>;
    using pattern_filter_bilinear_rgba32 = pattern_filter_bilinear_rgba<rgba32>;
}

#endif
