//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

class FPS8COUNTER
{
  public:
    void UPDATE();

    void RENDER();

  private:
    int fps_ = 0;
    int framesCounter_ = 0;
    int ticksLastUpdate_ = 0;
};