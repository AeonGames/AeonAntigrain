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

#ifndef AGG_SPAN_INTERPOLATOR_ADAPTOR_INCLUDED
#define AGG_SPAN_INTERPOLATOR_ADAPTOR_INCLUDED

#include "agg_basics.h"

namespace agg
{

    //===============================================span_interpolator_adaptor
    template<class Interpolator, class Distortion>
    class span_interpolator_adaptor : public Interpolator
    {
    public:
        using base_type = Interpolator;
        using trans_type = typename base_type::trans_type;
        using distortion_type = Distortion;

        //--------------------------------------------------------------------
        span_interpolator_adaptor() {}
        span_interpolator_adaptor(trans_type& trans, 
                                  distortion_type& dist) :
            base_type(trans),
            m_distortion(&dist)
        {   
        }

        //--------------------------------------------------------------------
        span_interpolator_adaptor(trans_type& trans,
                                  distortion_type& dist,
                                  double x, double y, unsigned len) :
            base_type(trans, x, y, len),
            m_distortion(&dist)
        {
        }

        //--------------------------------------------------------------------
        distortion_type& distortion() const
        {
            return *m_distortion;
        }

        //--------------------------------------------------------------------
        void distortion(distortion_type& dist)
        {
            m_distortion = dist;
        }

        //--------------------------------------------------------------------
        void coordinates(int* x, int* y) const
        {
            base_type::coordinates(x, y);
            m_distortion->calculate(x, y);
        }

    private:
        //--------------------------------------------------------------------
        distortion_type* m_distortion;
    };
}


#endif
