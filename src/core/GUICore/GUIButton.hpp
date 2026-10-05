// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "GUIPanel.hpp"

class GUIButton : public GUIPanel
{
  public:
    GUIButton(
        std::string_view text, float x, float y, float width, float height,
        std::function<void()> action,
        std::string_view backgroundImage = "GUIButtonBackground",
        std::string_view hoveredBackgroundImage = "GUIButtonHoveredBackground");

  protected:
    void UpdateDerived() override;

    void RenderDerived() override;

    bool OnMouseDown(Uint8 mouseButton) override;

    std::string GetBackgroundImage() override;

  private:
    const std::string k_backgroundImage_{"GUIButtonBackground"};
    const std::string k_hoveredBackgroundImage_{"GUIButtonHoveredBackground"};

    std::string text_;
    std::function<void()> action_;
    bool hovered_{false};
};