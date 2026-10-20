//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "RECT8F.HPP"

namespace FORRADIA
{
    bool
    RECT8F::CONTAINS(POINT8F point)
    {
        return point.x >= x && point.x <= x + width && point.y >= y &&
               point.y <= y + height;
    }
}