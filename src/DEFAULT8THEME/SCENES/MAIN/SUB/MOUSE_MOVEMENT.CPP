//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "MOUSE_MOVEMENT.HPP"
#include "CORE/CONFIGURATION/GAME8PROPERTIES.HPP"
#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"
#include "TILE_HOVERING.HPP"

void
MouseMovement::Update()
{
    auto destination{_<PLAYER>().destination_};

    POINT playerPosition{static_cast<int>(_<PLAYER>().position_.x),
                         static_cast<int>(_<PLAYER>().position_.y)};

    if (destination.x != -1 && destination.y != -1)
    {
        auto now{NOW()};

        if (now > _<PLAYER>().ticksLastMovement_ +
                      INVERT8SPEED(_<PLAYER>().movementSpeed_))
        {
            auto dx{destination.x - playerPosition.x};
            auto dy{destination.y - playerPosition.y};

            auto absDx{std::abs(dx)};
            auto absDy{std::abs(dy)};

            if (dx == 0 && dy == 0)
            {
                _<PLAYER>().destination_ = {-1, -1};

                return;
            }

            if (dy < 0 && absDy > absDx)
            {
                if (ctrlKeyDown_)
                {
                    _<PLAYER>().TURN8NORTH();
                }
                else
                {
                    _<PLAYER>().MOVE8NORTH();
                }
            }
            else if (dy > 0 && absDy > absDx)
            {
                if (ctrlKeyDown_)
                {
                    _<PLAYER>().TURN8SOUTH();
                }
                else
                {
                    _<PLAYER>().MOVE8SOUTH();
                }
            }
            else if (dx < 0 && absDx > absDy)
            {
                if (ctrlKeyDown_)
                {
                    _<PLAYER>().TURN8WEST();
                }
                else
                {
                    _<PLAYER>().MOVE8WEST();
                }
            }
            else if (dx > 0 && absDx > absDy)
            {
                if (ctrlKeyDown_)
                {
                    _<PLAYER>().TURN8EAST();
                }
                else
                {
                    _<PLAYER>().MOVE8EAST();
                }
            }
            else if (dy < 0)
            {
                if (ctrlKeyDown_)
                {
                    _<PLAYER>().TURN8NORTH();
                }
                else
                {
                    _<PLAYER>().MOVE8NORTH();
                }
            }
            else if (dy > 0)
            {
                if (ctrlKeyDown_)
                {
                    _<PLAYER>().TURN8SOUTH();
                }
                else
                {
                    _<PLAYER>().MOVE8SOUTH();
                }
            }
            else if (dx < 0)
            {
                if (ctrlKeyDown_)
                {
                    _<PLAYER>().TURN8WEST();
                }
                else
                {
                    _<PLAYER>().MOVE8WEST();
                }
            }
            else if (dx > 0)
            {
                if (ctrlKeyDown_)
                {
                    _<PLAYER>().TURN8EAST();
                }
                else
                {
                    _<PLAYER>().MOVE8EAST();
                }
            }

            _<PLAYER>().ticksLastMovement_ =
                now + rand() % 3 * (INVERT8SPEED(_<PLAYER>().movementSpeed_));
        }
    }
}

void
MouseMovement::OnKeyDown(SDL_Keycode key)
{
    if (key == SDLK_LCTRL || key == SDLK_RCTRL)
    {
        ctrlKeyDown_ = true;
    }
}

void
MouseMovement::OnKeyUp(SDL_Keycode key)
{
    if (key == SDLK_LCTRL || key == SDLK_RCTRL)
    {
        ctrlKeyDown_ = false;
    }
}

void
MouseMovement::OnMouseDown(Uint8 button)
{
    auto viewWidth{GAME8PROPERTIES::kViewWidth_};

    auto mousePosition{GET8MOUSE8POSITION()};

    if (mousePosition.x > viewWidth)
    {
        return;
    }

    if (button == SDL_BUTTON_LEFT)
    {
        _<PLAYER>().destination_ = _<TileHovering>().hoveredCoordinate_;
    }
}