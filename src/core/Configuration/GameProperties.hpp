/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class GameProperties
    {
      public:
        static constexpr Size k_worldAreaSize_{100, 100};
        static constexpr float k_tileWidth_{0.05f};
        static constexpr int k_tileUnitsWidth_{20};
        static constexpr float k_viewWidth_{0.5f};
    };
}