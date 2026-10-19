// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "GUI_WINDOW.HPP"
#include "GUI_WINDOW_TITLE_BAR.HPP"

GUIWindow::GUIWindow(std::string_view title, float x, float y, float width,
                     float height)
    : GUIPanel(x, y, width, height)
{
    isVisible_ = false;

    titleBar_ = dynamic_pointer_cast<GUIWindowTitleBar>(
        AddComponent(std::make_shared<GUIWindowTitleBar>(title, width, *this)));
}

void GUIWindow::ToggleVisibility()
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