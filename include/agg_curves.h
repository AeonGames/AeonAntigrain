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
// Copyright (C) 2005 Tony Juricic (tonygeek@yahoo.com)
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

#ifndef AGG_CURVES_INCLUDED
#define AGG_CURVES_INCLUDED

#include "agg_array.h"

namespace agg
{
    // See Implementation agg_curves.cpp
    //--------------------------------------------curve_approximation_method_e
    enum curve_approximation_method_e
    {
        curve_inc,
        curve_div
    };
    
    //--------------------------------------------------------------curve3_inc
    class curve3_inc
    {
    public:
        curve3_inc()  = default;

        curve3_inc(double x1, double y1, 
                   double x2, double y2, 
                   double x3, double y3)  
        { 
            init(x1, y1, x2, y2, x3, y3);
        }

        void reset() { m_num_steps = 0; m_step = -1; }
        AGGAPI void init(double x1, double y1, 
                  double x2, double y2, 
                  double x3, double y3);

        void approximation_method(curve_approximation_method_e) {}
        [[nodiscard]] curve_approximation_method_e approximation_method() const { return curve_inc; }

        AGGAPI void approximation_scale(double s);
        [[nodiscard]] AGGAPI double approximation_scale() const;

        void angle_tolerance(double) {}
        [[nodiscard]] double angle_tolerance() const { return 0.0; }

        void cusp_limit(double) {}
        [[nodiscard]] double cusp_limit() const { return 0.0; }

        AGGAPI void     rewind(unsigned path_id);
        AGGAPI unsigned vertex(double* x, double* y);

    private:
        int      m_num_steps{0};
        int      m_step{0};
        double   m_scale{1.0};
        double   m_start_x; 
        double   m_start_y;
        double   m_end_x; 
        double   m_end_y;
        double   m_fx; 
        double   m_fy;
        double   m_dfx; 
        double   m_dfy;
        double   m_ddfx; 
        double   m_ddfy;
        double   m_saved_fx; 
        double   m_saved_fy;
        double   m_saved_dfx; 
        double   m_saved_dfy;
    };

    //-------------------------------------------------------------curve3_div
    class curve3_div
    {
    public:
        curve3_div() 
            
        = default;

        curve3_div(double x1, double y1, 
                   double x2, double y2, 
                   double x3, double y3) :
            
            m_count(0)
        { 
            init(x1, y1, x2, y2, x3, y3);
        }

        void reset() { m_points.remove_all(); m_count = 0; }
        AGGAPI void init(double x1, double y1, 
                  double x2, double y2, 
                  double x3, double y3);

        void approximation_method(curve_approximation_method_e) {}
        [[nodiscard]] curve_approximation_method_e approximation_method() const { return curve_div; }

        void approximation_scale(double s) { m_approximation_scale = s; }
        [[nodiscard]] double approximation_scale() const { return m_approximation_scale;  }

        void angle_tolerance(double a) { m_angle_tolerance = a; }
        [[nodiscard]] double angle_tolerance() const { return m_angle_tolerance;  }

        void cusp_limit(double) {}
        [[nodiscard]] double cusp_limit() const { return 0.0; }

        void rewind(unsigned)
        {
            m_count = 0;
        }

        unsigned vertex(double* x, double* y)
        {
            if(m_count >= m_points.size()) return path_cmd_stop;
            const point_d& p = m_points[m_count++];
            *x = p.x;
            *y = p.y;
            return (m_count == 1) ? path_cmd_move_to : path_cmd_line_to;
        }

    private:
        AGGAPI void bezier(double x1, double y1,
                    double x2, double y2, 
                    double x3, double y3);
        AGGAPI void recursive_bezier(double x1, double y1, 
                              double x2, double y2, 
                              double x3, double y3,
                              unsigned level);

        double               m_approximation_scale{1.0};
        double               m_distance_tolerance_square;
        double               m_angle_tolerance{0.0};
        unsigned             m_count{0};
        pod_bvector<point_d> m_points;
    };







    //-------------------------------------------------------------curve4_points
    struct curve4_points
    {
        std::array<double, 8> cp;
        curve4_points() = default;
        curve4_points(double x1, double y1,
                      double x2, double y2,
                      double x3, double y3,
                      double x4, double y4)
        {
            cp[0] = x1; cp[1] = y1; cp[2] = x2; cp[3] = y2;
            cp[4] = x3; cp[5] = y3; cp[6] = x4; cp[7] = y4;
        }
        void init(double x1, double y1,
                  double x2, double y2,
                  double x3, double y3,
                  double x4, double y4)
        {
            cp[0] = x1; cp[1] = y1; cp[2] = x2; cp[3] = y2;
            cp[4] = x3; cp[5] = y3; cp[6] = x4; cp[7] = y4;
        }
        double  operator [] (unsigned i) const { return cp[i]; }
        double& operator [] (unsigned i)       { return cp[i]; }
    };



