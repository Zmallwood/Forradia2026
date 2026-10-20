//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "WORLD.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD8AREA.HPP"

WORLD::WORLD()
{
    currentWorldArea_ = std::make_shared<WORLD8AREA>();
}