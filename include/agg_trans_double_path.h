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

#ifndef AGG_TRANS_DOUBLE_PATH_INCLUDED
#define AGG_TRANS_DOUBLE_PATH_INCLUDED

#include "agg_basics.h"
#include "agg_vertex_sequence.h"

namespace agg
{
    
    // See also: agg_trans_double_path.cpp
    //
    //-------------------------------------------------------trans_double_path
    class trans_double_path
    {
        enum status_e
        {
            initial,
            making_path,
            ready
        };

    public:
        typedef vertex_sequence<vertex_dist, 6> vertex_storage;

        AGGAPI trans_double_path();

        //--------------------------------------------------------------------
        void   base_length(double v)  { m_base_length = v; }
        double base_length() const { return m_base_length; }

        //--------------------------------------------------------------------
        void   base_height(double v)  { m_base_height = v; }
        double base_height() const { return m_base_height; }

        //--------------------------------------------------------------------
        void preserve_x_scale(bool f) { m_preserve_x_scale = f;    }
        bool preserve_x_scale() const { return m_preserve_x_scale; }

        //--------------------------------------------------------------------
        AGGAPI void reset();
        AGGAPI void move_to1(double x, double y);
        AGGAPI void line_to1(double x, double y);
        AGGAPI void move_to2(double x, double y);
        AGGAPI void line_to2(double x, double y);
        AGGAPI void finalize_paths();

        //--------------------------------------------------------------------
        template<class VertexSource1, class VertexSource2> 
        void add_paths(VertexSource1& vs1, VertexSource2& vs2, 
                       unsigned path1_id=0, unsigned path2_id=0)
        {
            double x;
            double y;

            unsigned cmd;

            vs1.rewind(path1_id);
            while(!is_stop(cmd = vs1.vertex(&x, &y)))
            {
                if(is_move_to(cmd)) 
                {
                    move_to1(x, y);
                }
                else 
                {
                    if(is_vertex(cmd))
                    {
                        line_to1(x, y);
                    }
                }
            }

            vs2.rewind(path2_id);
            while(!is_stop(cmd = vs2.vertex(&x, &y)))
            {
                if(is_move_to(cmd)) 
                {
                    move_to2(x, y);
                }
                else 
                {
                    if(is_vertex(cmd))
                    {
                        line_to2(x, y);
                    }
                }
            }
            finalize_paths();
        }

        //--------------------------------------------------------------------
        AGGAPI double total_length1() const;
        AGGAPI double total_length2() const;
        AGGAPI void transform(double *x, double *y) const;

    private:
        double finalize_path(vertex_storage& vertices);
        void transform1(const vertex_storage& vertices, 
                        double kindex, double kx,
                        double *x, double* y) const;

        vertex_storage m_src_vertices1;
        vertex_storage m_src_vertices2;
        double         m_base_length;
        double         m_base_height;
        double         m_kindex1;
        double         m_kindex2;
        status_e       m_status1;
        status_e       m_status2;
        bool           m_preserve_x_scale;
    };
}
#endif
