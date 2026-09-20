/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "SceneManager.hpp"
#include "Theme/Scenes/Intro/IntroScene.hpp"
#include "Theme/Scenes/Main/MainScene.hpp"
#include "Theme/Scenes/MainMenu/MainMenuScene.hpp"
#include "Theme/Scenes/WorldGeneration/WorldGenerationScene.hpp"
#include "IScene.hpp"

namespace Forradia
{
    scene_manager::scene_manager()
    {
        add_scene("intro_scene", _<intro_scene>());
        add_scene("main_menu_scene", _<main_menu_scene>());
        add_scene("world_generation_scene", _<world_generation_scene>());
        add_scene("main_scene", _<main_scene>());

        go_to_scene("intro_scene");
    }

    void scene_manager::add_scene(std::string_view scene_name, i_scene &scene)
    {
        auto hash{get_hash(scene_name)};

        scenes_.insert({hash, scene});
    }

    void scene_manager::go_to_scene(std::string_view scene_name)
    {
        auto hash{get_hash(scene_name)};

        if (scenes_.contains(hash))
        {
            current_scene_ = hash;

            scenes_.at(current_scene_).on_enter();
        }
    }

    void scene_manager::update_current_scene()
    {
        if (scenes_.contains(current_scene_))
        {
            scenes_.at(current_scene_).update();
        }
    }

    void scene_manager::render_current_scene()
    {
        if (scenes_.contains(current_scene_))
        {
            scenes_.at(current_scene_).render();
        }
    }

    void scene_manager::on_key_down_current_scene(SDL_Keycode key)
    {
        if (scenes_.contains(current_scene_))
        {
            scenes_.at(current_scene_).on_key_down(key);
        }
    }

    void scene_manager::on_key_up_current_scene(SDL_Keycode key)
    {
        if (scenes_.contains(current_scene_))
        {
            scenes_.at(current_scene_).on_key_up(key);
        }
    }

    void scene_manager::on_mouse_down_current_scene(Uint8 button)
    {
        if (scenes_.contains(current_scene_))
        {
            scenes_.at(current_scene_).on_mouse_down(button);
        }
    }

    void scene_manager::on_mouse_up_current_scene(Uint8 button, int click_speed)
    {
        if (scenes_.contains(current_scene_))
        {
            scenes_.at(current_scene_).on_mouse_up(button, click_speed);
        }
    }
}