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
// classes scale_ctrl_impl, scale_ctrl
//
//----------------------------------------------------------------------------

#ifndef AGG_SCALE_CTRL_INCLUDED
#define AGG_SCALE_CTRL_INCLUDED

#include "agg_basics.h"
#include "agg_math.h"
#include "agg_ellipse.h"
#include "agg_trans_affine.h"
#include "agg_color_rgba.h"
#include "agg_ctrl.h"


namespace agg
{

    //------------------------------------------------------------------------
    class scale_ctrl_impl : public ctrl
    {
        enum move_e
        {
            move_nothing,
            move_value1,
            move_value2,
            move_slider
        };

    public:
        AGGCTRLAPI scale_ctrl_impl(double x1, double y1, double x2, double y2, bool flip_y=false);

        AGGCTRLAPI void border_thickness(double t, double extra=0.0);
        AGGCTRLAPI void resize(double x1, double y1, double x2, double y2);
        
        double min_delta() const { return m_min_d; }
        void min_delta(double d) { m_min_d = d; }
        
        double value1() const { return m_value1; }
        AGGCTRLAPI void value1(double value);

        double value2() const { return m_value2; }
        AGGCTRLAPI void value2(double value);

        AGGCTRLAPI void move(double d);

        AGGCTRLAPI bool in_rect(double x, double y) const override;
        AGGCTRLAPI bool on_mouse_button_down(double x, double y) override;
        AGGCTRLAPI bool on_mouse_button_up(double x, double y) override;
        AGGCTRLAPI bool on_mouse_move(double x, double y, bool button_flag) override;
        AGGCTRLAPI bool on_arrow_keys(bool left, bool right, bool down, bool up) override;
        AGGCTRLAPI ~scale_ctrl_impl() override;

        // Vertex source interface
        unsigned num_paths() { return 5; };
        AGGCTRLAPI void     rewind(unsigned path_id);
        AGGCTRLAPI unsigned vertex(double* x, double* y);

    private:
        AGGCTRLAPI void calc_box();

        double   m_border_thickness;
        double   m_border_extra;
        double   m_value1;
        double   m_value2;
        double   m_min_d;
        double   m_xs1;
        double   m_ys1;
        double   m_xs2;
        double   m_ys2;
        double   m_pdx;
        double   m_pdy;
        move_e   m_move_what;
        double   m_vx[32];
        double   m_vy[32];

        ellipse  m_ellipse;

        unsigned m_idx;
        unsigned m_vertex;

    };



    //------------------------------------------------------------------------
    template<class ColorT> class scale_ctrl : public scale_ctrl_impl
    {
    public:
        scale_ctrl(double x1, double y1, double x2, double y2, bool flip_y=false) :
            scale_ctrl_impl(x1, y1, x2, y2, flip_y),
            m_background_color(rgba(1.0, 0.9, 0.8)),
            m_border_color(rgba(0.0, 0.0, 0.0)),
            m_pointers_color(rgba(0.8, 0.0, 0.0, 0.8)),
            m_slider_color(rgba(0.2, 0.1, 0.0, 0.6))
        {
            m_colors[0] = &m_background_color;
            m_colors[1] = &m_border_color;
            m_colors[2] = &m_pointers_color;
            m_colors[3] = &m_pointers_color;
            m_colors[4] = &m_slider_color;
        }
          

        void background_color(const ColorT& c) { m_background_color = c; }
        void border_color(const ColorT& c)     { m_border_color = c; }
        void pointers_color(const ColorT& c)   { m_pointers_color = c; }
        void slider_color(const ColorT& c)     { m_slider_color = c; }

        const ColorT& color(unsigned i) const { return *m_colors[i]; } 

    private:
        AGGCTRLAPI scale_ctrl(const scale_ctrl<ColorT>&);
        AGGCTRLAPI const scale_ctrl<ColorT>& operator = (const scale_ctrl<ColorT>&);

        ColorT m_background_color;
        ColorT m_border_color;
        ColorT m_pointers_color;
        ColorT m_slider_color;
        ColorT* m_colors[5];
    };





}
#endif
