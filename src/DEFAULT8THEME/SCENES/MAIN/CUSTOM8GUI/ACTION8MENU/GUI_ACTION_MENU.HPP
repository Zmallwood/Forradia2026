//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "GUI_ACTION_MENU_ENTRY.HPP"

class GUIActionMenu
{
  public:
    void OnMouseDown(Uint8 mouseButton);

    void Render();

  private:
    static constexpr float kWidth = 0.1f;
    static constexpr float kLineHeight = 0.02f;
    static constexpr float kMarginX = 0.002f;
    POINT8F rightClickMousePosition_;
    std::vector<GUIActionMenuEntry> entries_;
    bool visible_ = false;
};