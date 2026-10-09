// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class Point
{
  public:
    auto operator<=>(const Point &) const = default;

    Point operator+(const Point &other) const;

    int x = 0;
    int y = 0;
};