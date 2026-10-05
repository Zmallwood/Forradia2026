/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "GUIExperienceMeter.hpp"
#include "Core/CoreGameObjects/Player.hpp"
#include "Theme0/Theme0Math/ExperienceMath.hpp"

GUIExperienceMeter::GUIExperienceMeter() : GUIMeter(0.0f, 0.985f, 1.0f, 0.015f)
{
}

float GUIExperienceMeter::GetMeterProgress()
{
    auto experience{_<Player>().experience_};

    auto progress{CalculateFractionalExperienceProgress(experience)};

    return progress;
}