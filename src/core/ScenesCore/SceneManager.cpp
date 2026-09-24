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
        AddScene("IntroScene", _<IntroScene>());
        AddScene("MainMenuScene", _<MainMenuScene>());
        AddScene("WorldGenerationScene", _<WorldGenerationScene>());
        AddScene("MainScene", _<MainScene>());

        GoToScene("IntroScene");
    }

    void SceneManager::AddScene(std::string_view sceneName, IScene &scene)
    {
        auto hash{Hash(sceneName)};

        scenes_.insert({hash, scene});
    }

    void SceneManager::GoToScene(std::string_view sceneName)
    {
        auto hash{Hash(sceneName)};

        if (scenes_.contains(hash))
        {
            currentScene_ = hash;

            scenes_.at(currentScene_).OnEnter();
        }
    }

    void SceneManager::UpdateCurrentScene()
    {
        if (scenes_.contains(currentScene_))
        {
            scenes_.at(currentScene_).Update();
        }
    }

    void SceneManager::RenderCurrentScene()
    {
        if (scenes_.contains(currentScene_))
        {
            scenes_.at(currentScene_).Render();
        }
    }

    void SceneManager::OnKeyDownCurrentScene(SDL_Keycode key)
    {
        if (scenes_.contains(currentScene_))
        {
            scenes_.at(currentScene_).OnKeyDown(key);
        }
    }

    void SceneManager::OnKeyUpCurrentScene(SDL_Keycode key)
    {
        if (scenes_.contains(currentScene_))
        {
            scenes_.at(currentScene_).OnKeyUp(key);
        }
    }

    void SceneManager::OnMouseDownCurrentScene(Uint8 button)
    {
        if (scenes_.contains(currentScene_))
        {
            scenes_.at(currentScene_).OnMouseDown(button);
        }
    }

    void SceneManager::OnMouseUpCurrentScene(Uint8 button, int clickSpeed)
    {
        if (scenes_.contains(currentScene_))
        {
            scenes_.at(currentScene_).OnMouseUp(button, clickSpeed);
        }
    }
}