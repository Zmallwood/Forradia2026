// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "GAME.HPP"
#include "ENGINE/ENGINE.HPP"

void GAME::START()
{
    _<ENGINE>().START();

    DESTROY_SINGLETON<ENGINE>();
}