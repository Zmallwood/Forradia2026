/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class ImageEntry
    {
      public:
        std::shared_ptr<SDL_Texture> texture;
        std::shared_ptr<SDL_Surface> surface;
    };
}