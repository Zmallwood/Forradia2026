// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "GUI_COMPONENT.HPP"

class GUIMeter : public GUIComponent
{
  public:
    GUIMeter(float x, float y, float width, float height);

    SIZE8F size_;

  protected:
    virtual void RenderDerived() override;

    virtual float GetMeterProgress();

    virtual COLOR GetFilledColor();
};