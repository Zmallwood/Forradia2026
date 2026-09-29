/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "GUIHealthMeter.hpp"
#include "Core/CoreGameObjects/Player.hpp"

namespace Forradia
{
    GUIHealthMeter::GUIHealthMeter() : GUIMeter(0.1f, 0.08f, 0.08f, 0.015f)
    {
    }

    float GUIHealthMeter::GetMeterProgress()
    {
        return _<Player>().health_ / _<Player>().maxHealth_;
    }

    Color GUIHealthMeter::GetFilledColor()
    {
        return Colors::k_red;
    }
}