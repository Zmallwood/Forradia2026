// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class CompletableImpactPoint
{
  public:
    POINT_F position;
    bool completed = false;
};