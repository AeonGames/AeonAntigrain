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

#ifndef AGG_WARP_MAGNIFIER_INCLUDED
#define AGG_WARP_MAGNIFIER_INCLUDED

#include "agg_basics.h"

namespace agg
{

    //----------------------------------------------------trans_warp_magnifier
    //
    // See Inmplementation agg_trans_warp_magnifier.cpp
    //
    class trans_warp_magnifier
    {
    public:
        trans_warp_magnifier()  = default;
 
        void center(double x, double y) { m_xc = x; m_yc = y; }
        void magnification(double m)    { m_magn = m;         }
        void radius(double r)           { m_radius = r;       }

        [[nodiscard]] double xc()            const { return m_xc; }
        [[nodiscard]] double yc()            const { return m_yc; }
        [[nodiscard]] double magnification() const { return m_magn;   }
        [[nodiscard]] double radius()        const { return m_radius; }

        AGGAPI void transform(double* x, double* y) const;
        AGGAPI void inverse_transform(double* x, double* y) const;

    private:
        double m_xc{0.0};
        double m_yc{0.0};
        double m_magn{1.0};
        double m_radius{1.0};
    };


}


#endif

