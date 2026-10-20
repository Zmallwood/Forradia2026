// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "COMPLETABLE8IMPACT8POINT.HPP"

class Object
{
  public:
    Object(int type);

    Object(std::string_view typeName);

    int type_ = 0;
    int quantity_ = 1;
    std::vector<COMPLETABLE8IMPACT8POINT> impactPoints_;
};