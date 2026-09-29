/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "KeyboardHotkeys.hpp"
#include "Theme0/Scenes/Main/CustomGUI/GUIInventoryWindow.hpp"

namespace Forradia
{
    void KeyboardHotkeys::OnKeyDown(SDL_Keycode key)
    {
        if (key == SDLK_b)
        {
            _<GUIInventoryWindow>().ToggleVisibility();
        }
    }
}