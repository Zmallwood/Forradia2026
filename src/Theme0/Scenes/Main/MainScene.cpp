/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "MainScene.hpp"
#include "Core/GUICore/GUI.hpp"
#include "Core/GUICore/GUIButton.hpp"
#include "Core/GUICore/GUITextConsole.hpp"
#include "CustomGUI/GUIInventoryWindow.hpp"
#include "CustomGUI/GUIStatusPanel.hpp"
#include "Sub/Combat.hpp"
#include "Sub/CreaturesMovement.hpp"
#include "Sub/FirstPersonHovering.hpp"
#include "Sub/FirstPersonView/FirstPersonView.hpp"
#include "Sub/KeyboardMovement.hpp"
#include "Sub/MouseMovement.hpp"
#include "Sub/TileHovering.hpp"
#include "Sub/WorldView/WorldView.hpp"

namespace Forradia
{
    void MainScene::InitializeDerived()
    {
        gui_->AddComponent(GetSingletonPtr<GUITextConsole>());

        gui_->AddComponent(std::make_shared<GUIButton>(
            "", 0.94f, 0.08f, 0.05f, ConvertWidthToHeight(0.05f),
            [this]() { _<GUIInventoryWindow>().ToggleVisibility(); },
            "GUIButtonInventoryBackground",
            "GUIButtonInventoryHoveredBackground"));

        gui_->AddComponent(std::make_shared<GUIButton>(
            "", 0.94f, 0.18f, 0.05f, ConvertWidthToHeight(0.05f), [this]() {},
            "GUIButtonEquipmentBackground",
            "GUIButtonEquipmentHoveredBackground"));

        gui_->AddComponent(std::make_shared<GUIStatusPanel>());

        gui_->AddComponent(GetSingletonPtr<GUIInventoryWindow>());
    }

    void MainScene::OnEnterDerived()
    {
        _<GUITextConsole>().PrintLine("You have entered the world.");
    }

    void MainScene::UpdateDerived()
    {
        _<CreaturesMovement>().Update();

        _<KeyboardMovement>().Update();

        _<MouseMovement>().Update();

        _<TileHovering>().Update();

        _<FirstPersonHovering>().Update();
    }

    void MainScene::RenderDerived()
    {
        _<WorldView>().Render();

        _<FirstPersonView>().Render();

        _<FirstPersonHovering>().Render();
    }

    void MainScene::OnKeyDownDerived(SDL_Keycode key)
    {
        _<KeyboardMovement>().OnKeyDown(key);

        _<MouseMovement>().OnKeyDown(key);
    }

    void MainScene::OnKeyUpDerived(SDL_Keycode key)
    {
        _<KeyboardMovement>().OnKeyUp(key);

        _<MouseMovement>().OnKeyUp(key);
    }

    void MainScene::OnMouseDownDerived(Uint8 button)
    {
        _<Combat>().OnMouseDown(button);

        _<MouseMovement>().OnMouseDown(button);
    }
}