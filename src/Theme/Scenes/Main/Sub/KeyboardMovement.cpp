/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "KeyboardMovement.hpp"
#include "Core/CoreGameObjects/Player.hpp"

namespace Forradia
{
    void KeyboardMovement::Update()
    {
        auto w_pressed{pressed_keys_.contains(SDLK_w)};
        auto s_pressed{pressed_keys_.contains(SDLK_s)};
        auto a_pressed{pressed_keys_.contains(SDLK_a)};
        auto q_pressed{pressed_keys_.contains(SDLK_q)};

        auto now{Ticks()};

        if (now > _<Player>().ticksLastMovement_ +
                      InvertSpeed(_<Player>().movementSpeed_) &&
            (w_pressed || s_pressed || a_pressed || q_pressed))
        {

            _<Player>().destination_ = {-1, -1};

            if (w_pressed)
            {
                if (pressed_keys_.contains(SDLK_LCTRL) ||
                    pressed_keys_.contains(SDLK_RCTRL))
                {
                    _<Player>().TurnNorth();
                }
                else
                {
                    _<Player>().MoveNorth();
                }
            }
            else if (s_pressed)
            {
                if (pressed_keys_.contains(SDLK_LCTRL) ||
                    pressed_keys_.contains(SDLK_RCTRL))
                {
                    _<Player>().TurnEast();
                }
                else
                {
                    _<Player>().MoveEast();
                }
            }
            else if (a_pressed)
            {
                if (pressed_keys_.contains(SDLK_LCTRL) ||
                    pressed_keys_.contains(SDLK_RCTRL))
                {
                    _<Player>().TurnSouth();
                }
                else
                {
                    _<Player>().MoveSouth();
                }
            }
            else if (q_pressed)
            {
                if (pressed_keys_.contains(SDLK_LCTRL) ||
                    pressed_keys_.contains(SDLK_RCTRL))
                {
                    _<Player>().TurnWest();
                }
                else
                {
                    _<Player>().MoveWest();
                }
            }

            _<Player>().ticksLastMovement_ = now;
        }
    }

    void KeyboardMovement::OnKeyDown(SDL_Keycode key)
    {
        pressed_keys_.insert(key);
    }

    void KeyboardMovement::OnKeyUp(SDL_Keycode key)
    {
        pressed_keys_.erase(key);
    }
}