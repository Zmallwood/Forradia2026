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
    class IntroScene : public IScene
    {
      protected:
        void RenderDerived() override;

        void OnKeyDown(SDL_Keycode key) override;

        void OnMouseDown(Uint8 button) override;
    };
}