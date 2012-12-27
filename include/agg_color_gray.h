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
// Adaptation for high precision colors has been sponsored by 
// Liberty Technology Systems, Inc., visit http://lib-sys.com
//
// Liberty Technology Systems, Inc. is the provider of
// PostScript and PDF technology for software developers.
// 
//----------------------------------------------------------------------------
//
// color types gray8, gray16
//
//----------------------------------------------------------------------------

#ifndef AGG_COLOR_GRAY_INCLUDED
#define AGG_COLOR_GRAY_INCLUDED

#include "agg_basics.h"
#include "agg_color_rgba.h"

namespace agg
{

    //===================================================================gray8
    struct gray8
    {
        typedef int8u  value_type;
        typedef int32u calc_type;
        typedef int32  long_type;
        enum base_scale_e
        {
            base_shift = 8,
            base_scale = 1 << base_shift,
            base_mask  = base_scale - 1,
            base_MSB = 1 << (base_shift - 1)
        };
        typedef gray8 self_type;

        value_type v;
        value_type a;

        //--------------------------------------------------------------------
        gray8() {}

        //--------------------------------------------------------------------
        gray8(unsigned v_, unsigned a_=base_mask) :
            v(int8u(v_)), a(int8u(a_)) {}

        //--------------------------------------------------------------------
        gray8(const self_type& c, unsigned a_) :
            v(c.v), a(value_type(a_)) {}

        //--------------------------------------------------------------------
        gray8(const rgba& c) :
            v((value_type)uround((0.299*c.r + 0.587*c.g + 0.114*c.b) * double(base_mask))),
            a((value_type)uround(c.a * double(base_mask))) {}

        //--------------------------------------------------------------------
        gray8(const rgba& c, double a_) :
            v((value_type)uround((0.299*c.r + 0.587*c.g + 0.114*c.b) * double(base_mask))),
            a((value_type)uround(a_ * double(base_mask))) {}

        //--------------------------------------------------------------------
        gray8(const rgba8& c) :
            v((c.r*77 + c.g*150 + c.b*29) >> 8),
            a(c.a) {}

        //--------------------------------------------------------------------
        gray8(const rgba8& c, unsigned a_) :
            v((value_type)((c.r*77 + c.g*150 + c.b*29) >> 8)),
            a((value_type)a_) {}

        //--------------------------------------------------------------------
        operator rgba8()
        {
            return rgba8(v, v, v, a);
        }

        //--------------------------------------------------------------------
        static AGG_INLINE double to_double(value_type a)
        {
            return double(a) / base_mask;
        }

        //--------------------------------------------------------------------
        static AGG_INLINE value_type from_double(double a)
        {
            return value_type(uround(a * base_mask));
        }

        //--------------------------------------------------------------------
        static AGG_INLINE value_type empty_value()
        {
            return 0;
        }

        //--------------------------------------------------------------------
        static AGG_INLINE value_type full_value()
        {
            return base_mask;
        }

        //--------------------------------------------------------------------
        AGG_INLINE bool is_transparent() const
        {
            return a == 0;
        }

        //--------------------------------------------------------------------
        AGG_INLINE bool is_opaque() const
        {
            return a == base_mask;
        }

        //--------------------------------------------------------------------
        // fixed-point multiply, exact over uint8
        static AGG_INLINE value_type multiply(value_type a, value_type b) 
        {
            calc_type t = a * b + base_MSB;
            return value_type(((t >> base_shift) + t) >> base_shift);
        }
        
        //--------------------------------------------------------------------
        static AGG_INLINE value_type demultiply(value_type a, value_type b) 
        {
            return b > 0 ? value_type(a / b) : 0; 
        }

        //--------------------------------------------------------------------
        template<typename T>
        static AGG_INLINE value_type downshift(T a, unsigned n) 
        {
            return value_type(a >> n);
        }

        //--------------------------------------------------------------------
        // fixed-point multiply, exact over uint8
        // specifically for multiplying a color component by a cover
        static AGG_INLINE value_type mult_cover(value_type a, value_type b) 
        {
            return multiply(a, b);
        }
        
        //--------------------------------------------------------------------
        static AGG_INLINE cover_type scale_cover(cover_type a, value_type b) 
        {
            return multiply(b, a);
        }
        
        //--------------------------------------------------------------------
        // linear interpolate q over p by a, assuming q is pre-muliplied by a
        static AGG_INLINE value_type prelerp(value_type p, value_type q, value_type a) 
        {
            return (p == q) ? p : p + q - multiply(p, a);
        }
        
