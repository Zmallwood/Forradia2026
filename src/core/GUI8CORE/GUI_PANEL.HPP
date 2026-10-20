// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "GUI_COMPONENT.HPP"

class GUIPanel : public GUIComponent
{
  public:
    GUIPanel(float x, float y, float width, float height);

    SIZE8F size_{0.0f, 0.0f};

  protected:
    virtual bool OnMouseDown(Uint8 mouseButton) override;

    virtual void RenderDerived() override;

    virtual std::string GetBackgroundImage();

    RECT8F GetBounds();

  private:
    inline static const std::string k_defaultBackgroundImage_ =
        "GUIPanelBackground";
};