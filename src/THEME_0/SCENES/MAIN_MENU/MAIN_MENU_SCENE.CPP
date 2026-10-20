// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "MAIN_MENU_SCENE.HPP"
#include "CORE/ENGINE/ENGINE.HPP"
#include "CORE/GUI_CORE/GUI.HPP"
#include "CORE/GUI_CORE/GUI_BUTTON.HPP"
#include "CORE/GUI_CORE/GUI_PANEL.HPP"
#include "CORE/GUI_CORE/GUI_TEXT_CONSOLE.HPP"
#include "CORE/RENDERING/IMAGES/IMAGE_RENDERER.HPP"
#include "CORE/SCENES_CORE/SCENE_MANAGER.HPP"

void MainMenuScene::InitializeDerived()
{
    gui_->AddComponent(GET8SINGLETON8PTR<GUITextConsole>());

    gui_->AddComponent(std::make_shared<GUIPanel>(0.4f, 0.4f, 0.2f, 0.2f));

    gui_->AddComponent(std::make_shared<GUIButton>(
        "Play", 0.45f, 0.44f, 0.1f, 0.04f,
        [this]() { _<SceneManager>().GoToScene("WorldGenerationScene"); }));

    gui_->AddComponent(std::make_shared<GUIButton>(
        "Quit ", 0.45f, 0.52f, 0.1f, 0.04f, [this]() { _<ENGINE>().STOP(); }));
}

void MainMenuScene::OnEnterDerived()
{
    _<GUITextConsole>().PrintLine("Starting game.");

    _<GUITextConsole>().SetYPosition(1.0f - _<GUITextConsole>().size_.height);
}

void MainMenuScene::RenderBeforeGUIDerived()
{
    _<ImageRenderer>().DrawImage("DefaultSceneBackground", 0.0f, 0.0f, 1.0f,
                                 1.0f);

    _<ImageRenderer>().DrawImage("ForradiaLogo", 0.3f, 0.2f, 0.4f, 0.15f);
}

void MainMenuScene::OnKeyDownDerived(SDL_Keycode key)
{
}

void MainMenuScene::OnMouseDownDerived(Uint8 button)
{
}