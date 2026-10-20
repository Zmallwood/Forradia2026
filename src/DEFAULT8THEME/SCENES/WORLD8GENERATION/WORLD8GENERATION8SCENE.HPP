//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "CORE/SCENES8CORE/I8SCENE.HPP"

namespace FORRADIA8GAME
{
    class WORLD8GENERATION8SCENE : public I8SCENE
    {
      protected:
        void ON8ENTER8DERIVED() override;
    };
}