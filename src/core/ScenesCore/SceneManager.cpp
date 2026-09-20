/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "SceneManager.hpp"
#include "IScene.hpp"
#include "Theme/Scenes/Intro/IntroScene.hpp"
#include "Theme/Scenes/Main/MainScene.hpp"
#include "Theme/Scenes/MainMenu/MainMenuScene.hpp"
#include "Theme/Scenes/WorldGeneration/WorldGenerationScene.hpp"


namespace Forradia
{
    SceneManager::SceneManager()
    {
        AddScene("intro_scene", _<IntroScene>());
        AddScene("main_menu_scene", _<MainMenuScene>());
        AddScene("world_generation_scene", _<WorldGenerationScene>());
        AddScene("main_scene", _<MainScene>());

        GoToScene("intro_scene");
    }

    void SceneManager::AddScene(std::string_view scene_name, IScene &scene)
    {
        auto hash{GetHash(scene_name)};

        scenes_.insert({hash, scene});
    }

    void SceneManager::GoToScene(std::string_view scene_name)
    {
        auto hash{GetHash(scene_name)};

        if (scenes_.contains(hash))
        {
            current_scene_ = hash;

            scenes_.at(current_scene_).OnEnter();
        }
    }

    void SceneManager::UpdateCurrentScene()
    {
        if (scenes_.contains(current_scene_))
        {
            scenes_.at(current_scene_).Update();
        }
    }

    void SceneManager::RenderCurrentScene()
    {
        if (scenes_.contains(current_scene_))
        {
            scenes_.at(current_scene_).Render();
        }
    }

    void SceneManager::OnKeyDownCurrentScene(SDL_Keycode key)
    {
        if (scenes_.contains(current_scene_))
        {
            scenes_.at(current_scene_).OnKeyDown(key);
        }
    }

    void SceneManager::OnKeyUpCurrentScene(SDL_Keycode key)
    {
        if (scenes_.contains(current_scene_))
        {
            scenes_.at(current_scene_).OnKeyUp(key);
        }
    }

    void SceneManager::OnMouseDownCurrentScene(Uint8 button)
    {
        if (scenes_.contains(current_scene_))
        {
            scenes_.at(current_scene_).OnMouseDown(button);
        }
    }

    void SceneManager::OnMouseUpCurrentScene(Uint8 button, int click_speed)
    {
        if (scenes_.contains(current_scene_))
        {
            scenes_.at(current_scene_).OnMouseUp(button, click_speed);
        }
    }
}