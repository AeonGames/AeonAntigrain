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
// Line dash generator
//
//----------------------------------------------------------------------------
#ifndef AGG_VCGEN_DASH_INCLUDED
#define AGG_VCGEN_DASH_INCLUDED

#include <array>
#include "agg_basics.h"
#include "agg_vertex_sequence.h"

namespace agg
{

    //---------------------------------------------------------------vcgen_dash
    //
    // See Implementation agg_vcgen_dash.cpp
    //
    class vcgen_dash
    {
        enum max_dashes_e
        {
            max_dashes = 32
        };

        enum status_e
        {
            initial,
            ready,
            polyline,
            stop
        };

    public:
        using vertex_storage = vertex_sequence<vertex_dist, 6>;

        AGGAPI vcgen_dash();

        AGGAPI void remove_all_dashes();
        AGGAPI void add_dash(double dash_len, double gap_len);
        AGGAPI void dash_start(double ds);

        void shorten(double s) { m_shorten = s; }
        [[nodiscard]] double shorten() const { return m_shorten; }

        // Vertex Generator Interface
        AGGAPI void remove_all();
        AGGAPI void add_vertex(double x, double y, unsigned cmd);

        // Vertex Source Interface
        AGGAPI void     rewind(unsigned path_id);
        AGGAPI unsigned vertex(double* x, double* y);

        vcgen_dash(const vcgen_dash&) = delete;
        const vcgen_dash& operator = (const vcgen_dash&) = delete;

    private:

        AGGAPI void calc_dash_start(double ds);

        std::array<double,max_dashes> m_dashes{};
        double             m_total_dash_len{0.0};
        unsigned           m_num_dashes{0};
        double             m_dash_start{0.0};
        double             m_shorten{0.0};
        double             m_curr_dash_start{0.0};
        unsigned           m_curr_dash{0};
        double             m_curr_rest;
        const vertex_dist* m_v1;
        const vertex_dist* m_v2;

        vertex_storage m_src_vertices;
        unsigned       m_closed{0};
        status_e       m_status{initial};
        unsigned       m_src_vertex{0};
    };
}

#endif
