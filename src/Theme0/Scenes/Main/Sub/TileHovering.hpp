// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class TileHovering
{
  public:
    void Update();

    Point hoveredCoordinate_{-1, -1};
};