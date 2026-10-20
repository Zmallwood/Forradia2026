// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "GUI8COMPONENT.HPP"

class GUI8PANEL : public GUI8COMPONENT
{
  public:
    GUI8PANEL(float x, float y, float width, float height);

    SIZE8F size_{0.0f, 0.0f};

  protected:
    virtual bool ON8MOUSE8DOWN(Uint8 mouseButton) override;

    virtual void RENDER8DERIVED() override;

    virtual std::string GET8BACKGROUND8IMAGE();

    RECT8F GET8BOUNDS();

  private:
    inline static const std::string k_defaultBackgroundImage_ =
        "GUIPanelBackground";
};