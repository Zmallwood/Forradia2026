//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "KEYBOARD_HOTKEYS.HPP"
#include "DEFAULT8THEME/SCENES/MAIN/CUSTOM8GUI/GUI_EQUIPMENT_WINDOW.HPP"
#include "DEFAULT8THEME/SCENES/MAIN/CUSTOM8GUI/GUI_INVENTORY_WINDOW.HPP"

void
KeyboardHotkeys::OnKeyDown(SDL_Keycode key)
{
    if (key == SDLK_b)
    {
        _<GUIInventoryWindow>().TOGGLE8VISIBILITY();
    }
    else if (key == SDLK_e)
    {
        _<GUIEquipmentWindow>().TOGGLE8VISIBILITY();
    }
}