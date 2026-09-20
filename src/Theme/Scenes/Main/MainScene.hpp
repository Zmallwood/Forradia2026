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
    class MainScene : public IScene
    {
      protected:
        void UpdateDerived() override;

        void RenderDerived() override;

        void OnKeyDown(SDL_Keycode key) override;

        void OnKeyUp(SDL_Keycode key) override;

        void OnMouseDown(Uint8 button) override;
    };
}