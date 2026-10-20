//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "GAME.HPP"
#include "ENGINE/ENGINE.HPP"

namespace FORRADIA
{
    void
    GAME::START()
    {
        _<ENGINE>().START();

        DESTROY8SINGLETON<ENGINE>();
    }
}