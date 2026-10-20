//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "MAIN_MENU_SCENE.HPP"
#include "CORE/ENGINE/ENGINE.HPP"
#include "CORE/GUI8CORE/GUI.HPP"
#include "CORE/GUI8CORE/GUI8BUTTON.HPP"
#include "CORE/GUI8CORE/GUI8PANEL.HPP"
#include "CORE/GUI8CORE/GUI8TEXT8CONSOLE.HPP"
#include "CORE/RENDERING/IMAGES/IMAGE8RENDERER.HPP"
#include "CORE/SCENES8CORE/SCENE8MANAGER.HPP"

void
MainMenuScene::INITIALIZE8DERIVED()
{
    gui_->ADD8COMPONENT(GET8SINGLETON8PTR<GUI8TEXT8CONSOLE>());

    gui_->ADD8COMPONENT(std::make_shared<GUI8PANEL>(0.4f, 0.4f, 0.2f, 0.2f));

    gui_->ADD8COMPONENT(std::make_shared<GUI8BUTTON>(
        "Play", 0.45f, 0.44f, 0.1f, 0.04f,
        [this]() { _<SCENE8MANAGER>().GO8TO8SCENE("WorldGenerationScene"); }));

    gui_->ADD8COMPONENT(std::make_shared<GUI8BUTTON>(
        "Quit ", 0.45f, 0.52f, 0.1f, 0.04f, [this]() { _<ENGINE>().STOP(); }));
}

void
MainMenuScene::ON8ENTER8DERIVED()
{
    _<GUI8TEXT8CONSOLE>().PRINT8LINE("Starting game.");

    _<GUI8TEXT8CONSOLE>().SET8Y8POSITION(1.0f -
                                         _<GUI8TEXT8CONSOLE>().size_.height);
}

void
MainMenuScene::RENDER8BEFORE8GUI8DERIVED()
{
    _<IMAGE8RENDERER>().DRAW8IMAGE("DefaultSceneBackground", 0.0f, 0.0f, 1.0f,
                                   1.0f);

    _<IMAGE8RENDERER>().DRAW8IMAGE("ForradiaLogo", 0.3f, 0.2f, 0.4f, 0.15f);
}

void
MainMenuScene::ON8KEY8DOWN8DERIVED(SDL_Keycode key)
{
}

void
MainMenuScene::ON8MOUSE8DOWN8DERIVED(Uint8 button)
{
}