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
    void main_menu_scene::render_derived()
    {
        _<image_renderer>().draw_image("default_scene_background", 0.0f, 0.0f,
                                       1.0f, 1.0f);

        _<image_renderer>().draw_image("forradia_logo", 0.3f, 0.2f, 0.4f,
                                       0.15f);
    }

    void main_menu_scene::on_key_down(SDL_Keycode key)
    {
        _<scene_manager>().go_to_scene("world_generation_scene");
    }

    void main_menu_scene::on_mouse_down(Uint8 button)
    {
        _<scene_manager>().go_to_scene("world_generation_scene");
    }
}