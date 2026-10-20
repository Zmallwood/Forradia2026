// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "GUI_EXPERIENCE_METER.HPP"
#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"
#include "DEFAULT8THEME/THEME8MATH/EXPERIENCE_MATH.HPP"

GUIExperienceMeter::GUIExperienceMeter() : GUIMeter(0.0f, 0.985f, 1.0f, 0.015f)
{
}

float GUIExperienceMeter::GetMeterProgress()
{
    auto experience = _<PLAYER>().experience_;

    auto progress = CalculateFractionalExperienceProgress(experience);

    return progress;
}