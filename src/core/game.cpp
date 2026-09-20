/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "Game.hpp"
#include "Engine/Engine.hpp"

namespace Forradia
{
    void Game::Start()
    {
        _<Engine>().Start();
    }
}