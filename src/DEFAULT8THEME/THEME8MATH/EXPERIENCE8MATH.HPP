//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME
{
    int CALCULATE8CURRENT8LEVEL(int experience);

    int CALCULATE8EXPERIENCE8FOR8LEVEL(int level);

    int CALCULATE8EXPERIENCE8DIFFERENCE8TO8NEXT8LEVEL(int experience);

    int CALCULATE8EXPERIENCE8REQUIRED8FOR8CURRENT8LEVEL8START(int experience);

    int CALCULATE8EXPERIENCE8GAINED8SINCE8LEVEL8START(int experience);

    float CALCULATE8FRACTIONAL8EXPERIENCE8PROGRESS(int experience);
}