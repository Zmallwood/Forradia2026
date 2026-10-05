// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class WorldArea;

class World
{
  public:
    World();

    std::shared_ptr<WorldArea> currentWorldArea_;
};