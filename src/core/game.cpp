/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "game.hpp"
#include "Engine/engine.hpp"

namespace Forradia
{
    void game::start()
    {
        _<engine>().start();
    }
}