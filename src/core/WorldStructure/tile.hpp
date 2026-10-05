// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class TileObjects;
class Creature;
class NPC;

class Tile
{
  public:
    Tile();

    int ground_{0};
    int elevation_{0};
    std::shared_ptr<TileObjects> tileObjects_;
    std::shared_ptr<Creature> creature_;
    std::shared_ptr<NPC> npc_;
};