    //-------------------------------------------------------------curve4_inc
    class curve4_inc
    {
    public:
        curve4_inc()  = default;

        curve4_inc(double x1, double y1, 
                   double x2, double y2, 
                   double x3, double y3,
                   double x4, double y4)  
        { 
            init(x1, y1, x2, y2, x3, y3, x4, y4);
        }

        curve4_inc(const curve4_points& cp)  
        { 
            init(cp[0], cp[1], cp[2], cp[3], cp[4], cp[5], cp[6], cp[7]);
        }

        void reset() { m_num_steps = 0; m_step = -1; }
        AGGAPI void init(double x1, double y1, 
                  double x2, double y2, 
                  double x3, double y3,
                  double x4, double y4);

        void init(const curve4_points& cp)
        {
            init(cp[0], cp[1], cp[2], cp[3], cp[4], cp[5], cp[6], cp[7]);
        }

        void approximation_method(curve_approximation_method_e) {}
        [[nodiscard]] curve_approximation_method_e approximation_method() const { return curve_inc; }

        AGGAPI void approximation_scale(double s);
        [[nodiscard]] AGGAPI double approximation_scale() const;

        void angle_tolerance(double) {}
        [[nodiscard]] double angle_tolerance() const { return 0.0; }

        void cusp_limit(double) {}
        [[nodiscard]] double cusp_limit() const { return 0.0; }

        AGGAPI void     rewind(unsigned path_id);
        AGGAPI unsigned vertex(double* x, double* y);

    private:
        int      m_num_steps{0};
        int      m_step{0};
        double   m_scale{1.0};
        double   m_start_x; 
        double   m_start_y;
        double   m_end_x; 
        double   m_end_y;
        double   m_fx; 
        double   m_fy;
        double   m_dfx; 
        double   m_dfy;
        double   m_ddfx; 
        double   m_ddfy;
        double   m_dddfx; 
        double   m_dddfy;
        double   m_saved_fx; 
        double   m_saved_fy;
        double   m_saved_dfx; 
        double   m_saved_dfy;
        double   m_saved_ddfx; 
        double   m_saved_ddfy;
    };



    //-------------------------------------------------------catrom_to_bezier
    inline curve4_points catrom_to_bezier(double x1, double y1, 
                                          double x2, double y2, 
                                          double x3, double y3,
                                          double x4, double y4)
    {
        // Trans. matrix Catmull-Rom to Bezier
        //
        //  0       1       0       0
        //  -1/6    1       1/6     0
        //  0       1/6     1       -1/6
        //  0       0       1       0
        //
        return curve4_points(
            x2,
            y2,
            (-x1 + 6*x2 + x3) / 6,
            (-y1 + 6*y2 + y3) / 6,
            ( x2 + 6*x3 - x4) / 6,
            ( y2 + 6*y3 - y4) / 6,
            x3,
            y3);
    }


    //-----------------------------------------------------------------------
    inline curve4_points
    catrom_to_bezier(const curve4_points& cp)
    {
        return catrom_to_bezier(cp[0], cp[1], cp[2], cp[3], 
                                cp[4], cp[5], cp[6], cp[7]);
    }



    //-----------------------------------------------------ubspline_to_bezier
    inline curve4_points ubspline_to_bezier(double x1, double y1, 
                                            double x2, double y2, 
                                            double x3, double y3,
                                            double x4, double y4)
    {
        // Trans. matrix Uniform BSpline to Bezier
        //
        //  1/6     4/6     1/6     0
        //  0       4/6     2/6     0
        //  0       2/6     4/6     0
        //  0       1/6     4/6     1/6
        //
        return curve4_points(
            (x1 + 4*x2 + x3) / 6,
            (y1 + 4*y2 + y3) / 6,
            (4*x2 + 2*x3) / 6,
            (4*y2 + 2*y3) / 6,
            (2*x2 + 4*x3) / 6,
            (2*y2 + 4*y3) / 6,
            (x2 + 4*x3 + x4) / 6,
            (y2 + 4*y3 + y4) / 6);
    }


