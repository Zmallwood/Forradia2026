// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "Core/ScenesCore/IScene.hpp"

class MainScene : public IScene
{
  protected:
    void InitializeDerived() override;

    void OnEnterDerived() override;

    void UpdateDerived() override;

    void RenderBeforeGUIDerived() override;

    void RenderAfterGUIDerived() override;

    void OnKeyDownDerived(SDL_Keycode key) override;

    void OnKeyUpDerived(SDL_Keycode key) override;

    void OnMouseDownDerived(Uint8 button) override;

    void OnMouseUpDerived(Uint8 button, int clickSpeed) override;
};