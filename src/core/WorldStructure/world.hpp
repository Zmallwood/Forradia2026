/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class WorldArea;

    class World
    {
      public:
        World();

        std::shared_ptr<WorldArea> current_world_area_;
    };
}