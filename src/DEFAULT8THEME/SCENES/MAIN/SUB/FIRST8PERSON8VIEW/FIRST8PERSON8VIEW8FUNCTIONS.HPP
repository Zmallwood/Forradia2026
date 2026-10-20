//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "POSITIONED8OBJECT.HPP"

namespace FORRADIA8GAME {
    std::map<std::pair<int, int>, POSITIONED8OBJECT> GET8ORDERED8OBJECTS();

    POINT GET8HOVERED8TILE8POSITION(POINT8F mouseOffset);
}