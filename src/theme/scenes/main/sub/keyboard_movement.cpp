#include "keyboard_movement.hpp"
#include "core/core_game_objects/player.hpp"

namespace darktale
{
    void keyboard_movement::update()
    {
        auto w_pressed{pressed_keys_.contains(SDLK_w)};
        auto s_pressed{pressed_keys_.contains(SDLK_s)};
        auto a_pressed{pressed_keys_.contains(SDLK_a)};
        auto q_pressed{pressed_keys_.contains(SDLK_q)};

        auto now{ticks()};

        if (now > _<player>().ticks_last_movement_ +
                      invert_speed(_<player>().movement_speed_) &&
            (w_pressed || s_pressed || a_pressed || q_pressed))
        {

            _<player>().destination_ = {-1, -1};

            if (w_pressed)
            {
                if (pressed_keys_.contains(SDLK_LCTRL) ||
                    pressed_keys_.contains(SDLK_RCTRL))
                {
                    _<player>().turn_north();
                }
                else
                {
                    _<player>().move_north();
                }
            }
            else if (s_pressed)
            {
                if (pressed_keys_.contains(SDLK_LCTRL) ||
                    pressed_keys_.contains(SDLK_RCTRL))
                {
                    _<player>().turn_east();
                }
                else
                {
                    _<player>().move_east();
                }
            }
            else if (a_pressed)
            {
                if (pressed_keys_.contains(SDLK_LCTRL) ||
                    pressed_keys_.contains(SDLK_RCTRL))
                {
                    _<player>().turn_south();
                }
                else
                {
                    _<player>().move_south();
                }
            }
            else if (q_pressed)
            {
                if (pressed_keys_.contains(SDLK_LCTRL) ||
                    pressed_keys_.contains(SDLK_RCTRL))
                {
                    _<player>().turn_west();
                }
                else
                {
                    _<player>().move_west();
                }
            }

            _<player>().ticks_last_movement_ = now;
        }
    }

    void keyboard_movement::on_key_down(SDL_Keycode key)
    {
        pressed_keys_.insert(key);
    }

    void keyboard_movement::on_key_up(SDL_Keycode key)
    {
        pressed_keys_.erase(key);
    }
}