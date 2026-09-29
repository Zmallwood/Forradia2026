/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    int CalculateCurrentLevel(int experience);

    int CalculateExperienceForLevel(int level);

    int CalculateExperienceDifferenceToNextLevel(int experience);

    int CalculateExperienceRequiredForCurrentLevelStart(int experience);

    int CalculateExperienceGainedSinceLevelStart(int experience);

    float CalculateFractionalExperienceProgress(int experience);
}