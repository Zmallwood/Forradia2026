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
    class MainMenuScene : public IScene
    {
      protected:
        void InitializeDerived() override;

        void OnEnterDerived() override;

        void RenderBeforeGUIDerived() override;

        void OnKeyDownDerived(SDL_Keycode key) override;

        void OnMouseDownDerived(Uint8 button) override;
    };
}