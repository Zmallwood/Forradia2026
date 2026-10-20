// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class OBJECT;

class PositionedObject
{
  public:
    POINT position_ = {-1, -1};
    std::shared_ptr<OBJECT> object_;
};