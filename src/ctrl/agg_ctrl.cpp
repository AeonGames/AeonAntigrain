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
#include "ctrl/agg_ctrl.h"

namespace agg
{
    ctrl::~ctrl() = default;
    ctrl::ctrl(double x1, double y1, double x2, double y2, bool flip_y) :
            m_x1(x1),
            m_y1(y1),
            m_x2(x2),
            m_y2(y2), 
            m_flip_y(flip_y),
            m_mtx(0){}
}
