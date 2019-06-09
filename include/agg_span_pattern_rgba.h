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
// Adaptation for high precision colors has been sponsored by 
// Liberty Technology Systems, Inc., visit http://lib-sys.com
//
// Liberty Technology Systems, Inc. is the provider of
// PostScript and PDF technology for software developers.
// 
//----------------------------------------------------------------------------


#ifndef AGG_SPAN_PATTERN_RGBA_INCLUDED
#define AGG_SPAN_PATTERN_RGBA_INCLUDED

#include "agg_basics.h"

namespace agg
{

    //======================================================span_pattern_rgba
    template<class Source> class span_pattern_rgba
    {
    public:
        using source_type = Source;
        using color_type = typename source_type::color_type;
        using order_type = typename source_type::order_type;
        using value_type = typename color_type::value_type;
        using calc_type = typename color_type::calc_type;

        //--------------------------------------------------------------------
        span_pattern_rgba() {}
        span_pattern_rgba(source_type& src, 
                          unsigned offset_x, unsigned offset_y) :
            m_src(&src),
            m_offset_x(offset_x),
            m_offset_y(offset_y)
        {}

        //--------------------------------------------------------------------
        void   attach(source_type& v)      { m_src = &v; }
               source_type& source()       { return *m_src; }
        const  source_type& source() const { return *m_src; }

        //--------------------------------------------------------------------
        void       offset_x(unsigned v) { m_offset_x = v; }
        void       offset_y(unsigned v) { m_offset_y = v; }
        unsigned   offset_x() const { return m_offset_x; }
        unsigned   offset_y() const { return m_offset_y; }
        void       alpha(value_type) {}
        value_type alpha() const { return 0; }

        //--------------------------------------------------------------------
        void prepare() {}
        void generate(color_type* span, int x, int y, unsigned len)
        {   
            x += m_offset_x;
            y += m_offset_y;
            const value_type* p = (const value_type*)m_src->span(x, y, len);
            do
            {
                span->r = p[order_type::R];
                span->g = p[order_type::G];
                span->b = p[order_type::B];
                span->a = p[order_type::A];
                p = (const value_type*)m_src->next_x();
                ++span;
            }
            while(--len);
        }

    private:
        source_type* m_src;
        unsigned     m_offset_x;
        unsigned     m_offset_y;

    };

}

#endif

