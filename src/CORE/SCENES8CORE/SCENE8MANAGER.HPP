//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME {
    class I8SCENE;

    class SCENE8MANAGER {
      public:
        SCENE8MANAGER();

        void GO8TO8SCENE(std::string_view sceneName);

        void UPDATE8CURRENT8SCENE();

        void RENDER8CURRENT8SCENE();

        void ON8KEY8DOWN8CURRENT8SCENE(SDL_Keycode key);

        void ON8KEY8UP8CURRENT8SCENE(SDL_Keycode key);

        void ON8MOUSE8DOWN8CURRENT8SCENE(Uint8 button);

        void ON8MOUSE8UP8CURRENT8SCENE(Uint8 button, int clickSpeed);

      private:
        void ADD8SCENE(std::string_view sceneName, I8SCENE &scene);

        int currentScene_{0};
        std::unordered_map<int, I8SCENE &> scenes_;
    };
}