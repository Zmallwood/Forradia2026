#include "main_scene.hpp"
#include "sub/keyboard_movement.hpp"
#include "sub/mouse_movement.hpp"
#include "sub/tile_hovering.hpp"
#include "sub/views/first_person_view.hpp"
#include "sub/views/world_view.hpp"

namespace Forradia
{
    void main_scene::update_derived()
    {
        _<keyboard_movement>().update();

        _<mouse_movement>().update();

        _<tile_hovering>().update();
    }

    void main_scene::render_derived()
    {
        _<world_view>().render();

        _<first_person_view>().render();
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