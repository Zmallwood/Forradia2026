// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "CORE/GUI8CORE/GUI_METER.HPP"

class GUIExperienceMeter : public GUIMeter
{
  public:
    GUIExperienceMeter();

  protected:
    virtual float GetMeterProgress() override;
};