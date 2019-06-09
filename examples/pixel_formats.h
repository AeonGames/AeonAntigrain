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
#ifndef PIXEL_FORMATS_INCLUDED
#define PIXEL_FORMATS_INCLUDED

#if defined(AGG_GRAY8)

#include "agg_pixfmt_gray.h"
const agg::pix_format_e pix_format = agg::pix_format_gray8;
using pixfmt = agg::pixfmt_gray8;
using pixfmt_pre = agg::pixfmt_gray8_pre;
using color_type = agg::gray8;
using gray_type = agg::gray8;

#elif defined(AGG_SGRAY8)

#include "agg_pixfmt_gray.h"
const agg::pix_format_e pix_format = agg::pix_format_sgray8;
using pixfmt = agg::pixfmt_sgray8;
using pixfmt_pre = agg::pixfmt_sgray8_pre;
using color_type = agg::sgray8;
using gray_type = agg::sgray8;

#elif defined(AGG_GRAY16)

#include "agg_pixfmt_gray.h"
const agg::pix_format_e pix_format = agg::pix_format_gray16;
using pixfmt = agg::pixfmt_gray16;
using pixfmt_pre = agg::pixfmt_gray16_pre;
using color_type = agg::gray16;
using gray_type = agg::gray16;

#elif defined(AGG_GRAY32)

#include "agg_pixfmt_gray.h"
const agg::pix_format_e pix_format = agg::pix_format_gray32;
using pixfmt = agg::pixfmt_gray32;
using pixfmt_pre = agg::pixfmt_gray32_pre;
using color_type = agg::gray32;
using gray_type = agg::gray32;

#elif defined(AGG_BGR24)

#include "agg_pixfmt_rgb.h"
const agg::pix_format_e pix_format = agg::pix_format_bgr24;
using pixfmt = agg::pixfmt_bgr24;
using pixfmt_pre = agg::pixfmt_bgr24_pre;
#define pixfmt_gamma agg::pixfmt_bgr24_gamma
using color_type = agg::rgba8;
using component_order = agg::order_bgr;
using gray_type = agg::gray8;

#elif defined(AGG_RGB24)

#include "agg_pixfmt_rgb.h"
const agg::pix_format_e pix_format = agg::pix_format_rgb24;
using pixfmt = agg::pixfmt_rgb24;
using pixfmt_pre = agg::pixfmt_rgb24_pre;
#define pixfmt_gamma agg::pixfmt_rgb24_gamma
using color_type = agg::rgba8;
using component_order = agg::order_rgb;
using gray_type = agg::gray8;

#elif defined(AGG_SBGR24)

#include "agg_pixfmt_rgb.h"
const agg::pix_format_e pix_format = agg::pix_format_sbgr24;
using pixfmt = agg::pixfmt_sbgr24;
using pixfmt_pre = agg::pixfmt_sbgr24_pre;
#define pixfmt_gamma agg::pixfmt_sbgr24_gamma
using color_type = agg::srgba8;
using component_order = agg::order_bgr;
using gray_type = agg::sgray8;

#elif defined(AGG_SRGB24)

#include "agg_pixfmt_rgb.h"
const agg::pix_format_e pix_format = agg::pix_format_srgb24;
using pixfmt = agg::pixfmt_srgb24;
using pixfmt_pre = agg::pixfmt_srgb24_pre;
#define pixfmt_gamma agg::pixfmt_srgb24_gamma
using color_type = agg::srgba8;
using component_order = agg::order_rgb;
using gray_type = agg::sgray8;

#elif defined(AGG_BGR48)

#include "agg_pixfmt_rgb.h"
const agg::pix_format_e pix_format = agg::pix_format_bgr48;
using pixfmt = agg::pixfmt_bgr48;
using pixfmt_pre = agg::pixfmt_bgr48_pre;
#define pixfmt_gamma agg::pixfmt_bgr48_gamma
using color_type = agg::rgba16;
using component_order = agg::order_bgr;
using gray_type = agg::gray16;

#elif defined(AGG_RGB48)

#include "agg_pixfmt_rgb.h"
const agg::pix_format_e pix_format = agg::pix_format_rgb48;
using pixfmt = agg::pixfmt_rgb48;
using pixfmt_pre = agg::pixfmt_rgb48_pre;
#define pixfmt_gamma agg::pixfmt_rgb48_gamma
using color_type = agg::rgba16;
using component_order = agg::order_rgb;
using gray_type = agg::gray16;

#elif defined(AGG_BGR96)

