/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "main_scene.hpp"
#include "Sub/FirstPersonView/first_person_view.hpp"
#include "Sub/WorldView/world_view.hpp"
#include "Sub/keyboard_movement.hpp"
#include "Sub/mouse_movement.hpp"
#include "Sub/object_hovering.hpp"
#include "Sub/tile_hovering.hpp"


namespace Forradia
{
    void main_scene::update_derived()
    {
        _<keyboard_movement>().update();

        _<mouse_movement>().update();

        _<tile_hovering>().update();

        _<object_hovering>().update();
    }

    void main_scene::render_derived()
    {
        _<world_view>().render();

        _<first_person_view>().render();

        _<object_hovering>().render();
    }

    void main_scene::on_key_down(SDL_Keycode key)
    {
        _<keyboard_movement>().on_key_down(key);

        _<mouse_movement>().on_key_down(key);
    }

    void main_scene::on_key_up(SDL_Keycode key)
    {
        _<keyboard_movement>().on_key_up(key);

        _<mouse_movement>().on_key_up(key);
    }

    void main_scene::on_mouse_down(Uint8 button)
    {
        _<mouse_movement>().on_mouse_down(button);
    }
}