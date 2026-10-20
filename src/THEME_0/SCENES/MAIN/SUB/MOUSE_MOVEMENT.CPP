// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CORE/CONFIGURATION/GAME8PROPERTIES.HPP"
#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"
#include "MOUSE_MOVEMENT.HPP"
#include "TILE_HOVERING.HPP"

void MouseMovement::Update()
{
    auto destination{_<Player>().destination_};

    POINT playerPosition{static_cast<int>(_<Player>().position_.x),
                         static_cast<int>(_<Player>().position_.y)};

    if (destination.x != -1 && destination.y != -1)
    {
        auto now{NOW()};

        if (now > _<Player>().ticksLastMovement_ +
                      INVERT8SPEED(_<Player>().movementSpeed_))
        {
            auto dx{destination.x - playerPosition.x};
            auto dy{destination.y - playerPosition.y};

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

            _<Player>().ticksLastMovement_ =
                now + rand() % 3 * (INVERT8SPEED(_<Player>().movementSpeed_));
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
    auto viewWidth{GAME8PROPERTIES::k_viewWidth_};

    auto mousePosition{GET8MOUSE8POSITION()};

    if (mousePosition.x > viewWidth)
    {
        return;
    }

    if (button == SDL_BUTTON_LEFT)
    {
        _<Player>().destination_ = _<TileHovering>().hoveredCoordinate_;
    }
}