        //--------------------------------------------------------------------
        // linear interpolate q over p by a
        static AGG_INLINE value_type lerp(value_type p, value_type q, value_type a) 
        {
            if (p < q) return p + multiply(q - p, a);
            else if (p > q) return p - multiply(p - q, a);
            else return p;
        }
        
        //--------------------------------------------------------------------
        void clear()
        {
            v = a = 0;
        }

        //--------------------------------------------------------------------
        const self_type& transparent()
        {
            a = 0;
            return *this;
        }

        //--------------------------------------------------------------------
        void opacity(double a_)
        {
            if (a_ < 0) a_ = 0;
            else if (a_ > 1) a_ = 1;
            else a = (value_type)uround(a_ * double(base_mask));
        }

        //--------------------------------------------------------------------
        double opacity() const
        {
            return double(a) / double(base_mask);
        }
        
        //--------------------------------------------------------------------
        const self_type& premultiply()
        {
            if (a < base_mask)
            {
                if (a == 0) v = 0;
                else v = multiply(v, a);
            }
            return *this;
        }

        //--------------------------------------------------------------------
        const self_type& demultiply()
        {
            if (a < base_mask)
            {
                if (a == 0)
                {
                    v = 0;
                }
                else
                {
                    calc_type v_ = (calc_type(v) * base_mask) / a;
                    v = value_type((v_ > base_mask) ? (value_type)base_mask : v_);
                }
            }
            return *this;
        }

        //--------------------------------------------------------------------
        self_type gradient(self_type c, double k) const
        {
            self_type ret;
            calc_type ik = uround(k * base_scale);
            ret.v = lerp(v, c.v, ik);
            ret.a = lerp(a, c.a, ik);
            return ret;
        }

        //--------------------------------------------------------------------
        AGG_INLINE void add(const self_type& c, unsigned cover)
        {
            calc_type cv, ca;
            if (cover == cover_mask)
            {
                if (c.a == base_mask) 
                {
                    *this = c;
                    return;
                }
                else
                {
                    cv = v + c.v; 
                    ca = a + c.a; 
                }
            }
            else
            {
                cv = v + mult_cover(c.v, cover);
                ca = a + mult_cover(c.a, cover);
            }
            v = (value_type)((cv > calc_type(base_mask)) ? calc_type(base_mask) : cv);
            a = (value_type)((ca > calc_type(base_mask)) ? calc_type(base_mask) : ca);
        }

        //--------------------------------------------------------------------
        static self_type no_color() { return self_type(0,0); }
    };


    //-------------------------------------------------------------gray8_pre
    inline gray8 gray8_pre(unsigned v, unsigned a = gray8::base_mask)
    {
        return gray8(v,a).premultiply();
    }
    inline gray8 gray8_pre(const gray8& c, unsigned a)
    {
        return gray8(c,a).premultiply();
    }
    inline gray8 gray8_pre(const rgba& c)
    {
        return gray8(c).premultiply();
    }
    inline gray8 gray8_pre(const rgba& c, double a)
    {
        return gray8(c,a).premultiply();
    }
    inline gray8 gray8_pre(const rgba8& c)
    {
        return gray8(c).premultiply();
    }
    inline gray8 gray8_pre(const rgba8& c, unsigned a)
    {
        return gray8(c,a).premultiply();
    }




    //==================================================================gray16
    struct gray16
    {
        typedef int16u value_type;
        typedef int32u calc_type;
        typedef int64  long_type;
        enum base_scale_e
        {
            base_shift = 16,
            base_scale = 1 << base_shift,
            base_mask  = base_scale - 1,
            base_MSB = 1 << (base_shift - 1)
        };
        typedef gray16 self_type;

        value_type v;
        value_type a;

        //--------------------------------------------------------------------
        gray16() {}

        //--------------------------------------------------------------------
        gray16(unsigned v_, unsigned a_=base_mask) :
            v(int16u(v_)), a(int16u(a_)) {}

        //--------------------------------------------------------------------
        gray16(const self_type& c, unsigned a_) :
            v(c.v), a(value_type(a_)) {}

        //--------------------------------------------------------------------
        gray16(const rgba& c) :
            v((value_type)uround((0.299*c.r + 0.587*c.g + 0.114*c.b) * double(base_mask))),
            a((value_type)uround(c.a * double(base_mask))) {}

        //--------------------------------------------------------------------
        gray16(const rgba& c, double a_) :
            v((value_type)uround((0.299*c.r + 0.587*c.g + 0.114*c.b) * double(base_mask))),
            a((value_type)uround(a_ * double(base_mask))) {}

