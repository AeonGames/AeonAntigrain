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
// class bspline
//
//----------------------------------------------------------------------------

#ifndef AGG_BSPLINE_INCLUDED
#define AGG_BSPLINE_INCLUDED

#include "agg_array.h"

namespace agg
{
    //----------------------------------------------------------------bspline
    // A very simple class of Bi-cubic Spline interpolation.
    // First call init(num, x[], y[]) where num - number of source points, 
    // x, y - arrays of X and Y values respectively. Here Y must be a function 
    // of X. It means that all the X-coordinates must be arranged in the ascending
    // order. 
    // Then call get(x) that calculates a value Y for the respective X. 
    // The class supports extrapolation, i.e. you can call get(x) where x is
    // outside the given with init() X-range. Extrapolation is a simple linear 
    // function.
    //
    //  See Implementation agg_bspline.cpp
    //------------------------------------------------------------------------
    class bspline 
    {
    public:
        AGGAPI bspline();
        AGGAPI bspline(int num);
        AGGAPI bspline(int num, const double* x, const double* y);

        AGGAPI void   init(int num);
        AGGAPI void   add_point(double x, double y);
        AGGAPI void   prepare();

        AGGAPI void   init(int num, const double* x, const double* y);

        AGGAPI double get(double x) const;
        AGGAPI double get_stateful(double x) const;

        bspline(const bspline&) = delete;
        const bspline& operator = (const bspline&) = delete;

    private:

        AGGAPI static void bsearch(int n, const double *x, double x0, int *i);
        AGGAPI double extrapolation_left(double x) const;
        AGGAPI double extrapolation_right(double x) const;
        AGGAPI double interpolation(double x, int i) const;

        int               m_max{0};
        int               m_num{0};
        double*           m_x{nullptr};
        double*           m_y{nullptr};
        pod_array<double> m_am;
        mutable int       m_last_idx{-1};
    };
}

#endif
