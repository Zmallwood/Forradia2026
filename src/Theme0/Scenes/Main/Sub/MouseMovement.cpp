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
            auto now{Now()};

            if (now > _<Player>().ticksLastMovement_ +
                          InvertSpeed(_<Player>().movementSpeed_))
            {
                auto dx{destination.x - _<Player>().position_.x};
                auto dy{destination.y - _<Player>().position_.y};

                auto absDx{std::abs(dx)};
                auto absDy{std::abs(dy)};

                if (dx == 0 && dy == 0)
                {
                    _<Player>().destination_ = {-1, -1};

                    return;
                }

                if (dy < 0 && absDy > absDx)
                {
                    if (ctrlKeyDown_)
                    {
                        _<Player>().TurnNorth();
                    }
                    else
                    {
                        _<Player>().MoveNorth();
                    }
                }
                else if (dy > 0 && absDy > absDx)
                {
                    if (ctrlKeyDown_)
                    {
                        _<Player>().TurnSouth();
                    }
                    else
                    {
                        _<Player>().MoveSouth();
                    }
                }
                else if (dx < 0 && absDx > absDy)
                {
                    if (ctrlKeyDown_)
                    {
                        _<Player>().TurnWest();
                    }
                    else
                    {
                        _<Player>().MoveWest();
                    }
                }
                else if (dx > 0 && absDx > absDy)
                {
                    if (ctrlKeyDown_)
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
                    if (ctrlKeyDown_)
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
                    if (ctrlKeyDown_)
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
                    if (ctrlKeyDown_)
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
                    if (ctrlKeyDown_)
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
            ctrlKeyDown_ = true;
        }
    }

    void MouseMovement::OnKeyUp(SDL_Keycode key)
    {
        if (key == SDLK_LCTRL || key == SDLK_RCTRL)
        {
            ctrlKeyDown_ = false;
        }
    }

    void MouseMovement::OnMouseDown(Uint8 button)
    {
        auto viewWidth{GameProperties::k_viewWidth_};

        auto mousePosition{GetMousePosition()};

        if (mousePosition.x > viewWidth)
        {
            return;
        }

        if (button == SDL_BUTTON_LEFT)
        {
            _<Player>().destination_ = _<TileHovering>().hoveredCoordinate_;
        }
    }
}