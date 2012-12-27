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
// Conversion from one colorspace/pixel format to another
//
//----------------------------------------------------------------------------

#ifndef AGG_COLOR_CONV_INCLUDED
#define AGG_COLOR_CONV_INCLUDED

#include <string.h>
#include "agg_basics.h"
#include "agg_rendering_buffer.h"




namespace agg
{

    //--------------------------------------------------------------color_conv
    template<class RenBuf, class CopyRow> 
    void color_conv(RenBuf* dst, const RenBuf* src, CopyRow copy_row_functor)
    {
        unsigned width = src->width();
        unsigned height = src->height();

        if(dst->width()  < width)  width  = dst->width();
        if(dst->height() < height) height = dst->height();

        if(width)
        {
            unsigned y;
            for(y = 0; y < height; y++)
            {
                copy_row_functor(dst->row_ptr(0, y, width), 
                                 src->row_ptr(y), 
                                 width);
            }
        }
    }


    //---------------------------------------------------------color_conv_row
    template<class CopyRow> 
    void color_conv_row(int8u* dst, 
                        const int8u* src,
                        unsigned width,
                        CopyRow copy_row_functor)
    {
        copy_row_functor(dst, src, width);
    }


    //---------------------------------------------------------color_conv_same
    template<int BPP> class color_conv_same
    {
    public:
        void operator () (int8u* dst, 
                          const int8u* src,
                          unsigned width) const
        {
            memmove(dst, src, width*BPP);
        }
    };


    // Base class for converters.
    template<class DstFormat, class SrcFormat>
    struct conv_base
    {
        typedef DstFormat dst_format;
        typedef SrcFormat src_format;
        typedef typename dst_format::value_type dst_value;
        typedef typename const src_format::value_type src_value;
    };

    // Generic pixel converter.
    template<class DstFormat, class SrcFormat>
    struct conv_pixel : conv_base<DstFormat, SrcFormat>
    {
        void operator()(dst_value* dst, src_value* src) const
        {
            // Read a pixel from the source format and write it to the destination format.
            dst_format::make_pix(dst, src_format::make_color(src));
        }
    };

    // Generic row converter. Uses conv_pixel to convert individual pixels.
    template<class DstFormat, class SrcFormat>
    struct conv_row : conv_base<DstFormat, SrcFormat>
    {
        void operator()(void* dst, const void* src, unsigned width) const
        {
            dst_value* dval = static_cast<dst_value*>(dst);
            src_value* sval = static_cast<src_value*>(src);
            conv_pixel<DstFormat, SrcFormat> conv;
            do
            {
                conv(dval, sval);
                dval += DstFormat::pix_step;
                sval += SrcFormat::pix_step;
            }
            while (--width);
        }
    };

    // Specialization for case where source and destination formats are identical.
    template<class Format>
    struct conv_row<Format, Format>
    {
        void operator()(void* dst, const void* src, unsigned width) const
        {
            memmove(dst, src, width * Format::pix_width);
        }
    };

    // Top-level conversion function, converts one pixel format to any other.
    template<class DstFormat, class SrcFormat, class RenBuf>
    void convert(RenBuf* dst, const RenBuf* src)
    {
        color_conv(dst, src, conv_row<DstFormat, SrcFormat>());
    }
}



#endif
