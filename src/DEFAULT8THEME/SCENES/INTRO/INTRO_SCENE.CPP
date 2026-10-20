// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CORE/RENDERING/IMAGES/IMAGE8RENDERER.HPP"
#include "CORE/SCENES8CORE/SCENE_MANAGER.HPP"
#include "INTRO_SCENE.HPP"


void IntroScene::RenderBeforeGUIDerived()
{
    _<IMAGE8RENDERER>().DRAW8IMAGE("DefaultSceneBackground", 0.0f, 0.0f, 1.0f,
                                   1.0f);

    _<IMAGE8RENDERER>().DRAW8IMAGE("ForradiaLogo", 0.2f, 0.2f, 0.6f, 0.2f);
}

void IntroScene::OnKeyDownDerived(SDL_Keycode key)
{
    _<SceneManager>().GoToScene("MainMenuScene");
}

void IntroScene::OnMouseDownDerived(Uint8 button)
{
    _<SceneManager>().GoToScene("MainMenuScene");
}