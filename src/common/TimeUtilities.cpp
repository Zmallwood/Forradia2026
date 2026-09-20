/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "TimeUtilities.hpp"

namespace Forradia
{
    int Ticks()
    {
        return SDL_GetTicks();
    }
}