/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "time_utilities.hpp"

namespace Forradia
{
    int ticks()
    {
        return SDL_GetTicks();
    }
}