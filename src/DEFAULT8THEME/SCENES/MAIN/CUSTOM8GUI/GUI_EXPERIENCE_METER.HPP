//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "CORE/GUI8CORE/GUI8METER.HPP"

namespace FORRADIA8GAME
{
    class GUIExperienceMeter : public GUI8METER
    {
      public:
        GUIExperienceMeter();

      protected:
        virtual float GET8METER8PROGRESS() override;
    };
}