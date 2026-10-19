// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "KEYBOARD_HOTKEYS.HPP"
#include "THEME_0/SCENES/MAIN/CUSTOM_GUI/GUI_EQUIPMENT_WINDOW.HPP"
#include "THEME_0/SCENES/MAIN/CUSTOM_GUI/GUI_INVENTORY_WINDOW.HPP"

void KeyboardHotkeys::OnKeyDown(SDL_Keycode key)
{
    if (key == SDLK_b)
    {
        _<GUIInventoryWindow>().ToggleVisibility();
    }
    else if (key == SDLK_e)
    {
        _<GUIEquipmentWindow>().ToggleVisibility();
    }
}