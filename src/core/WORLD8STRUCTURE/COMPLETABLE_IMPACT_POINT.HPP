// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class CompletableImpactPoint
{
  public:
    POINT8F position;
    bool completed = false;
};