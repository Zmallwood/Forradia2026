/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "World.hpp"
#include "Core/WorldStructure/WorldArea.hpp"

namespace Forradia
{
    World::World()
    {
        currentWorldArea_ = std::make_shared<WorldArea>();
    }
}