    //-----------------------------------------------------------------------
    inline curve4_points 
    ubspline_to_bezier(const curve4_points& cp)
    {
        return ubspline_to_bezier(cp[0], cp[1], cp[2], cp[3], 
                                  cp[4], cp[5], cp[6], cp[7]);
    }




    //------------------------------------------------------hermite_to_bezier
    inline curve4_points hermite_to_bezier(double x1, double y1, 
                                           double x2, double y2, 
                                           double x3, double y3,
                                           double x4, double y4)
    {
        // Trans. matrix Hermite to Bezier
        //
        //  1       0       0       0
        //  1       0       1/3     0
        //  0       1       0       -1/3
        //  0       1       0       0
        //
        return curve4_points(
            x1,
            y1,
            (3*x1 + x3) / 3,
            (3*y1 + y3) / 3,
            (3*x2 - x4) / 3,
            (3*y2 - y4) / 3,
            x2,
            y2);
    }



    //-----------------------------------------------------------------------
    inline curve4_points 
    hermite_to_bezier(const curve4_points& cp)
    {
        return hermite_to_bezier(cp[0], cp[1], cp[2], cp[3], 
                                 cp[4], cp[5], cp[6], cp[7]);
    }


    //-------------------------------------------------------------curve4_div
    class curve4_div
    {
    public:
        curve4_div() 
            
        = default;

        curve4_div(double x1, double y1, 
                   double x2, double y2, 
                   double x3, double y3,
                   double x4, double y4) :
            
            m_count(0)
        { 
            init(x1, y1, x2, y2, x3, y3, x4, y4);
        }

        curve4_div(const curve4_points& cp) :
            
            m_count(0)
        { 
            init(cp[0], cp[1], cp[2], cp[3], cp[4], cp[5], cp[6], cp[7]);
        }

        void reset() { m_points.remove_all(); m_count = 0; }
        AGGAPI void init(double x1, double y1, 
                  double x2, double y2, 
                  double x3, double y3,
                  double x4, double y4);

        void init(const curve4_points& cp)
        {
            init(cp[0], cp[1], cp[2], cp[3], cp[4], cp[5], cp[6], cp[7]);
        }

        void approximation_method(curve_approximation_method_e) {}

        [[nodiscard]] curve_approximation_method_e approximation_method() const 
        { 
            return curve_div; 
        }

        void approximation_scale(double s) { m_approximation_scale = s; }
        [[nodiscard]] double approximation_scale() const { return m_approximation_scale;  }

        void angle_tolerance(double a) { m_angle_tolerance = a; }
        [[nodiscard]] double angle_tolerance() const { return m_angle_tolerance;  }

        void cusp_limit(double v) 
        { 
            m_cusp_limit = (v == 0.0) ? 0.0 : pi - v; 
        }

        [[nodiscard]] double cusp_limit() const 
        { 
            return (m_cusp_limit == 0.0) ? 0.0 : pi - m_cusp_limit; 
        }

        void rewind(unsigned)
        {
            m_count = 0;
        }

        unsigned vertex(double* x, double* y)
        {
            if(m_count >= m_points.size()) return path_cmd_stop;
            const point_d& p = m_points[m_count++];
            *x = p.x;
            *y = p.y;
            return (m_count == 1) ? path_cmd_move_to : path_cmd_line_to;
        }

    private:
        AGGAPI void bezier(double x1, double y1, 
                    double x2, double y2, 
                    double x3, double y3, 
                    double x4, double y4);

        AGGAPI void recursive_bezier(double x1, double y1, 
                              double x2, double y2, 
                              double x3, double y3, 
                              double x4, double y4,
                              unsigned level);

        double               m_approximation_scale{1.0};
        double               m_distance_tolerance_square;
        double               m_angle_tolerance{0.0};
        double               m_cusp_limit{0.0};
        unsigned             m_count{0};
        pod_bvector<point_d> m_points;
    };


    //-----------------------------------------------------------------curve3
    class curve3
    {
    public:
        curve3()  = default;
        curve3(double x1, double y1, 
               double x2, double y2, 
               double x3, double y3) 
            
        { 
            init(x1, y1, x2, y2, x3, y3);
        }

        void reset() 
        { 
            m_curve_inc.reset();
            m_curve_div.reset();
        }

