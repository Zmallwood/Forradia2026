/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "MainMenuScene.hpp"
#include "Core/Rendering/Images/ImageRenderer.hpp"
#include "Core/ScenesCore/SceneManager.hpp"

namespace Forradia
{
    void MainMenuScene::RenderDerived()
    {
        _<ImageRenderer>().DrawImage("default_scene_background", 0.0f, 0.0f,
                                     1.0f, 1.0f);

        _<ImageRenderer>().DrawImage("forradia_logo", 0.3f, 0.2f, 0.4f, 0.15f);
    }

    void MainMenuScene::OnKeyDown(SDL_Keycode key)
    {
        _<SceneManager>().GoToScene("world_generation_scene");
    }

    void MainMenuScene::OnMouseDown(Uint8 button)
    {
        _<SceneManager>().GoToScene("world_generation_scene");
    }
}