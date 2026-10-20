//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "SCENE8MANAGER.HPP"
#include "DEFAULT8THEME/SCENES/INTRO/INTRO8SCENE.HPP"
#include "DEFAULT8THEME/SCENES/MAIN/MAIN8SCENE.HPP"
#include "DEFAULT8THEME/SCENES/MAIN8MENU/MAIN8MENU8SCENE.HPP"
#include "DEFAULT8THEME/SCENES/WORLD8GENERATION/WORLD8GENERATION8SCENE.HPP"
#include "I8SCENE.HPP"

namespace FORRADIA8GAME {
    SCENE8MANAGER::SCENE8MANAGER() {
        ADD8SCENE("IntroScene", _<INTRO8SCENE>());
        ADD8SCENE("MainMenuScene", _<MAIN8MENU8SCENE>());
        ADD8SCENE("WorldGenerationScene", _<WORLD8GENERATION8SCENE>());
        ADD8SCENE("MainScene", _<MAIN8SCENE>());
        GO8TO8SCENE("IntroScene");
    }

    void
    SCENE8MANAGER::ADD8SCENE(std::string_view sceneName, I8SCENE &scene) {
        auto hash = HASH(sceneName);

        scenes_.insert({hash, scene});

        scene.INITIALIZE();
    }

    void
    SCENE8MANAGER::GO8TO8SCENE(std::string_view sceneName) {
        auto hash = HASH(sceneName);

        if (scenes_.contains(hash)) {
            currentScene_ = hash;

            scenes_.at(currentScene_).ON8ENTER();
        }
    }

    void
    SCENE8MANAGER::UPDATE8CURRENT8SCENE() {
        if (scenes_.contains(currentScene_))
            scenes_.at(currentScene_).UPDATE();
    }

    void
    SCENE8MANAGER::RENDER8CURRENT8SCENE() {
        if (scenes_.contains(currentScene_))
            scenes_.at(currentScene_).RENDER();
    }

    void
    SCENE8MANAGER::ON8KEY8DOWN8CURRENT8SCENE(SDL_Keycode key) {
        if (scenes_.contains(currentScene_))
            scenes_.at(currentScene_).ON8KEY8DOWN(key);
    }

    void
    SCENE8MANAGER::ON8KEY8UP8CURRENT8SCENE(SDL_Keycode key) {
        if (scenes_.contains(currentScene_))
            scenes_.at(currentScene_).ON8KEY8UP(key);
    }

    void
    SCENE8MANAGER::ON8MOUSE8DOWN8CURRENT8SCENE(Uint8 button) {
        if (scenes_.contains(currentScene_))
            scenes_.at(currentScene_).ON8MOUSE8DOWN(button);
    }

    void
    SCENE8MANAGER::ON8MOUSE8UP8CURRENT8SCENE(Uint8 button, int clickSpeed) {
        if (scenes_.contains(currentScene_))
            scenes_.at(currentScene_).ON8MOUSE8UP(button, clickSpeed);
    }
}