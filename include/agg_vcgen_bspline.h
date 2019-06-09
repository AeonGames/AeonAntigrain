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

#ifndef AGG_VCGEN_BSPLINE_INCLUDED
#define AGG_VCGEN_BSPLINE_INCLUDED

#include "agg_basics.h"
#include "agg_array.h"
#include "agg_bspline.h"


namespace agg
{

    //==========================================================vcgen_bspline
    class vcgen_bspline
    {
        enum status_e
        {
            initial,
            ready,
            polygon,
            end_poly,
            stop
        };

    public:
        typedef pod_bvector<point_d, 6> vertex_storage;

        AGGAPI vcgen_bspline();

        void interpolation_step(double v) { m_interpolation_step = v; }
        double interpolation_step() const { return m_interpolation_step; }

        // Vertex Generator Interface
        AGGAPI void remove_all();
        AGGAPI void add_vertex(double x, double y, unsigned cmd);

        // Vertex Source Interface
        AGGAPI void     rewind(unsigned path_id);
        AGGAPI unsigned vertex(double* x, double* y);

    private:
        AGGAPI vcgen_bspline(const vcgen_bspline&);
        AGGAPI const vcgen_bspline& operator = (const vcgen_bspline&);

        vertex_storage m_src_vertices;
        bspline        m_spline_x;
        bspline        m_spline_y;
        double         m_interpolation_step;
        unsigned       m_closed;
        status_e       m_status;
        unsigned       m_src_vertex;
        double         m_cur_abscissa;
        double         m_max_abscissa;
    };
}
#endif
