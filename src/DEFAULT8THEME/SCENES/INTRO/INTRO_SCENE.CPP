//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "INTRO_SCENE.HPP"
#include "CORE/RENDERING/IMAGES/IMAGE8RENDERER.HPP"
#include "CORE/SCENES8CORE/SCENE8MANAGER.HPP"

namespace FORRADIA
{
    void
    IntroScene::RENDER8BEFORE8GUI8DERIVED()
    {
        _<IMAGE8RENDERER>().DRAW8IMAGE("DefaultSceneBackground", 0.0f, 0.0f,
                                       1.0f, 1.0f);

        _<IMAGE8RENDERER>().DRAW8IMAGE("ForradiaLogo", 0.2f, 0.2f, 0.6f, 0.2f);
    }

    void
    IntroScene::ON8KEY8DOWN8DERIVED(SDL_Keycode key)
    {
        _<SCENE8MANAGER>().GO8TO8SCENE("MainMenuScene");
    }

    void
    IntroScene::ON8MOUSE8DOWN8DERIVED(Uint8 button)
    {
        _<SCENE8MANAGER>().GO8TO8SCENE("MainMenuScene");
    }
}