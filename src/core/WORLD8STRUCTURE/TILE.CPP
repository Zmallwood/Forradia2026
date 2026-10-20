//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "TILE.HPP"
#include "TILE8OBJECTS.HPP"

namespace FORRADIA8GAME
{
    TILE::TILE()
    {
        tileObjects_ = std::make_shared<TILE8OBJECTS>();
    }
}