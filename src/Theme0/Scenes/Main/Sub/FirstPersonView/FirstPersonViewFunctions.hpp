/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

#include "PositionedObject.hpp"

namespace Forradia
{
    std::map<std::pair<int, int>, PositionedObject> GetOrderedObjects();
}