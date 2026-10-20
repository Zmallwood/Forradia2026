//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "POSITIONED_OBJECT.HPP"

std::map<std::pair<int, int>, PositionedObject> GetOrderedObjects();

POINT GetHoveredTilePosition(POINT8F mouseOffset);