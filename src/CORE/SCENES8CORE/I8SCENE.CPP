//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "I8SCENE.HPP"
#include "CORE/GUI8CORE/GUI.HPP"

namespace FORRADIA8GAME {
    I8SCENE::I8SCENE() : mGUI(std::make_shared<GUI>()) {
    }

    void
    I8SCENE::INITIALIZE() {
        INITIALIZE8DERIVED();
    }

    void
    I8SCENE::ON8ENTER() {
        ON8ENTER8DERIVED();
    }

    void
    I8SCENE::UPDATE() {
        mGUI->UPDATE();
        UPDATE8DERIVED();
    }

    void
    I8SCENE::RENDER() {
        RENDER8BEFORE8GUI8DERIVED();
        mGUI->RENDER();
        RENDER8AFTER8GUI8DERIVED();
    }

    void
    I8SCENE::ON8KEY8DOWN(SDL_Keycode key) {
        if (mGUI->ON8KEY8DOWN(key))
            return;
        ON8KEY8DOWN8DERIVED(key);
    }

    void
    I8SCENE::ON8KEY8UP(SDL_Keycode key) {
        if (mGUI->ON8KEY8UP(key))
            return;
        ON8KEY8UP8DERIVED(key);
    }

    void
    I8SCENE::ON8MOUSE8DOWN(Uint8 button) {
        if (mGUI->ON8MOUSE8DOWN(button))
            return;
        ON8MOUSE8DOWN8DERIVED(button);
    }

    void
    I8SCENE::ON8MOUSE8UP(Uint8 button, int clickSpeed) {
        if (mGUI->ON8MOUSE8UP(button, clickSpeed))
            return;
        ON8MOUSE8UP8DERIVED(button, clickSpeed);
    }
}