#include "agg_pixfmt_rgb.h"
const agg::pix_format_e pix_format = agg::pix_format_bgr96;
using pixfmt = agg::pixfmt_bgr96;
using pixfmt_pre = agg::pixfmt_bgr96_pre;
using color_type = agg::rgba32;
using component_order = agg::order_bgr;
using gray_type = agg::gray32;

#elif defined(AGG_RGB96)

#include "agg_pixfmt_rgb.h"
const agg::pix_format_e pix_format = agg::pix_format_rgb96;
using pixfmt = agg::pixfmt_rgb96;
using pixfmt_pre = agg::pixfmt_rgb96_pre;
using color_type = agg::rgba32;
using component_order = agg::order_bgr;
using gray_type = agg::gray32;

#elif defined(AGG_BGRA32)

#include "agg_pixfmt_rgba.h"
const agg::pix_format_e pix_format = agg::pix_format_bgra32;
using pixfmt = agg::pixfmt_bgra32;
using pixfmt_pre = agg::pixfmt_bgra32_pre;
using color_type = agg::rgba8;
using component_order = agg::order_bgra;
using gray_type = agg::gray8;

#elif defined(AGG_RGBA32)

#include "agg_pixfmt_rgba.h"
const agg::pix_format_e pix_format = agg::pix_format_rgba32;
using pixfmt = agg::pixfmt_rgba32;
using pixfmt_pre = agg::pixfmt_rgba32_pre;
using color_type = agg::rgba8;
using component_order = agg::order_rgba;
using gray_type = agg::gray8;

#elif defined(AGG_ARGB32)

#include "agg_pixfmt_rgba.h"
const agg::pix_format_e pix_format = agg::pix_format_argb32;
using pixfmt = agg::pixfmt_argb32;
using pixfmt_pre = agg::pixfmt_argb32_pre;
using color_type = agg::rgba8;
using component_order = agg::order_argb;
using gray_type = agg::gray8;

#elif defined(AGG_ABGR32)

#include "agg_pixfmt_rgba.h"
const agg::pix_format_e pix_format = agg::pix_format_abgr32;
using pixfmt = agg::pixfmt_abgr32;
using pixfmt_pre = agg::pixfmt_abgr32_pre;
using color_type = agg::rgba8;
using component_order = agg::order_argb;
using gray_type = agg::gray8;

#elif defined(AGG_SBGRA32)

#include "agg_pixfmt_rgba.h"
const agg::pix_format_e pix_format = agg::pix_format_sbgra32;
using pixfmt = agg::pixfmt_sbgra32;
using pixfmt_pre = agg::pixfmt_sbgra32_pre;
using color_type = agg::srgba8;
using component_order = agg::order_bgra;
using gray_type = agg::sgray8;

#elif defined(AGG_SRGBA32)

#include "agg_pixfmt_rgba.h"
const agg::pix_format_e pix_format = agg::pix_format_srgba32;
using pixfmt = agg::pixfmt_srgba32;
using pixfmt_pre = agg::pixfmt_srgba32_pre;
using color_type = agg::srgba8;
using component_order = agg::order_rgba;
using gray_type = agg::sgray8;

#elif defined(AGG_SARGB32)

#include "agg_pixfmt_rgba.h"
const agg::pix_format_e pix_format = agg::pix_format_sargb32;
using pixfmt = agg::pixfmt_sargb32;
using pixfmt_pre = agg::pixfmt_sargb32_pre;
using color_type = agg::srgba8;
using component_order = agg::order_argb;
using gray_type = agg::sgray8;

#elif defined(AGG_SABGR32)

#include "agg_pixfmt_rgba.h"
const agg::pix_format_e pix_format = agg::pix_format_sabgr32;
using pixfmt = agg::pixfmt_sabgr32;
using pixfmt_pre = agg::pixfmt_sabgr32_pre;
using color_type = agg::srgba8;
using component_order = agg::order_argb;
using gray_type = agg::sgray8;

#elif defined(AGG_BGRA64)

#include "agg_pixfmt_rgba.h"
const agg::pix_format_e pix_format = agg::pix_format_bgra64;
using pixfmt = agg::pixfmt_bgra64;
using pixfmt_pre = agg::pixfmt_bgra64_pre;
using color_type = agg::rgba16;
using component_order = agg::order_bgra;
using gray_type = agg::gray16;

#elif defined(AGG_RGBA64)

#include "agg_pixfmt_rgba.h"
const agg::pix_format_e pix_format = agg::pix_format_rgba64;
using pixfmt = agg::pixfmt_rgba64;
using pixfmt_pre = agg::pixfmt_rgba64_pre;
using color_type = agg::rgba16;
using component_order = agg::order_rgba;
using gray_type = agg::gray16;

#elif defined(AGG_ARGB64)

