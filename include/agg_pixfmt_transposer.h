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

#ifndef AGG_PIXFMT_TRANSPOSER_INCLUDED
#define AGG_PIXFMT_TRANSPOSER_INCLUDED

#include "agg_basics.h"

namespace agg
{
    //=======================================================pixfmt_transposer
    template<class PixFmt> class pixfmt_transposer
    {
    public:
        using pixfmt_type = PixFmt;
        using color_type = typename pixfmt_type::color_type;
        using row_data = typename pixfmt_type::row_data;
        using value_type = typename color_type::value_type;
        using calc_type = typename color_type::calc_type;

        //--------------------------------------------------------------------
        pixfmt_transposer() : m_pixf(0) {}
        explicit pixfmt_transposer(pixfmt_type& pixf) : m_pixf(&pixf) {}
        void attach(pixfmt_type& pixf) { m_pixf = &pixf; }

        //--------------------------------------------------------------------
        AGG_INLINE unsigned width()  const { return m_pixf->height();  }
        AGG_INLINE unsigned height() const { return m_pixf->width(); }

        //--------------------------------------------------------------------
        AGG_INLINE color_type pixel(int x, int y) const
        {
            return m_pixf->pixel(y, x);
        }

        //--------------------------------------------------------------------
        AGG_INLINE void copy_pixel(int x, int y, const color_type& c)
        {
            m_pixf->copy_pixel(y, x, c);
        }

        //--------------------------------------------------------------------
        AGG_INLINE void blend_pixel(int x, int y, 
                                    const color_type& c, 
                                    int8u cover)
        {
            m_pixf->blend_pixel(y, x, c, cover);
        }

        //--------------------------------------------------------------------
        AGG_INLINE void copy_hline(int x, int y, 
                                   unsigned len, 
                                   const color_type& c)
        {
            m_pixf->copy_vline(y, x, len, c);
        }

        //--------------------------------------------------------------------
        AGG_INLINE void copy_vline(int x, int y,
                                   unsigned len, 
                                   const color_type& c)
        {
            m_pixf->copy_hline(y, x, len, c);
        }

        //--------------------------------------------------------------------
        AGG_INLINE void blend_hline(int x, int y,
                                    unsigned len, 
                                    const color_type& c,
                                    int8u cover)
        {
            m_pixf->blend_vline(y, x, len, c, cover);
        }

        //--------------------------------------------------------------------
        AGG_INLINE void blend_vline(int x, int y,
                                    unsigned len, 
                                    const color_type& c,
                                    int8u cover)
        {
            m_pixf->blend_hline(y, x, len, c, cover);
        }

        //--------------------------------------------------------------------
        AGG_INLINE void blend_solid_hspan(int x, int y,
                                          unsigned len, 
                                          const color_type& c,
                                          const int8u* covers)
        {
            m_pixf->blend_solid_vspan(y, x, len, c, covers);
        }

        //--------------------------------------------------------------------
        AGG_INLINE void blend_solid_vspan(int x, int y,
                                          unsigned len, 
                                          const color_type& c,
                                          const int8u* covers)
        {
            m_pixf->blend_solid_hspan(y, x, len, c, covers);
        }

        //--------------------------------------------------------------------
        AGG_INLINE void copy_color_hspan(int x, int y,
                                         unsigned len, 
                                         const color_type* colors)
        {
            m_pixf->copy_color_vspan(y, x, len, colors);
        }

        //--------------------------------------------------------------------
        AGG_INLINE void copy_color_vspan(int x, int y,
                                         unsigned len, 
                                         const color_type* colors)
        {
            m_pixf->copy_color_hspan(y, x, len, colors);
        }

        //--------------------------------------------------------------------
        AGG_INLINE void blend_color_hspan(int x, int y,
                                          unsigned len, 
                                          const color_type* colors,
                                          const int8u* covers,
                                          int8u cover)
        {
            m_pixf->blend_color_vspan(y, x, len, colors, covers, cover);
        }

        //--------------------------------------------------------------------
        AGG_INLINE void blend_color_vspan(int x, int y,
                               unsigned len, 
                               const color_type* colors,
                               const int8u* covers,
                               int8u cover)
        {
            m_pixf->blend_color_hspan(y, x, len, colors, covers, cover);
        }

    private:
        pixfmt_type* m_pixf;
    };
}

#endif


