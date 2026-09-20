/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class game_properties
    {
      public:
        static constexpr size k_world_area_size_{100, 100};
        static constexpr float k_tile_width_{0.05f};
        static constexpr int k_tile_units_width_{20};
        static constexpr float k_view_width_{0.5f};
    };
}