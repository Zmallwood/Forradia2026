//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "MAIN8MENU8SCENE.HPP"
#include "CORE/ENGINE/ENGINE.HPP"
#include "CORE/GUI8CORE/GUI.HPP"
#include "CORE/GUI8CORE/GUI8BUTTON.HPP"
#include "CORE/GUI8CORE/GUI8PANEL.HPP"
#include "CORE/GUI8CORE/GUI8TEXT8CONSOLE.HPP"
#include "CORE/RENDERING/IMAGES/IMAGE8RENDERER.HPP"
#include "CORE/SCENES8CORE/SCENE8MANAGER.HPP"

namespace FORRADIA8GAME {
    void
    MAIN8MENU8SCENE::INITIALIZE8DERIVED() {
        gui_->ADD8COMPONENT(GET8SINGLETON8PTR<GUI8TEXT8CONSOLE>());

        gui_->ADD8COMPONENT(
            std::make_shared<GUI8PANEL>(0.4F, 0.4F, 0.2F, 0.3F));

        gui_->ADD8COMPONENT(std::make_shared<GUI8BUTTON>(
            "Play", 0.45F, 0.44F, 0.1F, 0.04F, [this]() {
                _<SCENE8MANAGER>().GO8TO8SCENE("WorldGenerationScene");
            }));

        gui_->ADD8COMPONENT(std::make_shared<GUI8BUTTON>(
            "Editor ", 0.45F, 0.52F, 0.1F, 0.04F, [this]() {}));

        gui_->ADD8COMPONENT(
            std::make_shared<GUI8BUTTON>("Quit ", 0.45F, 0.6F, 0.1F, 0.04F,
                                         [this]() { _<ENGINE>().STOP(); }));
    }

    void
    MAIN8MENU8SCENE::ON8ENTER8DERIVED() {
        _<GUI8TEXT8CONSOLE>().PRINT8LINE("Starting game.");

        _<GUI8TEXT8CONSOLE>().SET8Y8POSITION(
            1.0F - _<GUI8TEXT8CONSOLE>().size_.height);
    }

    void
    MAIN8MENU8SCENE::RENDER8BEFORE8GUI8DERIVED() {
        _<IMAGE8RENDERER>().DRAW8IMAGE("DefaultSceneBackground", 0.0F, 0.0F,
                                       1.0F, 1.0F);
        _<IMAGE8RENDERER>().DRAW8IMAGE8AUTOSIZE("ForradiaLogo", 0.35F, 0.2F,
                                                0.3F);
    }

    void
    MAIN8MENU8SCENE::ON8KEY8DOWN8DERIVED(SDL_Keycode key) {
    }

    void
    MAIN8MENU8SCENE::ON8MOUSE8DOWN8DERIVED(Uint8 button) {
    }
}