//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME {
    enum class ROAD8ORIENTATION {
        None,
        Horizontal,
        Vertical,
        CornerNorthEast,
        CornerSouthEast,
        CornerSouthWest,
        CornerNorthWest,
        TIntersectionNorth,
        TIntersectionSouth,
        TIntersectionEast,
        TIntersectionWest,
        CrossIntersection,
        Fill
    };
}