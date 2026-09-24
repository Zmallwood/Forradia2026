/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class IScene;

    class SceneManager
    {
      public:
        SceneManager();

        void GoToScene(std::string_view sceneName);

        void UpdateCurrentScene();

        void RenderCurrentScene();

        void OnKeyDownCurrentScene(SDL_Keycode key);

        void OnKeyUpCurrentScene(SDL_Keycode key);

        void OnMouseDownCurrentScene(Uint8 button);

        void OnMouseUpCurrentScene(Uint8 button, int clickSpeed);

      private:
        void AddScene(std::string_view sceneName, IScene &scene);

        int currentScene_{0};
        std::unordered_map<int, IScene &> scenes_;
    };
}