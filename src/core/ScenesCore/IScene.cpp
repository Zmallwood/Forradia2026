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

    void IScene::OnEnter()
    {
        OnEnterDerived();
    }

    void IScene::Update()
    {
        gui_->Update();

        UpdateDerived();
    }

    void IScene::Render()
    {
        RenderBeforeGUIDerived();

        gui_->Render();

        RenderAfterGUIDerived();
    }

    void IScene::OnKeyDown(SDL_Keycode key)
    {
        if (gui_->OnKeyDown(key))
        {
            return;
        }

        OnKeyDownDerived(key);
    }

    void IScene::OnKeyUp(SDL_Keycode key)
    {
        if (gui_->OnKeyUp(key))
        {
            return;
        }

        OnKeyUpDerived(key);
    }

    void IScene::OnMouseDown(Uint8 button)
    {
        if (gui_->OnMouseDown(button))
        {
            return;
        }

        OnMouseDownDerived(button);
    }

    void IScene::OnMouseUp(Uint8 button, int clickSpeed)
    {
        if (gui_->OnMouseUp(button, clickSpeed))
        {
            return;
        }

        OnMouseUpDerived(button, clickSpeed);
    }
}