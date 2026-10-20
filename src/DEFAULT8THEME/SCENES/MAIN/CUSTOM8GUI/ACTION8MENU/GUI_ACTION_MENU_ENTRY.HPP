// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class GUIActionMenuEntry
{
  public:
    std::string label;
    std::function<void()> action;
};