/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "Tile.hpp"
#include "TileObjects.hpp"

namespace Forradia
{
    Tile::Tile()
    {
        tile_objects_ = std::make_shared<TileObjects>();
    }
}