        void init(double x1, double y1, 
                  double x2, double y2, 
                  double x3, double y3)
        {
            if(m_approximation_method == curve_inc) 
            {
                m_curve_inc.init(x1, y1, x2, y2, x3, y3);
            }
            else
            {
                m_curve_div.init(x1, y1, x2, y2, x3, y3);
            }
        }

        void approximation_method(curve_approximation_method_e v) 
        { 
            m_approximation_method = v; 
        }

        [[nodiscard]] curve_approximation_method_e approximation_method() const 
        { 
            return m_approximation_method; 
        }

        void approximation_scale(double s) 
        { 
            m_curve_inc.approximation_scale(s);
            m_curve_div.approximation_scale(s);
        }

        [[nodiscard]] double approximation_scale() const 
        { 
            return m_curve_inc.approximation_scale(); 
        }

        void angle_tolerance(double a) 
        { 
            m_curve_div.angle_tolerance(a); 
        }

        [[nodiscard]] double angle_tolerance() const 
        { 
            return m_curve_div.angle_tolerance(); 
        }

        void cusp_limit(double v) 
        { 
            m_curve_div.cusp_limit(v); 
        }

        [[nodiscard]] double cusp_limit() const 
        { 
            return m_curve_div.cusp_limit();  
        }

        void rewind(unsigned path_id)
        {
            if(m_approximation_method == curve_inc) 
            {
                m_curve_inc.rewind(path_id);
            }
            else
            {
                m_curve_div.rewind(path_id);
            }
        }

        unsigned vertex(double* x, double* y)
        {
            if(m_approximation_method == curve_inc) 
            {
                return m_curve_inc.vertex(x, y);
            }
            return m_curve_div.vertex(x, y);
        }

    private:
        curve3_inc m_curve_inc;
        curve3_div m_curve_div;
        curve_approximation_method_e m_approximation_method{curve_div};
    };





    //-----------------------------------------------------------------curve4
    class curve4
    {
    public:
        curve4()  = default;
        curve4(double x1, double y1, 
               double x2, double y2, 
               double x3, double y3,
               double x4, double y4)  
            
        { 
            init(x1, y1, x2, y2, x3, y3, x4, y4);
        }

        curve4(const curve4_points& cp) 
            
        { 
            init(cp[0], cp[1], cp[2], cp[3], cp[4], cp[5], cp[6], cp[7]);
        }

        void reset() 
        { 
            m_curve_inc.reset();
            m_curve_div.reset();
        }

        void init(double x1, double y1, 
                  double x2, double y2, 
                  double x3, double y3,
                  double x4, double y4)
        {
            if(m_approximation_method == curve_inc) 
            {
                m_curve_inc.init(x1, y1, x2, y2, x3, y3, x4, y4);
            }
            else
            {
                m_curve_div.init(x1, y1, x2, y2, x3, y3, x4, y4);
            }
        }

        void init(const curve4_points& cp)
        {
            init(cp[0], cp[1], cp[2], cp[3], cp[4], cp[5], cp[6], cp[7]);
        }

        void approximation_method(curve_approximation_method_e v) 
        { 
            m_approximation_method = v; 
        }

        [[nodiscard]] curve_approximation_method_e approximation_method() const 
        { 
            return m_approximation_method; 
        }

        void approximation_scale(double s) 
        { 
            m_curve_inc.approximation_scale(s);
            m_curve_div.approximation_scale(s);
        }
        [[nodiscard]] double approximation_scale() const { return m_curve_inc.approximation_scale(); }

        void angle_tolerance(double v) 
        { 
            m_curve_div.angle_tolerance(v); 
        }

        [[nodiscard]] double angle_tolerance() const 
        { 
            return m_curve_div.angle_tolerance();  
        }

        void cusp_limit(double v) 
        { 
            m_curve_div.cusp_limit(v); 
        }

        [[nodiscard]] double cusp_limit() const 
        { 
            return m_curve_div.cusp_limit();  
        }

        void rewind(unsigned path_id)
        {
            if(m_approximation_method == curve_inc) 
            {
                m_curve_inc.rewind(path_id);
            }
            else
            {
                m_curve_div.rewind(path_id);
            }
        }

        unsigned vertex(double* x, double* y)
        {
            if(m_approximation_method == curve_inc) 
            {
                return m_curve_inc.vertex(x, y);
            }
            return m_curve_div.vertex(x, y);
        }

    private:
        curve4_inc m_curve_inc;
        curve4_div m_curve_div;
        curve_approximation_method_e m_approximation_method{curve_div};
    };
}
#endif
