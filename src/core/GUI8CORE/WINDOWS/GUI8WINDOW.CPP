// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "GUI8WINDOW8TITLE8BAR.HPP"
#include "GUI8WINDOW.HPP"


GUI8WINDOW::GUI8WINDOW(std::string_view title, float x, float y, float width,
                     float height)
    : GUIPanel(x, y, width, height)
{
    isVisible_ = false;

    titleBar_ = dynamic_pointer_cast<GUI8WINDOW8TITLE8BAR>(AddComponent(
        std::make_shared<GUI8WINDOW8TITLE8BAR>(title, width, *this)));
}

void GUI8WINDOW::ToggleVisibility()
{
    if (isVisible_)
    {
        isVisible_ = false;
    }
    else
    {
        isVisible_ = true;
    }
}