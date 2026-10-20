// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"
#include "DEFAULT8THEME/THEME8MATH/EXPERIENCE_MATH.HPP"
#include "GUI_EXPERIENCE_METER.HPP"

GUIExperienceMeter::GUIExperienceMeter() : GUI8METER(0.0f, 0.985f, 1.0f, 0.015f)
{
}

float GUIExperienceMeter::GET8METER8PROGRESS()
{
    auto experience = _<PLAYER>().experience_;

    auto progress = CalculateFractionalExperienceProgress(experience);

    return progress;
}