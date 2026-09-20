/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "RunNewTheme.hpp"
#include "Core/Game.hpp"

namespace Forradia
{
    void run_new_theme()
    {
        _<game>().start();
    }
}