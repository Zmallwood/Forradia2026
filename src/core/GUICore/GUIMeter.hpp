/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

#include "GUIComponent.hpp"

class GUIMeter : public GUIComponent
{
  public:
    GUIMeter(float x, float y, float width, float height);

    SizeF size_;

  protected:
    virtual void RenderDerived() override;

    virtual float GetMeterProgress();

    virtual Color GetFilledColor();
};