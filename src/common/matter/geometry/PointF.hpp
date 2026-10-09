// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class PointF
{
  public:
    void operator+=(const PointF &other);

    PointF operator+(const PointF &other) const;

    PointF operator-(const PointF &other) const;

    float x = 0.0f;
    float y = 0.0f;
};