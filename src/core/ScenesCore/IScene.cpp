/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "IScene.hpp"
#include "Core/GUICore/GUI.hpp"

namespace Forradia
{
    IScene::IScene() : gui_(std::make_shared<GUI>())
    {
    }

    void IScene::Initialize()
    {
        InitializeDerived();
    }

    void IScene::Update()
    {
        gui_->Update();

        UpdateDerived();
    }

    void IScene::Render()
    {
        RenderDerived();

        gui_->Render();
    }

    void IScene::OnKeyDown(SDL_Keycode key)
    {
        gui_->OnKeyDown(key);
    }

    void IScene::OnKeyUp(SDL_Keycode key)
    {
        gui_->OnKeyUp(key);
    }

    void IScene::OnMouseDown(Uint8 button)
    {
        gui_->OnMouseDown(button);
    }

    void IScene::OnMouseUp(Uint8 button, int clickSpeed)
    {
        gui_->OnMouseUp(button, clickSpeed);
    }
}