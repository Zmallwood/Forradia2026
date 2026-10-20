// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "CORE/GUI8CORE/GUI_PANEL.HPP"

class GUI8WINDOW;

class GUI8WINDOW8TITLE8BAR : public GUIPanel
{
  public:
    GUI8WINDOW8TITLE8BAR(std::string_view title, float width,
                         GUI8WINDOW &guiWindow);

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

    GUI8WINDOW &guiWindow_;
    std::string title_;
    POINT8F positionStartMove_;
    POINT8F mousePositionStartMove_;
    bool isMoving_{false};
};