        //--------------------------------------------------------------------
        gray16(const rgba8& c) :
            v(c.r*77 + c.g*150 + c.b*29),
            a((value_type(c.a) << 8) | c.a) {}

        //--------------------------------------------------------------------
        gray16(const rgba8& c, unsigned a_) :
            v(c.r*77 + c.g*150 + c.b*29),
            a((value_type(a_) << 8) | c.a) {}

        //--------------------------------------------------------------------
        gray16(const rgba16& c) :
        v((c.r*19595 + c.g*38470 + c.b*7471) >> 16),
        a(c.a) {}
        
        //--------------------------------------------------------------------
        gray16(const rgba16& c, unsigned a_) :
        v((value_type)((c.r*19595 + c.g*38470 + c.b*7471) >> 16)),
        a((value_type)a_) {}
        
        //--------------------------------------------------------------------
        gray16(const gray8& c) :
            v((value_type(c.v) << 8) | c.v),
            a((value_type(c.a) << 8) | c.a) {}

        //--------------------------------------------------------------------
        operator rgba8()
        {
            return rgba8(v >> 8, v >> 8, v >> 8, a >> 8);
        }

        //--------------------------------------------------------------------
        operator rgba16()
        {
            return rgba16(v, v, v, a);
        }

        //--------------------------------------------------------------------
        operator gray8()
        {
            return gray8(v >> 8, a >> 8);
        }

        //--------------------------------------------------------------------
        operator gray16()
        {
            return gray16(v, a);
        }

        //--------------------------------------------------------------------
        static AGG_INLINE double to_double(value_type a)
        {
            return double(a) / base_mask;
        }

        //--------------------------------------------------------------------
        static AGG_INLINE value_type from_double(double a)
        {
            return value_type(uround(a * base_mask));
        }

        //--------------------------------------------------------------------
        static AGG_INLINE value_type empty_value()
        {
            return 0;
        }

        //--------------------------------------------------------------------
        static AGG_INLINE value_type full_value()
        {
            return base_mask;
        }

        //--------------------------------------------------------------------
        AGG_INLINE bool is_transparent() const
        {
            return a == 0;
        }

        //--------------------------------------------------------------------
        AGG_INLINE bool is_opaque() const
        {
            return a == base_mask;
        }

        //--------------------------------------------------------------------
        // fixed-point multiply, exact over uint16
        static AGG_INLINE value_type multiply(value_type a, value_type b) 
        {
            calc_type t = a * b + base_MSB;
            return value_type(((t >> base_shift) + t) >> base_shift);
        }
        
        //--------------------------------------------------------------------
        static AGG_INLINE value_type demultiply(value_type a, value_type b) 
        {
            return b > 0 ? value_type(a / b) : 0; 
        }

        //--------------------------------------------------------------------
        template<typename T>
        static AGG_INLINE value_type downshift(T a, unsigned n) 
        {
            return value_type(a >> n);
        }

        //--------------------------------------------------------------------
        // fixed-point multiply, almost exact over uint16
        // specifically for multiplying a color component by a cover
        static AGG_INLINE value_type mult_cover(value_type a, cover_type b) 
        {
            return multiply(a, b << 8 | b);
        }
        
        //--------------------------------------------------------------------
        static AGG_INLINE cover_type scale_cover(cover_type a, value_type b) 
        {
            return mult_cover(b, a) >> 8;
        }
        
        //--------------------------------------------------------------------
        // linear interpolate q over p by a, assuming q is pre-muliplied by a
        static AGG_INLINE value_type int_prelerp(value_type p, value_type q, value_type a) 
        {
            return (p == q) ? p : p + q - multiply(p, a);
        }
        
        //--------------------------------------------------------------------
        // linear interpolate q over p by a
        static AGG_INLINE value_type lerp(value_type p, value_type q, value_type a) 
        {
            if (p < q) return p + multiply(q - p, a);
            else if (p > q) return p - multiply(p - q, a);
            else return p;
        }
        
        //--------------------------------------------------------------------
        void clear()
        {
            v = a = 0;
        }

        //--------------------------------------------------------------------
        const self_type& transparent()
        {
            a = 0;
            return *this;
        }

        //--------------------------------------------------------------------
        void opacity(double a_)
        {
            if (a_ < 0) a_ = 0;
            else if(a_ > 1) a_ = 1;
            else a = (value_type)uround(a_ * double(base_mask));
        }

        //--------------------------------------------------------------------
        double opacity() const
        {
            return double(a) / double(base_mask);
        }


