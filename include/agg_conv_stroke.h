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
// conv_stroke
//
//----------------------------------------------------------------------------
#ifndef AGG_CONV_STROKE_INCLUDED
#define AGG_CONV_STROKE_INCLUDED

#include "agg_basics.h"
#include "agg_vcgen_stroke.h"
#include "agg_conv_adaptor_vcgen.h"

namespace agg
{

    //-------------------------------------------------------------conv_stroke
    template<class VertexSource, class Markers=null_markers> 
    struct conv_stroke : 
    public conv_adaptor_vcgen<VertexSource, vcgen_stroke, Markers>
    {
        using marker_type = Markers;
        using base_type = conv_adaptor_vcgen<VertexSource, vcgen_stroke, Markers>;

        conv_stroke(VertexSource& vs) : 
            conv_adaptor_vcgen<VertexSource, vcgen_stroke, Markers>(vs)
        {
        }

        void line_cap(line_cap_e lc)     { base_type::generator().line_cap(lc);  }
        void line_join(line_join_e lj)   { base_type::generator().line_join(lj); }
        void inner_join(inner_join_e ij) { base_type::generator().inner_join(ij); }

        [[nodiscard]] line_cap_e   line_cap()   const { return base_type::generator().line_cap();  }
        [[nodiscard]] line_join_e  line_join()  const { return base_type::generator().line_join(); }
        [[nodiscard]] inner_join_e inner_join() const { return base_type::generator().inner_join(); }

        void width(double w) { base_type::generator().width(w); }
        void miter_limit(double ml) { base_type::generator().miter_limit(ml); }
        void miter_limit_theta(double t) { base_type::generator().miter_limit_theta(t); }
        void inner_miter_limit(double ml) { base_type::generator().inner_miter_limit(ml); }
        void approximation_scale(double as) { base_type::generator().approximation_scale(as); }

        [[nodiscard]] double width() const { return base_type::generator().width(); }
        [[nodiscard]] double miter_limit() const { return base_type::generator().miter_limit(); }
        [[nodiscard]] double inner_miter_limit() const { return base_type::generator().inner_miter_limit(); }
        [[nodiscard]] double approximation_scale() const { return base_type::generator().approximation_scale(); }

        void shorten(double s) { base_type::generator().shorten(s); }
        [[nodiscard]] double shorten() const { return base_type::generator().shorten(); }

       conv_stroke(const conv_stroke<VertexSource, Markers>&) = delete;
       const conv_stroke<VertexSource, Markers>& 
           operator = (const conv_stroke<VertexSource, Markers>&) = delete;

    };

}

#endif
