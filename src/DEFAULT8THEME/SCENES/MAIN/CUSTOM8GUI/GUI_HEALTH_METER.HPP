// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "CORE/GUI8CORE/GUI_METER.HPP"

class GUIHealthMeter : public GUIMeter
{
  public:
    GUIHealthMeter();

  protected:
    virtual float GetMeterProgress() override;

    virtual COLOR GetFilledColor() override;
};