        //--------------------------------------------------------------------
        const self_type& premultiply()
        {
            if (a < base_mask)
            {
                if(a == 0) v = 0;
                else v = multiply(v, a);
            }
            return *this;
        }

        //--------------------------------------------------------------------
        const self_type& demultiply()
        {
            if (a < base_mask)
            {
                if (a == 0)
                {
                    v = 0;
                }
                else
                {
                    calc_type v_ = (calc_type(v) * base_mask) / a;
                    v = value_type((v_ > base_mask) ? base_mask : v_);
                }
            }
            return *this;
        }

        //--------------------------------------------------------------------
        self_type gradient(self_type c, double k) const
        {
            self_type ret;
            calc_type ik = uround(k * base_scale);
            ret.v = lerp(v, c.v, ik);
            ret.a = lerp(a, c.a, ik);
            return ret;
        }

        //--------------------------------------------------------------------
        AGG_INLINE void add(const self_type& c, unsigned cover)
        {
            calc_type cv, ca;
            if (cover == cover_mask)
            {
                if (c.a == base_mask) 
                {
                    *this = c;
                    return;
                }
                else
                {
                    cv = v + c.v; 
                    ca = a + c.a; 
                }
            }
            else
            {
                cv = v + mult_cover(c.v, cover);
                ca = a + mult_cover(c.a, cover);
            }
            v = (value_type)((cv > calc_type(base_mask)) ? calc_type(base_mask) : cv);
            a = (value_type)((ca > calc_type(base_mask)) ? calc_type(base_mask) : ca);
        }

        //--------------------------------------------------------------------
        static self_type no_color() { return self_type(0,0); }
    };


    //------------------------------------------------------------gray16_pre
    inline gray16 gray16_pre(unsigned v, unsigned a = gray16::base_mask)
    {
        return gray16(v,a).premultiply();
    }
    inline gray16 gray16_pre(const gray16& c, unsigned a)
    {
        return gray16(c,a).premultiply();
    }
    inline gray16 gray16_pre(const rgba& c)
    {
        return gray16(c).premultiply();
    }
    inline gray16 gray16_pre(const rgba& c, double a)
    {
        return gray16(c,a).premultiply();
    }
    inline gray16 gray16_pre(const rgba8& c)
    {
        return gray16(c).premultiply();
    }
    inline gray16 gray16_pre(const rgba8& c, unsigned a)
    {
        return gray16(c,a).premultiply();
    }


    //===================================================================gray32
    struct gray32
    {
        typedef float value_type;
        typedef double calc_type;
        typedef double long_type;
        typedef gray32 self_type;

        value_type v;
        value_type a;

        // Calculate greyscale value as per ITU-R BT.709.
        static value_type luminance(double r, double g, double b)
        {
            return value_type(0.2126 * r + 0.7152 * g + 0.0722 * b);
        }

        static value_type luminance(const rgba& c)
        {
            return luminance(c.r, c.g, c.b);
        }

        static value_type luminance(const rgba8& c)
        {
            return luminance(
                sRGB<>::conv_rgb(c.r), 
                sRGB<>::conv_rgb(c.g), 
                sRGB<>::conv_rgb(c.b));
        }

        //--------------------------------------------------------------------
        gray32() {}

        //--------------------------------------------------------------------
        gray32(value_type v_, value_type a_= 1) :
            v(v_), a(a_) {}

        //--------------------------------------------------------------------
        gray32(const self_type& c, value_type a_) :
            v(c.v), a(a_) {}

        //--------------------------------------------------------------------
        gray32(const rgba& c) :
            v(luminance(c)),
            a(value_type(c.a)) {}

        //--------------------------------------------------------------------
        gray32(const rgba& c, double a_) :
            v(luminance(c)),
            a(value_type(a_)) {}

        //--------------------------------------------------------------------
        gray32(const rgba8& c) :
            v(luminance(c)),
            a(value_type(c.a) / rgba8::base_mask) {}

        //--------------------------------------------------------------------
        gray32(const rgba8& c, unsigned a_) :
            v(luminance(c)),
            a(value_type(a_) / rgba8::base_mask) {}

        //--------------------------------------------------------------------
        gray32(const gray8& c) :
            v(sRGB<>::conv_rgb(c.v)), 
            a(sRGB<>::conv_alpha(c.a)) {}

        //--------------------------------------------------------------------
        operator rgba()
        {
            return rgba(v, v, v, a);
        }

        //--------------------------------------------------------------------
        operator gray8()
        {
            // Return non-premultiplied sRGB values.
            return gray8(
                sRGB<>::conv_rgb(v), 
                sRGB<>::conv_alpha(a));
        }

