// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "CompletableImpactPoint.hpp"

class Object
{
  public:
    Object(int type);

    Object(std::string_view typeName);

    int type_{0};
    int quantity_{1};
    std::vector<CompletableImpactPoint> impactPoints_;
};