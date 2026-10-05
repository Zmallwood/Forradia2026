// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "Game.hpp"
#include "Engine/Engine.hpp"

void Game::Start()
{
    _<Engine>().Start();

    DestroySingleton<Engine>();
}