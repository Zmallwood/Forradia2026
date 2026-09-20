/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "MouseMovement.hpp"
#include "Core/Configuration/GameProperties.hpp"
#include "Core/CoreGameObjects/Player.hpp"
#include "TileHovering.hpp"

namespace Forradia
{
    void MouseMovement::Update()
    {
        auto destination{_<Player>().destination_};

        if (destination.x != -1 && destination.y != -1)
        {
            auto now{Ticks()};

            if (now > _<Player>().ticksLastMovement_ +
                          InvertSpeed(_<Player>().movementSpeed_))
            {
                auto dx{destination.x - _<Player>().position_.x};
                auto dy{destination.y - _<Player>().position_.y};

                auto abs_dx{std::abs(dx)};
                auto abs_dy{std::abs(dy)};

                if (dx == 0 && dy == 0)
                {
                    _<Player>().destination_ = {-1, -1};

                    return;
                }

                if (dy < 0 && abs_dy > abs_dx)
                {
                    if (ctrl_key_down_)
                    {
                        _<Player>().TurnNorth();
                    }
                    else
                    {
                        _<Player>().MoveNorth();
                    }
                }
                else if (dy > 0 && abs_dy > abs_dx)
                {
                    if (ctrl_key_down_)
                    {
                        _<Player>().TurnSouth();
                    }
                    else
                    {
                        _<Player>().MoveSouth();
                    }
                }
                else if (dx < 0 && abs_dx > abs_dy)
                {
                    if (ctrl_key_down_)
                    {
                        _<Player>().TurnWest();
                    }
                    else
                    {
                        _<Player>().MoveWest();
                    }
                }
                else if (dx > 0 && abs_dx > abs_dy)
                {
                    if (ctrl_key_down_)
                    {
                        _<Player>().TurnEast();
                    }
                    else
                    {
                        _<Player>().MoveEast();
                    }
                }
                else if (dy < 0)
                {
                    if (ctrl_key_down_)
                    {
                        _<Player>().TurnNorth();
                    }
                    else
                    {
                        _<Player>().MoveNorth();
                    }
                }
                else if (dy > 0)
                {
                    if (ctrl_key_down_)
                    {
                        _<Player>().TurnSouth();
                    }
                    else
                    {
                        _<Player>().MoveSouth();
                    }
                }
                else if (dx < 0)
                {
                    if (ctrl_key_down_)
                    {
                        _<Player>().TurnWest();
                    }
                    else
                    {
                        _<Player>().MoveWest();
                    }
                }
                else if (dx > 0)
                {
                    if (ctrl_key_down_)
                    {
                        _<Player>().TurnEast();
                    }
                    else
                    {
                        _<Player>().MoveEast();
                    }
                }

                _<Player>().ticksLastMovement_ = now;
            }
        }
    }

    void MouseMovement::OnKeyDown(SDL_Keycode key)
    {
        if (key == SDLK_LCTRL || key == SDLK_RCTRL)
        {
            ctrl_key_down_ = true;
        }
    }

    void MouseMovement::OnKeyUp(SDL_Keycode key)
    {
        if (key == SDLK_LCTRL || key == SDLK_RCTRL)
        {
            ctrl_key_down_ = false;
        }
    }

    void MouseMovement::OnMouseDown(Uint8 button)
    {
        auto view_width{GameProperties::k_viewWidth_};

        auto mouse_position{GetMousePosition()};

        if (mouse_position.x > view_width)
        {
            return;
        }

        if (button == SDL_BUTTON_LEFT)
        {
            _<Player>().destination_ = _<TileHovering>().hovered_coordinate_;
        }
    }
}