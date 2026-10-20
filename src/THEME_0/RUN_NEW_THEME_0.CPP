// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "RUN_NEW_THEME_0.HPP"
#include "CORE/GAME.HPP"

void RUN_NEW_THEME_0()
{
    _<GAME>().START();

    DESTROY8SINGLETON<GAME>();
}