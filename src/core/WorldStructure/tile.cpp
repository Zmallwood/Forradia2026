/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "tile.hpp"
#include "tile_objects.hpp"

namespace Forradia
{
    tile::tile()
    {
        tile_objects_ = std::make_shared<tile_objects>();
    }
}