/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "world.hpp"
#include "Core/WorldStructure/world_area.hpp"

namespace Forradia
{
    world::world()
    {
        current_world_area_ = std::make_shared<world_area>();
    }
}