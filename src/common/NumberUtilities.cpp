/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "NumberUtilities.hpp"

namespace Forradia
{
    int InvertSpeed(float speed)
    {
        return static_cast<int>(1000 / speed);
    }
}