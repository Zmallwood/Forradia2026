// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "INTRO_SCENE.HPP"
#include "CORE/RENDERING/IMAGES/IMAGE_RENDERER.HPP"
#include "CORE/SCENES_CORE/SCENE_MANAGER.HPP"

void IntroScene::RenderBeforeGUIDerived()
{
    _<ImageRenderer>().DrawImage("DefaultSceneBackground", 0.0f, 0.0f, 1.0f,
                                 1.0f);

    _<ImageRenderer>().DrawImage("ForradiaLogo", 0.2f, 0.2f, 0.6f, 0.2f);
}

void IntroScene::OnKeyDownDerived(SDL_Keycode key)
{
    _<SceneManager>().GoToScene("MainMenuScene");
}

void IntroScene::OnMouseDownDerived(Uint8 button)
{
    _<SceneManager>().GoToScene("MainMenuScene");
}