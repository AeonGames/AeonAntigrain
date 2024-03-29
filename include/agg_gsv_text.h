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
//
// Class gsv_text
//
//----------------------------------------------------------------------------

#ifndef AGG_GSV_TEXT_INCLUDED
#define AGG_GSV_TEXT_INCLUDED

#include <array>
#include "agg_array.h"
#include "agg_conv_stroke.h"
#include "agg_conv_transform.h"

namespace agg
{
    //---------------------------------------------------------------gsv_text
    //
    // See Implementation agg_gsv_text.cpp 
    //
    class gsv_text
    {
        enum status
        {
            initial,
            next_char,
            start_glyph,
            glyph
        };

    public:
        AGGAPI gsv_text();
        AGGAPI void font(const void* font);
        void flip(bool flip_y) { m_flip = flip_y; }
        AGGAPI void load_font(const char* file);
        AGGAPI void size(double height, double width=0.0);
        AGGAPI void space(double space);
        AGGAPI void line_space(double line_space);
        AGGAPI void start_point(double x, double y);
        AGGAPI void text(const char* text);
        
        AGGAPI double text_width();

        AGGAPI void rewind(unsigned path_id);
        AGGAPI unsigned vertex(double* x, double* y);

        gsv_text(const gsv_text&) = delete;
        const gsv_text& operator = (const gsv_text&) = delete;

    private:
        int16u value(const int8u* p) const
        {
            int16u v;
            if(m_big_endian)
            {
                 *(int8u*)&v      = p[1];
                *((int8u*)&v + 1) = p[0];
            }
            else
            {
                 *(int8u*)&v      = p[0];
                *((int8u*)&v + 1) = p[1];
            }
            return v;
        }

    private:
        double          m_x{0.0};
        double          m_y{0.0};
        double          m_start_x{0.0};
        double          m_width{10.0};
        double          m_height{0.0};
        double          m_space{0.0};
        double          m_line_space{0.0};
        std::array<char,2> m_chr{};
        char*           m_text;
        pod_array<char> m_text_buf;
        char*           m_cur_chr;
        const void*     m_font;
        pod_array<char> m_loaded_font;
        status          m_status{initial};
        bool            m_big_endian{false};
        bool            m_flip{false};
        int8u*          m_indices;
        int8*           m_glyphs;
        int8*           m_bglyph;
        int8*           m_eglyph;
        double          m_w;
        double          m_h;
    };

    //--------------------------------------------------------gsv_text_outline
    template<class Transformer = trans_affine> class gsv_text_outline
    {
    public:
        gsv_text_outline(gsv_text& text, Transformer& trans) :
          m_polyline(text),
          m_trans(m_polyline, trans)
        {
        }

        void width(double w) 
        { 
            m_polyline.width(w); 
        }

        void transformer(const Transformer* trans) 
        {
            m_trans->transformer(trans);
        }

        void rewind(unsigned path_id) 
        { 
            m_trans.rewind(path_id); 
            m_polyline.line_join(round_join);
            m_polyline.line_cap(round_cap);
        }

        unsigned vertex(double* x, double* y)
        {
            return m_trans.vertex(x, y);
        }

    private:
        conv_stroke<gsv_text> m_polyline;
        conv_transform<conv_stroke<gsv_text>, Transformer> m_trans;
    };
}

#endif
