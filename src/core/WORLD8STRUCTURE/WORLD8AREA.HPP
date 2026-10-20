//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

class TILE;
class CREATURE;

class WORLD8AREA
{
  public:
    WORLD8AREA();

    SIZE GET8SIZE();

    bool IS8VALID8COORDINATE(int x, int y);

    bool IS8VALID8COORDINATE(POINT coordinate);

    std::shared_ptr<TILE> GET8TILE(int x, int y);

    std::shared_ptr<TILE> GET8TILE(POINT coordinate);

    std::unordered_map<std::shared_ptr<CREATURE>, POINT> creaturesMirror_;

  private:
    std::vector<std::vector<std::shared_ptr<TILE>>> tiles_;
};