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
    world::world()
    {
        current_world_area_ = std::make_shared<world_area>();
    }
}