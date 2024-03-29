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

#ifndef AGG_VCGEN_MARKERS_TERM_INCLUDED
#define AGG_VCGEN_MARKERS_TERM_INCLUDED

#include "agg_basics.h"
#include "agg_vertex_sequence.h"

namespace agg
{

    //======================================================vcgen_markers_term
    //
    // See Implemantation agg_vcgen_markers_term.cpp
    // Terminal markers generator (arrowhead/arrowtail)
    //
    //------------------------------------------------------------------------
    class vcgen_markers_term
    {
    public:
        vcgen_markers_term()  = default;

        // Vertex Generator Interface
        AGGAPI void remove_all();
        AGGAPI void add_vertex(double x, double y, unsigned cmd);

        // Vertex Source Interface
        AGGAPI void rewind(unsigned path_id);
        AGGAPI unsigned vertex(double* x, double* y);

        vcgen_markers_term(const vcgen_markers_term&) = delete;
        const vcgen_markers_term& operator = (const vcgen_markers_term&) = delete;

    private:

        struct coord_type
        {
            double x, y;

            coord_type() = default;
            coord_type(double x_, double y_) : x(x_), y(y_) {}
        };

        using coord_storage = pod_bvector<coord_type, 6>; 

        coord_storage m_markers;
        unsigned      m_curr_id{0};
        unsigned      m_curr_idx{0};
    };


}

#endif
