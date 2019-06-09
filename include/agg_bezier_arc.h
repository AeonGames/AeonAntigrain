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
// Arc generator. Produces at most 4 consecutive cubic bezier curves, i.e., 
// 4, 7, 10, or 13 vertices.
//
//----------------------------------------------------------------------------

#ifndef AGG_BEZIER_ARC_INCLUDED
#define AGG_BEZIER_ARC_INCLUDED

#include <array>
#include "agg_conv_transform.h"

namespace agg
{

    //-----------------------------------------------------------------------
    AGGAPI void arc_to_bezier(double cx, double cy, double rx, double ry, 
                       double start_angle, double sweep_angle,
                       double* curve);


    //==============================================================bezier_arc
    // 
    // See implemantaion agg_bezier_arc.cpp
    //
    class bezier_arc
    {
    public:
        //--------------------------------------------------------------------
        bezier_arc()  = default;
        bezier_arc(double x,  double y, 
                   double rx, double ry, 
                   double start_angle, 
                   double sweep_angle)
        {
            init(x, y, rx, ry, start_angle, sweep_angle);
        }

        //--------------------------------------------------------------------
        AGGAPI void init(double x,  double y, 
                  double rx, double ry, 
                  double start_angle, 
                  double sweep_angle);

        //--------------------------------------------------------------------
        void rewind(unsigned)
        {
            m_vertex = 0;
        }

        //--------------------------------------------------------------------
        unsigned vertex(double* x, double* y)
        {
            if(m_vertex >= m_num_vertices) return path_cmd_stop;
            *x = m_vertices[m_vertex];
            *y = m_vertices[m_vertex + 1];
            m_vertex += 2;
            return (m_vertex == 2) ? unsigned(path_cmd_move_to) : m_cmd;
        }

        // Supplemantary functions. num_vertices() actually returns doubled 
        // number of vertices. That is, for 1 vertex it returns 2.
        //--------------------------------------------------------------------
        [[nodiscard]] unsigned  num_vertices() const { return m_num_vertices; }
        [[nodiscard]] const double* vertices() const { return m_vertices.data();     }
        double*       vertices()       { return m_vertices.data();     }
 
    private:
        unsigned m_vertex{26};
        unsigned m_num_vertices{0};
        std::array<double,26> m_vertices{};
        unsigned m_cmd{path_cmd_line_to};
    };



    //==========================================================bezier_arc_svg
    // Compute an SVG-style bezier arc. 
    //
    // Computes an elliptical arc from (x1, y1) to (x2, y2). The size and 
    // orientation of the ellipse are defined by two radii (rx, ry) 
    // and an x-axis-rotation, which indicates how the ellipse as a whole 
    // is rotated relative to the current coordinate system. The center 
    // (cx, cy) of the ellipse is calculated automatically to satisfy the 
    // constraints imposed by the other parameters. 
    // large-arc-flag and sweep-flag contribute to the automatic calculations 
    // and help determine how the arc is drawn.
    class bezier_arc_svg
    {
    public:
        //--------------------------------------------------------------------
        bezier_arc_svg() : m_arc() {}

        bezier_arc_svg(double x1, double y1, 
                       double rx, double ry, 
                       double angle,
                       bool large_arc_flag,
                       bool sweep_flag,
                       double x2, double y2) : 
            m_arc() 
        {
            init(x1, y1, rx, ry, angle, large_arc_flag, sweep_flag, x2, y2);
        }

        //--------------------------------------------------------------------
        AGGAPI void init(double x1, double y1, 
                  double rx, double ry, 
                  double angle,
                  bool large_arc_flag,
                  bool sweep_flag,
                  double x2, double y2);

        //--------------------------------------------------------------------
        [[nodiscard]] bool radii_ok() const { return m_radii_ok; }

        //--------------------------------------------------------------------
        void rewind(unsigned)
        {
            m_arc.rewind(0);
        }

        //--------------------------------------------------------------------
        unsigned vertex(double* x, double* y)
        {
            return m_arc.vertex(x, y);
        }

        // Supplemantary functions. num_vertices() actually returns doubled 
        // number of vertices. That is, for 1 vertex it returns 2.
        //--------------------------------------------------------------------
        [[nodiscard]] unsigned  num_vertices() const { return m_arc.num_vertices(); }
        [[nodiscard]] const double* vertices() const { return m_arc.vertices();     }
        double*       vertices()       { return m_arc.vertices();     }

    private:
        bezier_arc m_arc;
        bool       m_radii_ok{false};
    };
}
#endif
