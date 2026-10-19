// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "GUI_HEALTH_METER.HPP"
#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"

GUIHealthMeter::GUIHealthMeter() : GUIMeter(0.1f, 0.08f, 0.08f, 0.015f)
{
}

float GUIHealthMeter::GetMeterProgress()
{
    return _<Player>().health_ / _<Player>().maxHealth_;
}

COLOR GUIHealthMeter::GetFilledColor()
{
    return COLORS::k_red;
}