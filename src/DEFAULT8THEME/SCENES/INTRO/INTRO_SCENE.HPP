// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "CORE/SCENES8CORE/I_SCENE.HPP"

class IntroScene : public IScene
{
  protected:
    void RenderBeforeGUIDerived() override;

    void OnKeyDownDerived(SDL_Keycode key) override;

    void OnMouseDownDerived(Uint8 button) override;
};