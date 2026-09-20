/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "IntroScene.hpp"
#include "Core/Rendering/Images/ImageRenderer.hpp"
#include "Core/ScenesCore/SceneManager.hpp"

namespace Forradia
{
    void IntroScene::RenderDerived()
    {
        _<ImageRenderer>().DrawImage("default_scene_background", 0.0f, 0.0f,
                                     1.0f, 1.0f);

        _<ImageRenderer>().DrawImage("forradia_logo", 0.2f, 0.2f, 0.6f, 0.2f);
    }

    void IntroScene::OnKeyDown(SDL_Keycode key)
    {
        _<SceneManager>().GoToScene("main_menu_scene");
    }

    void IntroScene::OnMouseDown(Uint8 button)
    {
        _<SceneManager>().GoToScene("main_menu_scene");
    }
}