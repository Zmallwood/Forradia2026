// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "CORE/GUI_CORE/GUI_PANEL.HPP"

class GUIWindowTitleBar;

class GUIWindow : public GUIPanel
{
  public:
    GUIWindow(std::string_view title, float x, float y, float width,
              float height);

    void ToggleVisibility();

    std::shared_ptr<GUIWindowTitleBar> titleBar_;
};