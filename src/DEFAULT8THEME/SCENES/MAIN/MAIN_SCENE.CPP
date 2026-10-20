// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CORE/GUI8CORE/GUI.HPP"
#include "CORE/GUI8CORE/GUI8BUTTON.HPP"
#include "CORE/GUI8CORE/GUI8TEXT8CONSOLE.HPP"
#include "CUSTOM8GUI/ACTION8MENU/GUI_ACTION_MENU.HPP"
#include "CUSTOM8GUI/GUI_EQUIPMENT_WINDOW.HPP"
#include "CUSTOM8GUI/GUI_EXPERIENCE_METER.HPP"
#include "CUSTOM8GUI/GUI_INVENTORY_WINDOW.HPP"
#include "CUSTOM8GUI/GUI_STATUS_PANEL.HPP"
#include "MAIN_SCENE.HPP"
#include "SUB/CREATURES_COMBAT_TO_PLAYER.HPP"
#include "SUB/CREATURES_MOVEMENT.HPP"
#include "SUB/CREATURE_RESPAWNER.HPP"
#include "SUB/FIRST8PERSON8VIEW/FIRST_PERSON_VIEW.HPP"
#include "SUB/FIRST_PERSON_HOVERING.HPP"
#include "SUB/KEYBOARD_HOTKEYS.HPP"
#include "SUB/KEYBOARD_MOVEMENT.HPP"
#include "SUB/MOUSE_MOVEMENT.HPP"
#include "SUB/OBJECT_IMPACT.HPP"
#include "SUB/OBJECT_MOVING.HPP"
#include "SUB/PLAYER_COMBAT_TO_OTHERS.HPP"
#include "SUB/TILE_HOVERING.HPP"
#include "SUB/WORLD8VIEW/WORLD_VIEW.HPP"

void
MainScene::INITIALIZE8DERIVED()
{
    gui_->ADD8COMPONENT(GET8SINGLETON8PTR<GUI8TEXT8CONSOLE>());

    gui_->ADD8COMPONENT(GET8SINGLETON8PTR<GUIExperienceMeter>());

    gui_->ADD8COMPONENT(std::make_shared<GUI8BUTTON>(
        "", 0.94f, 0.08f, 0.05f, CONVERT8WIDTH8TO8HEIGHT(0.05f),
        [this]() { _<GUIInventoryWindow>().TOGGLE8VISIBILITY(); },
        "GUIButtonInventoryBackground", "GUIButtonInventoryHoveredBackground"));

    gui_->ADD8COMPONENT(std::make_shared<GUI8BUTTON>(
        "", 0.94f, 0.18f, 0.05f, CONVERT8WIDTH8TO8HEIGHT(0.05f),
        [this]() { _<GUIEquipmentWindow>().TOGGLE8VISIBILITY(); },
        "GUIButtonEquipmentBackground", "GUIButtonEquipmentHoveredBackground"));

    gui_->ADD8COMPONENT(std::make_shared<GUIStatusPanel>());

    gui_->ADD8COMPONENT(GET8SINGLETON8PTR<GUIInventoryWindow>());

    gui_->ADD8COMPONENT(GET8SINGLETON8PTR<GUIEquipmentWindow>());
}

void
MainScene::ON8ENTER8DERIVED()
{
    _<GUI8TEXT8CONSOLE>().SET8Y8POSITION(1.0f -
                                         _<GUI8TEXT8CONSOLE>().size_.height -
                                         _<GUIExperienceMeter>().size_.height);

    _<GUI8TEXT8CONSOLE>().PRINT8LINE("You have entered the world.");
}

void
MainScene::UPDATE8DERIVED()
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

void
MainScene::RENDER8BEFORE8GUI8DERIVED()
{
    _<WorldView>().Render();

    _<FirstPersonView>().Render();

    _<FirstPersonHovering>().Render();

    _<GUIActionMenu>().Render();
}

void
MainScene::RENDER8AFTER8GUI8DERIVED()
{
    _<ObjectMoving>().Render();
}

void
MainScene::ON8KEY8DOWN8DERIVED(SDL_Keycode key)
{
    _<KeyboardMovement>().OnKeyDown(key);

    _<MouseMovement>().OnKeyDown(key);

    _<KeyboardHotkeys>().OnKeyDown(key);
}

void
MainScene::ON8KEY8UP8DERIVED(SDL_Keycode key)
{
    _<KeyboardMovement>().OnKeyUp(key);

    _<MouseMovement>().OnKeyUp(key);
}

void
MainScene::ON8MOUSE8DOWN8DERIVED(Uint8 button)
{
    _<PlayerCombatToOthers>().OnMouseDown(button);

    _<MouseMovement>().OnMouseDown(button);

    _<ObjectImpact>().OnMouseDown(button);

    _<ObjectMoving>().OnMouseDown(button);

    _<GUIActionMenu>().OnMouseDown(button);
}

void
MainScene::ON8MOUSE8UP8DERIVED(Uint8 button, int clickSpeed)
{
    _<ObjectMoving>().OnMouseUp(button, clickSpeed);
}