//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "KEYBOARD8HOTKEYS.HPP"
#include "DEFAULT8THEME/SCENES/MAIN/CUSTOM8GUI/GUI8EQUIPMENT8WINDOW.HPP"
#include "DEFAULT8THEME/SCENES/MAIN/CUSTOM8GUI/GUI8INVENTORY8WINDOW.HPP"

namespace FORRADIA8GAME
{
    void
    KEYBOARD8HOTKEYS::ON8KEY8DOWN(SDL_Keycode key)
    {
        if (key == SDLK_b)
        {
            _<GUI8INVENTORY8WINDOW>().TOGGLE8VISIBILITY();
        }
        else if (key == SDLK_e)
        {
            _<GUI8EQUIPMENT8WINDOW>().TOGGLE8VISIBILITY();
        }
    }
}