        //--------------------------------------------------------------------
        operator rgba8()
        {
            // Return non-premultiplied sRGB values.
            rgba8::value_type y = sRGB<>::conv_rgb(v);
            return rgba8(y, y, y, sRGB<>::conv_alpha(a));
        }

        //--------------------------------------------------------------------
        static AGG_INLINE double to_double(value_type a)
        {
            return a;
        }

        //--------------------------------------------------------------------
        static AGG_INLINE value_type from_double(double a)
        {
            return value_type(a);
        }

        //--------------------------------------------------------------------
        static AGG_INLINE value_type empty_value()
        {
            return 0;
        }

        //--------------------------------------------------------------------
        static AGG_INLINE value_type full_value()
        {
            return 1;
        }

        //--------------------------------------------------------------------
        AGG_INLINE bool is_transparent() const
        {
            return a <= 0;
        }

        //--------------------------------------------------------------------
        AGG_INLINE bool is_opaque() const
        {
            return a >= 1;
        }

        //--------------------------------------------------------------------
        static AGG_INLINE value_type invert(value_type x) 
        {
            return 1 - x;
        }

        //--------------------------------------------------------------------
        static AGG_INLINE value_type multiply(value_type a, value_type b) 
        {
            return value_type(a * b);
        }

        //--------------------------------------------------------------------
        static AGG_INLINE value_type demultiply(value_type a, value_type b) 
        {
            if (b <= 0) return 0;
            else if (b >= 1) return a;
            else return value_type(a / b);
        }

        //--------------------------------------------------------------------
        template<typename T>
        static AGG_INLINE value_type downshift(T a, unsigned n) 
        {
            return value_type(n > 0 ? a / (1 << n) : a);
        }

        //--------------------------------------------------------------------
        static AGG_INLINE value_type mult_cover(value_type a, cover_type b) 
        {
            return value_type(a * b / cover_mask);
        }

        //--------------------------------------------------------------------
        static AGG_INLINE cover_type scale_cover(cover_type a, value_type b) 
        {
            return cover_type(uround(a * b));
        }
        
        //--------------------------------------------------------------------
        // linear interpolate q over p by a, assuming q is pre-muliplied by a
        static AGG_INLINE value_type prelerp(value_type p, value_type q, value_type a) 
        {
            return p + q - multiply(p, a);
        }
        
        //--------------------------------------------------------------------
        // linear interpolate q over p by a
        static AGG_INLINE value_type lerp(value_type p, value_type q, value_type a) 
        {
            return p + multiply(q - p, a);
        }
        
        //--------------------------------------------------------------------
        void clear()
        {
            v = a = 0;
        }

        //--------------------------------------------------------------------
        const self_type& transparent()
        {
            a = 0;
            return *this;
        }

        //--------------------------------------------------------------------
        void opacity(double a_)
        {
            if (a_ < 0) a = 0;
            else if (a_ > 1) a = 1;
            else a = value_type(a_);
        }

        //--------------------------------------------------------------------
        double opacity() const
        {
            return a;
        }


        //--------------------------------------------------------------------
        const self_type& premultiply()
        {
            if (a < 0) v = 0;
            else if(a < 1) v *= a;
            return *this;
        }

        //--------------------------------------------------------------------
        const self_type& demultiply()
        {
            if (a < 0) v = 0;
            else if (a < 1) v /= a;
            return *this;
        }

        //--------------------------------------------------------------------
        self_type gradient(self_type c, double k) const
        {
            return self_type(
                value_type(v + (c.v - v) * k), 
                value_type(a + (c.a - a) * k));
        }

        //--------------------------------------------------------------------
        static self_type no_color() { return self_type(0,0); }
    };


    //-------------------------------------------------------------gray32_pre
    inline gray32 gray32_pre(float v, float a = 1)
    {
        return gray32(v,a).premultiply();
    }
    inline gray32 gray32_pre(const gray32& c, float a)
    {
        return gray32(c,a).premultiply();
    }
    inline gray32 gray32_pre(const rgba& c)
    {
        return gray32(c).premultiply();
    }
    inline gray32 gray32_pre(const rgba& c, double a)
    {
        return gray32(c,a).premultiply();
    }
    inline gray32 gray32_pre(const rgba8& c)
    {
        return gray32(c).premultiply();
    }
    inline gray32 gray32_pre(const rgba8& c, unsigned a)
    {
        return gray32(c,a).premultiply();
    }

}




#endif
