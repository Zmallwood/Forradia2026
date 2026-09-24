/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "TimeUtilities.hpp"

namespace Forradia
{
    int Now()
    {
        return SDL_GetTicks();
    }
}