// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "I_SCENE.HPP"
#include "CORE/GUI8CORE/GUI.HPP"

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
    gui_->UPDATE();

    UpdateDerived();
}

void IScene::Render()
{
    RenderBeforeGUIDerived();

    gui_->RENDER();

    RenderAfterGUIDerived();
}

void IScene::OnKeyDown(SDL_Keycode key)
{
    if (gui_->ON8KEY8DOWN(key))
    {
        return;
    }

    OnKeyDownDerived(key);
}

void IScene::OnKeyUp(SDL_Keycode key)
{
    if (gui_->ON8KEY8UP(key))
    {
        return;
    }

    OnKeyUpDerived(key);
}

void IScene::OnMouseDown(Uint8 button)
{
    if (gui_->ON8MOUSE8DOWN(button))
    {
        return;
    }

    OnMouseDownDerived(button);
}

void IScene::OnMouseUp(Uint8 button, int clickSpeed)
{
    if (gui_->ON8MOUSE8UP(button, clickSpeed))
    {
        return;
    }

    OnMouseUpDerived(button, clickSpeed);
}