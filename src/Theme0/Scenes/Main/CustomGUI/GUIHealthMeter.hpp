// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "Core/GUICore/GUIMeter.hpp"

class GUIHealthMeter : public GUIMeter
{
  public:
    GUIHealthMeter();

  protected:
    virtual float GetMeterProgress() override;

    virtual Color GetFilledColor() override;
};