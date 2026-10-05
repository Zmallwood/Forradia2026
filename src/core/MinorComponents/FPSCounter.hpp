// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class FPSCounter
{
  public:
    void Update();

    void Render();

  private:
    int fps_{0};
    int framesCounter_{0};
    int ticksLastUpdate_{0};
};