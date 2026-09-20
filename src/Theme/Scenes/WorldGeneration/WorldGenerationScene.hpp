/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

#include "Core/ScenesCore/IScene.hpp"

namespace Forradia
{
    class world_generation_scene : public i_scene
    {
      protected:
        void on_enter() override;
    };
}