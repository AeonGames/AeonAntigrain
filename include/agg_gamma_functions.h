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

#ifndef AGG_GAMMA_FUNCTIONS_INCLUDED
#define AGG_GAMMA_FUNCTIONS_INCLUDED

#include "agg_basics.h"

namespace agg
{
    //===============================================================gamma_none
    struct gamma_none
    {
        double operator()(double x) const { return x; }
    };


    //==============================================================gamma_power
    class gamma_power
    {
    public:
        gamma_power()  = default;
        gamma_power(double g) : m_gamma(g) {}

        void gamma(double g) { m_gamma = g; }
        [[nodiscard]] double gamma() const { return m_gamma; }

        double operator() (double x) const
        {
            return pow(x, m_gamma);
        }

    private:
        double m_gamma{1.0};
    };


    //==========================================================gamma_threshold
    class gamma_threshold
    {
    public:
        gamma_threshold()  = default;
        gamma_threshold(double t) : m_threshold(t) {}

        void threshold(double t) { m_threshold = t; }
        [[nodiscard]] double threshold() const { return m_threshold; }

        double operator() (double x) const
        {
            return (x < m_threshold) ? 0.0 : 1.0;
        }

    private:
        double m_threshold{0.5};
    };


    //============================================================gamma_linear
    class gamma_linear
    {
    public:
        gamma_linear()  = default;
        gamma_linear(double s, double e) : m_start(s), m_end(e) {}

        void set(double s, double e) { m_start = s; m_end = e; }
        void start(double s) { m_start = s; }
        void end(double e) { m_end = e; }
        [[nodiscard]] double start() const { return m_start; }
        [[nodiscard]] double end() const { return m_end; }

        double operator() (double x) const
        {
            if(x < m_start) return 0.0;
            if(x > m_end) return 1.0;
            return (x - m_start) / (m_end - m_start);
        }

    private:
        double m_start{0.0};
        double m_end{1.0};
    };


    //==========================================================gamma_multiply
    class gamma_multiply
    {
    public:
        gamma_multiply()  = default;
        gamma_multiply(double v) : m_mul(v) {}

        void value(double v) { m_mul = v; }
        [[nodiscard]] double value() const { return m_mul; }

        double operator() (double x) const
        {
            double y = x * m_mul;
            if(y > 1.0) y = 1.0;
            return y;
        }

    private:
        double m_mul{1.0};
    };

    inline double sRGB_to_linear(double x)
    {
        return (x <= 0.04045) ? (x / 12.92) : pow((x + 0.055) / (1.055), 2.4);
    }

    inline double linear_to_sRGB(double x)
    {
        return (x <= 0.0031308) ? (x * 12.92) : (1.055 * pow(x, 1 / 2.4) - 0.055);
    }
}

#endif



