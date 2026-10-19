// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "TILE.HPP"
#include "TILE_OBJECTS.HPP"

Tile::Tile()
{
    tileObjects_ = std::make_shared<TileObjects>();
}