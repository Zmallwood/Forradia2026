/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "MainMenuScene.hpp"
#include "Core/Engine/Engine.hpp"
#include "Core/GUICore/GUI.hpp"
#include "Core/GUICore/GUIButton.hpp"
#include "Core/GUICore/GUIPanel.hpp"
#include "Core/Rendering/Images/ImageRenderer.hpp"
#include "Core/ScenesCore/SceneManager.hpp"

namespace Forradia
{
    void MainMenuScene::InitializeDerived()
    {
        gui_->AddComponent(std::make_shared<GUIPanel>(0.4f, 0.4f, 0.2f, 0.2f));

        gui_->AddComponent(std::make_shared<GUIButton>(
            "Play", 0.45f, 0.44f, 0.1f, 0.04f,
            [this]() { _<SceneManager>().GoToScene("WorldGenerationScene"); }));

        gui_->AddComponent(
            std::make_shared<GUIButton>("Quit ", 0.45f, 0.52f, 0.1f, 0.04f,
                                        [this]() { _<Engine>().Stop(); }));
    }

    void MainMenuScene::RenderDerived()
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
}