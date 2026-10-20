// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "CORE/GUI8CORE/GUI_PANEL.HPP"

class GUI8WINDOW8TITLE8BAR;

class GUI8WINDOW : public GUIPanel
{
  public:
    GUI8WINDOW(std::string_view title, float x, float y, float width,
              float height);

    void ToggleVisibility();

    std::shared_ptr<GUI8WINDOW8TITLE8BAR> titleBar_;
};