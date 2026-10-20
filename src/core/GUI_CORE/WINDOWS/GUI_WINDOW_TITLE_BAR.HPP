// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "CORE/GUI_CORE/GUI_PANEL.HPP"

class GUIWindow;

class GUIWindowTitleBar : public GUIPanel
{
  public:
    GUIWindowTitleBar(std::string_view title, float width,
                      GUIWindow &guiWindow);

  protected:
    void UpdateDerived() override;

    void RenderDerived() override;

    bool OnMouseDown(Uint8 mouseButton) override;

    bool OnMouseUp(Uint8 mouseButton, int clickSpeed) override;

    virtual std::string GetBackgroundImage() override;

    POINT8F GetPosition() override;

    void SetPosition(POINT8F value) override;

  private:
    inline static const std::string k_defaultBackgroundImage_ =
        "GUIWindowTitleBarBackground";
    static constexpr POINT8F k_margin_ = {0.01F, 0.01F};

    GUIWindow &guiWindow_;
    std::string title_;
    POINT8F positionStartMove_;
    POINT8F mousePositionStartMove_;
    bool isMoving_{false};
};