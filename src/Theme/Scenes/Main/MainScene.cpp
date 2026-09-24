/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "MainScene.hpp"
#include "Sub/CreaturesMovement.hpp"
#include "Sub/FirstPersonView/FirstPersonView.hpp"
#include "Sub/KeyboardMovement.hpp"
#include "Sub/MouseMovement.hpp"
#include "Sub/ObjectHovering.hpp"
#include "Sub/TileHovering.hpp"
#include "Sub/WorldView/WorldView.hpp"


namespace Forradia
{
    void MainScene::UpdateDerived()
    {
        _<CreaturesMovement>().Update();

        _<KeyboardMovement>().Update();

        _<MouseMovement>().Update();

        _<TileHovering>().Update();

        _<ObjectHovering>().Update();
    }

    void MainScene::RenderDerived()
    {
        _<WorldView>().Render();

        _<FirstPersonView>().Render();

        _<ObjectHovering>().Render();
    }

    void MainScene::OnKeyDown(SDL_Keycode key)
    {
        _<KeyboardMovement>().OnKeyDown(key);

        _<MouseMovement>().OnKeyDown(key);
    }

    void MainScene::OnKeyUp(SDL_Keycode key)
    {
        _<KeyboardMovement>().OnKeyUp(key);

        _<MouseMovement>().OnKeyUp(key);
    }

    void MainScene::OnMouseDown(Uint8 button)
    {
        _<MouseMovement>().OnMouseDown(button);
    }
}