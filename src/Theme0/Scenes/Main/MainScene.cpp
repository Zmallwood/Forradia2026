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
#include "CustomGUI/ActionMenu/GUIActionMenu.hpp"
#include "CustomGUI/GUIEquipmentWindow.hpp"
#include "CustomGUI/GUIExperienceMeter.hpp"
#include "CustomGUI/GUIInventoryWindow.hpp"
#include "CustomGUI/GUIStatusPanel.hpp"
#include "Sub/CreatureRespawner.hpp"
#include "Sub/CreaturesCombatToPlayer.hpp"
#include "Sub/CreaturesMovement.hpp"
#include "Sub/FirstPersonHovering.hpp"
#include "Sub/FirstPersonView/FirstPersonView.hpp"
#include "Sub/KeyboardHotkeys.hpp"
#include "Sub/KeyboardMovement.hpp"
#include "Sub/MouseMovement.hpp"
#include "Sub/ObjectImpact.hpp"
#include "Sub/ObjectMoving.hpp"
#include "Sub/PlayerCombatToOthers.hpp"
#include "Sub/TileHovering.hpp"
#include "Sub/WorldView/WorldView.hpp"

void MainScene::InitializeDerived()
{
    gui_->AddComponent(GetSingletonPtr<GUITextConsole>());

    gui_->AddComponent(GetSingletonPtr<GUIExperienceMeter>());

    gui_->AddComponent(std::make_shared<GUIButton>(
        "", 0.94f, 0.08f, 0.05f, ConvertWidthToHeight(0.05f),
        [this]() { _<GUIInventoryWindow>().ToggleVisibility(); },
        "GUIButtonInventoryBackground", "GUIButtonInventoryHoveredBackground"));

    gui_->AddComponent(std::make_shared<GUIButton>(
        "", 0.94f, 0.18f, 0.05f, ConvertWidthToHeight(0.05f),
        [this]() { _<GUIEquipmentWindow>().ToggleVisibility(); },
        "GUIButtonEquipmentBackground", "GUIButtonEquipmentHoveredBackground"));

    gui_->AddComponent(std::make_shared<GUIStatusPanel>());

    gui_->AddComponent(GetSingletonPtr<GUIInventoryWindow>());

    gui_->AddComponent(GetSingletonPtr<GUIEquipmentWindow>());
}

void MainScene::OnEnterDerived()
{
    _<GUITextConsole>().SetYPosition(1.0f - _<GUITextConsole>().size_.height -
                                     _<GUIExperienceMeter>().size_.height);

    _<GUITextConsole>().PrintLine("You have entered the world.");
}

void MainScene::UpdateDerived()
{
    _<CreaturesMovement>().Update();

    _<KeyboardMovement>().Update();

    _<MouseMovement>().Update();

    _<TileHovering>().Update();

    _<FirstPersonHovering>().Update();

    _<CreatureRespawner>().Update();

    _<CreaturesCombatToPlayer>().Update();

    _<FirstPersonView>().Update();
}

void MainScene::RenderBeforeGUIDerived()
{
    _<WorldView>().Render();

    _<FirstPersonView>().Render();

    _<FirstPersonHovering>().Render();

    _<GUIActionMenu>().Render();
}

void MainScene::RenderAfterGUIDerived()
{
    _<ObjectMoving>().Render();
}

void MainScene::OnKeyDownDerived(SDL_Keycode key)
{
    _<KeyboardMovement>().OnKeyDown(key);

    _<MouseMovement>().OnKeyDown(key);

    _<KeyboardHotkeys>().OnKeyDown(key);
}

void MainScene::OnKeyUpDerived(SDL_Keycode key)
{
    _<KeyboardMovement>().OnKeyUp(key);

    _<MouseMovement>().OnKeyUp(key);
}

void MainScene::OnMouseDownDerived(Uint8 button)
{
    _<PlayerCombatToOthers>().OnMouseDown(button);

    _<MouseMovement>().OnMouseDown(button);

    _<ObjectImpact>().OnMouseDown(button);

    _<ObjectMoving>().OnMouseDown(button);

    _<GUIActionMenu>().OnMouseDown(button);
}

void MainScene::OnMouseUpDerived(Uint8 button, int clickSpeed)
{
    _<ObjectMoving>().OnMouseUp(button, clickSpeed);
}