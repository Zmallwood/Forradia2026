// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class TILE8OBJECTS;
class CREATURE;
class NPC;

class TILE
{
  public:
    TILE();

    int ground_ = 0;
    int elevation_ = 0;
    std::shared_ptr<TILE8OBJECTS> tileObjects_;
    std::shared_ptr<CREATURE> creature_;
    std::shared_ptr<NPC> npc_;
};