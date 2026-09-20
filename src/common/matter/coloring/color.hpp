/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class Color
    {
      public:
        SDL_Color ToSDLColor();

        float r{0.0f};
        float g{0.0f};
        float b{0.0f};
        float a{1.0f};
    };
}