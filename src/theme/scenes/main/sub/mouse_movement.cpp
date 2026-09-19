#include "mouse_movement.hpp"
#include "core/core_game_objects/player.hpp"
#include "tile_hovering.hpp"

namespace darktale
{
    void mouse_movement::update()
    {
        auto destination{_<player>().destination_};

        if (destination.x != -1 && destination.y != -1)
        {
            auto now{ticks()};

            if (now > _<player>().ticks_last_movement_ +
                          invert_speed(_<player>().movement_speed_))
            {
                auto dx{destination.x - _<player>().position_.x};
                auto dy{destination.y - _<player>().position_.y};

                auto abs_dx{std::abs(dx)};
                auto abs_dy{std::abs(dy)};

                if (dx == 0 && dy == 0)
                {
                    _<player>().destination_ = {-1, -1};

                    return;
                }

                if (dy < 0 && abs_dy > abs_dx)
                {
                    if (ctrl_key_down_)
                    {
                        _<player>().turn_north();
                    }
                    else
                    {
                        _<player>().move_north();
                    }
                }
                else if (dy > 0 && abs_dy > abs_dx)
                {
                    if (ctrl_key_down_)
                    {
                        _<player>().turn_south();
                    }
                    else
                    {
                        _<player>().move_south();
                    }
                }
                else if (dx < 0 && abs_dx > abs_dy)
                {
                    if (ctrl_key_down_)
                    {
                        _<player>().turn_west();
                    }
                    else
                    {
                        _<player>().move_west();
                    }
                }
                else if (dx > 0 && abs_dx > abs_dy)
                {
                    if (ctrl_key_down_)
                    {
                        _<player>().turn_east();
                    }
                    else
                    {
                        _<player>().move_east();
                    }
                }
                else if (dy < 0)
                {
                    if (ctrl_key_down_)
                    {
                        _<player>().turn_north();
                    }
                    else
                    {
                        _<player>().move_north();
                    }
                }
                else if (dy > 0)
                {
                    if (ctrl_key_down_)
                    {
                        _<player>().turn_south();
                    }
                    else
                    {
                        _<player>().move_south();
                    }
                }
                else if (dx < 0)
                {
                    if (ctrl_key_down_)
                    {
                        _<player>().turn_west();
                    }
                    else
                    {
                        _<player>().move_west();
                    }
                }
                else if (dx > 0)
                {
                    if (ctrl_key_down_)
                    {
                        _<player>().turn_east();
                    }
                    else
                    {
                        _<player>().move_east();
                    }
                }

                _<player>().ticks_last_movement_ = now;
            }
        }
    }

    void mouse_movement::on_key_down(SDL_Keycode key)
    {
        if (key == SDLK_LCTRL || key == SDLK_RCTRL)
        {
            ctrl_key_down_ = true;
        }
    }

    void mouse_movement::on_key_up(SDL_Keycode key)
    {
        if (key == SDLK_LCTRL || key == SDLK_RCTRL)
        {
            ctrl_key_down_ = false;
        }
    }

    void mouse_movement::on_mouse_down(Uint8 button)
    {
        if (button == SDL_BUTTON_LEFT)
        {
            _<player>().destination_ = _<tile_hovering>().hovered_coordinate_;
        }
    }
}