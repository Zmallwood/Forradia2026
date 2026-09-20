/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "NumberUtilities.hpp"

namespace Forradia
{
    int invert_speed(float speed)
    {
        return static_cast<int>(1000 / speed);
    }
}