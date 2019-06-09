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
// classes dda_line_interpolator, dda2_line_interpolator
//
//----------------------------------------------------------------------------

#ifndef AGG_DDA_LINE_INCLUDED
#define AGG_DDA_LINE_INCLUDED

#include <cstdlib>
#include "agg_basics.h"

namespace agg
{

    //===================================================dda_line_interpolator
    template<int FractionShift, int YShift=0> class dda_line_interpolator
    {
    public:
        //--------------------------------------------------------------------
        dda_line_interpolator() = default;

        //--------------------------------------------------------------------
        dda_line_interpolator(int y1, int y2, unsigned count) :
            m_y(y1),
            m_inc(((y2 - y1) << FractionShift) / int(count)),
            m_dy(0)
        {
        }

        //--------------------------------------------------------------------
        void operator ++ ()
        {
            m_dy += m_inc;
        }

        //--------------------------------------------------------------------
        void operator -- ()
        {
            m_dy -= m_inc;
        }

        //--------------------------------------------------------------------
        void operator += (unsigned n)
        {
            m_dy += m_inc * n;
        }

        //--------------------------------------------------------------------
        void operator -= (unsigned n)
        {
            m_dy -= m_inc * n;
        }


        //--------------------------------------------------------------------
        [[nodiscard]] int y()  const { return m_y + (m_dy >> (FractionShift-YShift)); }
        [[nodiscard]] int dy() const { return m_dy; }


    private:
        int m_y;
        int m_inc;
        int m_dy;
    };





    //=================================================dda2_line_interpolator
    class dda2_line_interpolator
    {
    public:
        using save_data_type = int;
        enum save_size_e { save_size = 2 };

        //--------------------------------------------------------------------
        dda2_line_interpolator() = default;

        //-------------------------------------------- Forward-adjusted line
        dda2_line_interpolator(int y1, int y2, int count) :
            m_cnt(count <= 0 ? 1 : count),
            m_lft((y2 - y1) / m_cnt),
            m_rem((y2 - y1) % m_cnt),
            m_mod(m_rem),
            m_y(y1)
        {
            if(m_mod <= 0)
            {
                m_mod += count;
                m_rem += count;
                m_lft--;
            }
            m_mod -= count;
        }

        //-------------------------------------------- Backward-adjusted line
        dda2_line_interpolator(int y1, int y2, int count, int) :
            m_cnt(count <= 0 ? 1 : count),
            m_lft((y2 - y1) / m_cnt),
            m_rem((y2 - y1) % m_cnt),
            m_mod(m_rem),
            m_y(y1)
        {
            if(m_mod <= 0)
            {
                m_mod += count;
                m_rem += count;
                m_lft--;
            }
        }

        //-------------------------------------------- Backward-adjusted line
        dda2_line_interpolator(int y, int count) :
            m_cnt(count <= 0 ? 1 : count),
            m_lft(y / m_cnt),
            m_rem(y % m_cnt),
            m_mod(m_rem),
            m_y(0)
        {
            if(m_mod <= 0)
            {
                m_mod += count;
                m_rem += count;
                m_lft--;
            }
        }


        //--------------------------------------------------------------------
        void save(save_data_type* data) const
        {
            data[0] = m_mod;
            data[1] = m_y;
        }

        //--------------------------------------------------------------------
        void load(const save_data_type* data)
        {
            m_mod = data[0];
            m_y   = data[1];
        }

        //--------------------------------------------------------------------
        void operator++()
        {
            m_mod += m_rem;
            m_y += m_lft;
            if(m_mod > 0)
            {
                m_mod -= m_cnt;
                m_y++;
            }
        }

        //--------------------------------------------------------------------
        void operator--()
        {
            if(m_mod <= m_rem)
            {
                m_mod += m_cnt;
                m_y--;
            }
            m_mod -= m_rem;
            m_y -= m_lft;
        }

        //--------------------------------------------------------------------
        void adjust_forward()
        {
            m_mod -= m_cnt;
        }

        //--------------------------------------------------------------------
        void adjust_backward()
        {
            m_mod += m_cnt;
        }

        //--------------------------------------------------------------------
        [[nodiscard]] int mod() const { return m_mod; }
        [[nodiscard]] int rem() const { return m_rem; }
        [[nodiscard]] int lft() const { return m_lft; }

        //--------------------------------------------------------------------
        [[nodiscard]] int y() const { return m_y; }

    private:
        int m_cnt;
        int m_lft;
        int m_rem;
        int m_mod;
        int m_y;
    };







    //---------------------------------------------line_bresenham_interpolator
    class line_bresenham_interpolator
    {
    public:
        enum subpixel_scale_e
        {
            subpixel_shift = 8,
            subpixel_scale = 1 << subpixel_shift,
            subpixel_mask  = subpixel_scale - 1
        };

        //--------------------------------------------------------------------
        static int line_lr(int v) { return v >> subpixel_shift; }

        //--------------------------------------------------------------------
        line_bresenham_interpolator(int x1, int y1, int x2, int y2) :
            m_x1_lr(line_lr(x1)),
            m_y1_lr(line_lr(y1)),
            m_x2_lr(line_lr(x2)),
            m_y2_lr(line_lr(y2)),
            m_ver(std::abs(m_x2_lr - m_x1_lr) < std::abs(m_y2_lr - m_y1_lr)),
            m_len(m_ver ? std::abs(m_y2_lr - m_y1_lr) : 
                          std::abs(m_x2_lr - m_x1_lr)),
            m_inc(m_ver ? ((y2 > y1) ? 1 : -1) : ((x2 > x1) ? 1 : -1)),
            m_interpolator(m_ver ? x1 : y1, 
                           m_ver ? x2 : y2, 
                           m_len)
        {
        }
    
        //--------------------------------------------------------------------
        [[nodiscard]] bool     is_ver() const { return m_ver; }
        [[nodiscard]] unsigned len()    const { return m_len; }
        [[nodiscard]] int      inc()    const { return m_inc; }

        //--------------------------------------------------------------------
        void hstep()
        {
            ++m_interpolator;
            m_x1_lr += m_inc;
        }

        //--------------------------------------------------------------------
        void vstep()
        {
            ++m_interpolator;
            m_y1_lr += m_inc;
        }

        //--------------------------------------------------------------------
        [[nodiscard]] int x1() const { return m_x1_lr; }
        [[nodiscard]] int y1() const { return m_y1_lr; }
        [[nodiscard]] int x2() const { return line_lr(m_interpolator.y()); }
        [[nodiscard]] int y2() const { return line_lr(m_interpolator.y()); }
        [[nodiscard]] int x2_hr() const { return m_interpolator.y(); }
        [[nodiscard]] int y2_hr() const { return m_interpolator.y(); }

    private:
        int                    m_x1_lr;
        int                    m_y1_lr;
        int                    m_x2_lr;
        int                    m_y2_lr;
        bool                   m_ver;
        unsigned               m_len;
        int                    m_inc;
        dda2_line_interpolator m_interpolator;

    };


}



#endif
