// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "RUN8NEW8DEFAULT8THEME.HPP"
#include "CORE/GAME.HPP"

void RUN8NEW8DEFAULT8THEME()
{
    _<GAME>().START();

    DESTROY8SINGLETON<GAME>();
}