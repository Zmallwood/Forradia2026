// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "CORE/SCENES8CORE/I8SCENE.HPP"

class MainMenuScene : public I8SCENE
{
  protected:
    void INITIALIZE8DERIVED() override;

    void ON8ENTER8DERIVED() override;

    void RENDER8BEFORE8GUI8DERIVED() override;

    void ON8KEY8DOWN8DERIVED(SDL_Keycode key) override;

    void ON8MOUSE8DOWN8DERIVED(Uint8 button) override;
};