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

        void OnKeyDownDerived(SDL_Keycode key) override;

        void OnKeyUpDerived(SDL_Keycode key) override;

        void OnMouseDownDerived(Uint8 button) override;
    };
}