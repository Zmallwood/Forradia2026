// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class POINT_F
{
  public:
    void operator+=(const POINT_F &other);

    POINT_F operator+(const POINT_F &other) const;

    POINT_F operator-(const POINT_F &other) const;

    float x = 0.0f;
    float y = 0.0f;
};