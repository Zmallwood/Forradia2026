// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class Tile;
class CREATURE;

class WorldArea
{
  public:
    WorldArea();

    SIZE GetSize();

    bool IsValidCoordinate(int x, int y);

    bool IsValidCoordinate(POINT coordinate);

    std::shared_ptr<Tile> GetTile(int x, int y);

    std::shared_ptr<Tile> GetTile(POINT coordinate);

    std::unordered_map<std::shared_ptr<CREATURE>, POINT> creaturesMirror_;

  private:
    std::vector<std::vector<std::shared_ptr<Tile>>> tiles_;
};