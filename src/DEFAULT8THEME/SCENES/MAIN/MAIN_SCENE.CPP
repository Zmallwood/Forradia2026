//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "MAIN_SCENE.HPP"
#include "SUB/WORLD8VIEW/WORLD8VIEW.HPP"
#include "CORE/GUI8CORE/GUI.HPP"
#include "CORE/GUI8CORE/GUI8BUTTON.HPP"
#include "CORE/GUI8CORE/GUI8TEXT8CONSOLE.HPP"
#include "CUSTOM8GUI/ACTION8MENU/GUI8ACTION8MENU.HPP"
#include "CUSTOM8GUI/GUI8EQUIPMENT8WINDOW.HPP"
#include "CUSTOM8GUI/GUI8EXPERIENCE8METER.HPP"
#include "CUSTOM8GUI/GUI8INVENTORY8WINDOW.HPP"
#include "CUSTOM8GUI/GUI8STATUS8PANEL.HPP"
#include "SUB/CREATURES8COMBAT8TO8PLAYER.HPP"
#include "SUB/CREATURES_MOVEMENT.HPP"
#include "SUB/CREATURE8RESPAWNER.HPP"
#include "SUB/FIRST8PERSON8VIEW/FIRST8PERSON8VIEW.HPP"
#include "SUB/FIRST8PERSON8HOVERING.HPP"
#include "SUB/KEYBOARD8HOTKEYS.HPP"
#include "SUB/KEYBOARD_MOVEMENT.HPP"
#include "SUB/MOUSE_MOVEMENT.HPP"
#include "SUB/OBJECT8IMPACT.HPP"
#include "SUB/OBJECT8MOVING.HPP"
#include "SUB/PLAYER_COMBAT_TO_OTHERS.HPP"
#include "SUB/TILE_HOVERING.HPP"

namespace FORRADIA8GAME
{
    void
    MainScene::INITIALIZE8DERIVED()
    {
        gui_->ADD8COMPONENT(GET8SINGLETON8PTR<GUI8TEXT8CONSOLE>());

        gui_->ADD8COMPONENT(GET8SINGLETON8PTR<GUI8EXPERIENCE8METER>());

        gui_->ADD8COMPONENT(std::make_shared<GUI8BUTTON>(
            "", 0.94f, 0.08f, 0.05f, CONVERT8WIDTH8TO8HEIGHT(0.05f),
            [this]() { _<GUI8INVENTORY8WINDOW>().TOGGLE8VISIBILITY(); },
            "GUIButtonInventoryBackground",
            "GUIButtonInventoryHoveredBackground"));

        gui_->ADD8COMPONENT(std::make_shared<GUI8BUTTON>(
            "", 0.94f, 0.18f, 0.05f, CONVERT8WIDTH8TO8HEIGHT(0.05f),
            [this]() { _<GUI8EQUIPMENT8WINDOW>().TOGGLE8VISIBILITY(); },
            "GUIButtonEquipmentBackground",
            "GUIButtonEquipmentHoveredBackground"));

        gui_->ADD8COMPONENT(std::make_shared<GUI8STATUS8PANEL>());

        gui_->ADD8COMPONENT(GET8SINGLETON8PTR<GUI8INVENTORY8WINDOW>());

        gui_->ADD8COMPONENT(GET8SINGLETON8PTR<GUI8EQUIPMENT8WINDOW>());
    }

    void
    MainScene::ON8ENTER8DERIVED()
    {
        _<GUI8TEXT8CONSOLE>().SET8Y8POSITION(
            1.0f - _<GUI8TEXT8CONSOLE>().size_.height -
            _<GUI8EXPERIENCE8METER>().size_.height);

        _<GUI8TEXT8CONSOLE>().PRINT8LINE("You have entered the world.");
    }

    void
    MainScene::UPDATE8DERIVED()
    {
        _<CreaturesMovement>().Update();

        _<KeyboardMovement>().Update();

        _<MouseMovement>().Update();

        _<TileHovering>().Update();

        _<FIRST8PERSON8HOVERING>().UPDATE();

        _<CREATURE8RESPAWNER>().UPDATE();

        _<CREATURES8COMBAT8TO8PLAYER>().UPDATE();

        _<FIRST8PERSON8VIEW>().UPDATE();
    }

    void
    MainScene::RENDER8BEFORE8GUI8DERIVED()
    {
        _<WORLD8VIEW>().RENDER();

        _<FIRST8PERSON8VIEW>().RENDER();

        _<FIRST8PERSON8HOVERING>().RENDER();

        _<GUI8ACTION8MENU>().Render();
    }

    void
    MainScene::RENDER8AFTER8GUI8DERIVED()
    {
        _<OBJECT8MOVING>().RENDER();
    }

    void
    MainScene::ON8KEY8DOWN8DERIVED(SDL_Keycode key)
    {
        _<KeyboardMovement>().OnKeyDown(key);

        _<MouseMovement>().OnKeyDown(key);

        _<KEYBOARD8HOTKEYS>().ON8KEY8DOWN(key);
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

        _<OBJECT8IMPACT>().ON8MOUSE8DOWN(button);

        _<OBJECT8MOVING>().ON8MOUSE8DOWN(button);

        _<GUI8ACTION8MENU>().OnMouseDown(button);
    }

    void
    MainScene::ON8MOUSE8UP8DERIVED(Uint8 button, int clickSpeed)
    {
        _<OBJECT8MOVING>().ON8MOUSE8UP(button, clickSpeed);
    }
}