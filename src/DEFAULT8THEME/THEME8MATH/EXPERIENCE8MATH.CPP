//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "EXPERIENCE8MATH.HPP"

namespace FORRADIA8GAME {
    int
    CALCULATE8CURRENT8LEVEL(int experience) {
        auto level{std::trunc(log2f(pow(experience + 70, 2) / 5000)) + 1};

        return static_cast<int>(level);
    }

    int
    CALCULATE8EXPERIENCE8FOR8LEVEL(int level) {
        auto experience{std::max(sqrtf(powf(2, level - 1) * 5000) - 70, 0.0F)};

        return static_cast<int>(experience);
    }

    int
    CALCULATE8EXPERIENCE8DIFFERENCE8TO8NEXT8LEVEL(int experience) {
        auto currentLevel{CALCULATE8CURRENT8LEVEL(experience)};

        auto nextLevel{currentLevel + 1};

        auto totalExperienceForCurrentLevel{
            CALCULATE8EXPERIENCE8FOR8LEVEL(currentLevel)};

        auto totalExperienceForNextLevel{
            CALCULATE8EXPERIENCE8FOR8LEVEL(nextLevel)};

        return totalExperienceForNextLevel - totalExperienceForCurrentLevel;
    }

    int
    CALCULATE8EXPERIENCE8REQUIRED8FOR8CURRENT8LEVEL8START(int experience) {
        auto currentLevel{CALCULATE8CURRENT8LEVEL(experience)};

        return CALCULATE8EXPERIENCE8FOR8LEVEL(currentLevel);
    }

    int
    CALCULATE8EXPERIENCE8GAINED8SINCE8LEVEL8START(int experience) {
        return experience -
               CALCULATE8EXPERIENCE8REQUIRED8FOR8CURRENT8LEVEL8START(
                   experience);
    }

    float
    CALCULATE8FRACTIONAL8EXPERIENCE8PROGRESS(int experience) {
        auto experienceGain{
            experience -
            CALCULATE8EXPERIENCE8REQUIRED8FOR8CURRENT8LEVEL8START(experience)};

        auto experienceDiff{
            CALCULATE8EXPERIENCE8DIFFERENCE8TO8NEXT8LEVEL(experience)};

        return static_cast<float>(experienceGain) / experienceDiff;
    }
}