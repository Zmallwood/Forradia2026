// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "KeyboardHotkeys.hpp"
#include "Theme0/Scenes/Main/CustomGUI/GUIEquipmentWindow.hpp"
#include "Theme0/Scenes/Main/CustomGUI/GUIInventoryWindow.hpp"

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