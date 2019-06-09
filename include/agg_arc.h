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
// Arc vertex generator
//
//----------------------------------------------------------------------------

#ifndef AGG_ARC_INCLUDED
#define AGG_ARC_INCLUDED

#include "agg_basics.h"

namespace agg
{

    //=====================================================================arc
    //
    // See Implementation agg_arc.cpp 
    //
	class arc
	{
	public:
		arc() = default;
		AGGAPI arc(double x, double y,
			double rx, double ry,
			double a1, double a2,
			bool ccw = true);

		AGGAPI void init(double x, double y,
			double rx, double ry,
			double a1, double a2,
			bool ccw = true);

		AGGAPI void approximation_scale(double s);
		[[nodiscard]] double approximation_scale() const { return m_scale; }

		AGGAPI void rewind(unsigned);
		AGGAPI unsigned vertex(double* x, double* y);

	private:
		void normalize(double a1, double a2, bool ccw);

		double   m_x{};
		double   m_y{};
		double   m_rx{};
		double   m_ry{};
		double   m_angle{};
		double   m_start{};
		double   m_end{};
		double   m_scale{ 1.0 };
		double   m_da{};
		bool     m_ccw{};
		bool     m_initialized{false};
		unsigned m_path_cmd{};
    };


}


#endif
