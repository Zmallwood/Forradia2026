// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "MAIN_SCENE.HPP"
#include "CORE/GUI_CORE/GUI.HPP"
#include "CORE/GUI_CORE/GUI_BUTTON.HPP"
#include "CORE/GUI_CORE/GUI_TEXT_CONSOLE.HPP"
#include "CUSTOM_GUI/ACTION_MENU/GUI_ACTION_MENU.HPP"
#include "CUSTOM_GUI/GUI_EQUIPMENT_WINDOW.HPP"
#include "CUSTOM_GUI/GUI_EXPERIENCE_METER.HPP"
#include "CUSTOM_GUI/GUI_INVENTORY_WINDOW.HPP"
#include "CUSTOM_GUI/GUI_STATUS_PANEL.HPP"
#include "SUB/CREATURE_RESPAWNER.HPP"
#include "SUB/CREATURES_COMBAT_TO_PLAYER.HPP"
#include "SUB/CREATURES_MOVEMENT.HPP"
#include "SUB/FIRST_PERSON_HOVERING.HPP"
#include "SUB/FIRST_PERSON_VIEW/FIRST_PERSON_VIEW.HPP"
#include "SUB/KEYBOARD_HOTKEYS.HPP"
#include "SUB/KEYBOARD_MOVEMENT.HPP"
#include "SUB/MOUSE_MOVEMENT.HPP"
#include "SUB/OBJECT_IMPACT.HPP"
#include "SUB/OBJECT_MOVING.HPP"
#include "SUB/PLAYER_COMBAT_TO_OTHERS.HPP"
#include "SUB/TILE_HOVERING.HPP"
#include "SUB/WORLD_VIEW/WORLD_VIEW.HPP"

void MainScene::InitializeDerived()
{
    gui_->AddComponent(GetSingletonPtr<GUITextConsole>());

    gui_->AddComponent(GetSingletonPtr<GUIExperienceMeter>());

    gui_->AddComponent(std::make_shared<GUIButton>(
        "", 0.94f, 0.08f, 0.05f, CONVERT_WIDTH_TO_HEIGHT(0.05f),
        [this]() { _<GUIInventoryWindow>().ToggleVisibility(); },
        "GUIButtonInventoryBackground", "GUIButtonInventoryHoveredBackground"));

    gui_->AddComponent(std::make_shared<GUIButton>(
        "", 0.94f, 0.18f, 0.05f, CONVERT_WIDTH_TO_HEIGHT(0.05f),
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