#include "agg_pixfmt_rgba.h"
const agg::pix_format_e pix_format = agg::pix_format_argb64;
using pixfmt = agg::pixfmt_argb64;
using pixfmt_pre = agg::pixfmt_argb64_pre;
using color_type = agg::rgba16;
using component_order = agg::order_argb;
using gray_type = agg::gray16;

#elif defined(AGG_ABGR64)

#include "agg_pixfmt_rgba.h"
const agg::pix_format_e pix_format = agg::pix_format_abgr64;
using pixfmt = agg::pixfmt_abgr64;
using pixfmt_pre = agg::pixfmt_abgr64_pre;
using color_type = agg::rgba16;
using component_order = agg::order_argb;
using gray_type = agg::gray16;

#elif defined(AGG_BGRA128)

#include "agg_pixfmt_rgba.h"
const agg::pix_format_e pix_format = agg::pix_format_bgra128;
using pixfmt = agg::pixfmt_bgra128;
using pixfmt_pre = agg::pixfmt_bgra128_pre;
using color_type = agg::rgba32;
using component_order = agg::order_bgra;
using gray_type = agg::gray32;

#elif defined(AGG_RGBA128)

#include "agg_pixfmt_rgba.h"
const agg::pix_format_e pix_format = agg::pix_format_rgba128;
using pixfmt = agg::pixfmt_rgba128;
using pixfmt_pre = agg::pixfmt_rgba128_pre;
using color_type = agg::rgba32;
using component_order = agg::order_rgba;
using gray_type = agg::gray32;

#elif defined(AGG_ARGB128)

#include "agg_pixfmt_rgba.h"
const agg::pix_format_e pix_format = agg::pix_format_argb128;
using pixfmt = agg::pixfmt_argb128;
using pixfmt_pre = agg::pixfmt_argb128_pre;
using color_type = agg::rgba32;
using component_order = agg::order_argb;
using gray_type = agg::gray32;

#elif defined(AGG_ABGR128)

#include "agg_pixfmt_rgba.h"
const agg::pix_format_e pix_format = agg::pix_format_abgr128;
using pixfmt = agg::pixfmt_abgr128;
using pixfmt_pre = agg::pixfmt_abgr128_pre;
using color_type = agg::rgba32;
using component_order = agg::order_argb;
using gray_type = agg::gray32;

#elif defined(AGG_RGB565)

#include "agg_pixfmt_rgb_packed.h"
const agg::pix_format_e pix_format = agg::pix_format_rgb565;
using pixfmt = agg::pixfmt_rgb565;
using pixfmt_pre = agg::pixfmt_rgb565_pre;
using color_type = agg::rgba8;
using gray_type = agg::gray8;

#elif defined(AGG_RGB555)

#include "agg_pixfmt_rgb_packed.h"
const agg::pix_format_e pix_format = agg::pix_format_rgb555;
using pixfmt = agg::pixfmt_rgb555;
using pixfmt_pre = agg::pixfmt_rgb555_pre;
using color_type = agg::rgba8;
using gray_type = agg::gray8;

#elif defined(AGG_RGB_AAA)

#include "agg_pixfmt_rgb_packed.h"
const agg::pix_format_e pix_format = agg::pix_format_rgbAAA;
using pixfmt = agg::pixfmt_rgbAAA;
using pixfmt_pre = agg::pixfmt_rgbAAA_pre;
using color_type = agg::rgba16;
using gray_type = agg::gray16;

#elif defined(AGG_BGR_AAA)

#include "agg_pixfmt_rgb_packed.h"
const agg::pix_format_e pix_format = agg::pix_format_bgrAAA;
using pixfmt = agg::pixfmt_bgrAAA;
using pixfmt_pre = agg::pixfmt_bgrAAA_pre;
using color_type = agg::rgba16;
using gray_type = agg::gray16;

#elif defined(AGG_RGB_BBA)

#include "agg_pixfmt_rgb_packed.h"
const agg::pix_format_e pix_format = agg::pix_format_rgbBBA;
using pixfmt = agg::pixfmt_rgbBBA;
using pixfmt_pre = agg::pixfmt_rgbBBA_pre;
using color_type = agg::rgba16;
using gray_type = agg::gray16;

#elif defined(AGG_BGR_ABB)

#include "agg_pixfmt_rgb_packed.h"
const agg::pix_format_e pix_format = agg::pix_format_bgrABB;
using pixfmt = agg::pixfmt_bgrABB;
using pixfmt_pre = agg::pixfmt_bgrABB_pre;
using color_type = agg::rgba16;
using gray_type = agg::gray16;

#else
#error Please define pixel format: AGG_GRAY8, AGG_BGR24, AGG_RGB24, etc. See this file above
#endif

#endif
