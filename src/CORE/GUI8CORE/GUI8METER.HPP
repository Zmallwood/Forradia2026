//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "GUI8COMPONENT.HPP"

namespace FORRADIA8GAME {
    class GUI8METER : public GUI8COMPONENT {
      public:
        GUI8METER(float x, float y, float width, float height);

        SIZE8F mSize;

      protected:
        virtual void RENDER8DERIVED() override;

        virtual float GET8METER8PROGRESS();

        virtual COLOR GET8FILLED8COLOR();
    };
}