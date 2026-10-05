// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "CursorStyles.hpp"

class Cursor
{
  public:
    Cursor();

    void Reset();

    void Render();

    CursorStyles cursorStyle_{CursorStyles::Default};

  private:
    static constexpr float k_cursorSize_{0.05f};
};