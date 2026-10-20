// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "WORLD.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD_AREA.HPP"

World::World()
{
    currentWorldArea_ = std::make_shared<WorldArea>();
}