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

        void GoToScene(std::string_view scene_name);

        void UpdateCurrentScene();

        void RenderCurrentScene();

        void OnKeyDownCurrentScene(SDL_Keycode key);

        void OnKeyUpCurrentScene(SDL_Keycode key);

        void OnMouseDownCurrentScene(Uint8 button);

        void OnMouseUpCurrentScene(Uint8 button, int click_speed);

      private:
        void AddScene(std::string_view scene_name, IScene &scene);

        int current_scene_{0};
        std::unordered_map<int, IScene &> scenes_;
    };
}