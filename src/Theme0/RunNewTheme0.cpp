/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "RunNewTheme0.hpp"
#include "Core/Game.hpp"

void RunNewTheme0()
{
    _<Game>().Start();

    DestroySingleton<Game>();
}