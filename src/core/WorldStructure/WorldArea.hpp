/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class Tile;

    class WorldArea
    {
      public:
        WorldArea();

        Size GetSize();

        bool IsValidCoordinate(int x, int y);

        bool IsValidCoordinate(Point coordinate);

        std::shared_ptr<Tile> GetTile(int x, int y);

        std::shared_ptr<Tile> GetTile(Point coordinate);

      private:
        std::vector<std::vector<std::shared_ptr<Tile>>> tiles_;
    };
}