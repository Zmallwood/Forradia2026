//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "NUMBER8UTILITIES.HPP"

namespace FORRADIA
{
    int
    INVERT8SPEED(float speed)
    {
        return static_cast<int>(1000 / speed);
    }
}