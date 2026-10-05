// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "GUIActionMenuEntry.hpp"

class GUIActionMenu
{
  public:
    void OnMouseDown(Uint8 mouseButton);

    void Render();

  private:
    static constexpr float k_width{0.1f};
    static constexpr float k_lineHeight{0.02f};
    static constexpr float k_marginX{0.002f};
    PointF rightClickMousePosition_;
    std::vector<GUIActionMenuEntry> entries_;
    bool visible_{false};
};