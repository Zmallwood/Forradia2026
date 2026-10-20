// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CORE/GAME.HPP"
#include "RUN8NEW8DEFAULT8THEME.HPP"

void
RUN8NEW8DEFAULT8THEME()
{
    _<GAME>().START();

    DESTROY8SINGLETON<GAME>();
}