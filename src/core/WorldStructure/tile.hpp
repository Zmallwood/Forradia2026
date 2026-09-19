/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class tile_objects;

    class tile
    {
      public:
        tile();

        int ground_{0};
        int elevation_{0};
        std::shared_ptr<tile_objects> tile_objects_;
    };
}