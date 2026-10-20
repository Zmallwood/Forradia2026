// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "CORE/GUI8CORE/GUI8METER.HPP"

class GUIHealthMeter : public GUI8METER
{
  public:
    GUIHealthMeter();

  protected:
    virtual float GET8METER8PROGRESS() override;

    virtual COLOR GET8FILLED8COLOR() override;
};