//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "KEYBOARD_MOVEMENT.HPP"
#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"

namespace FORRADIA8GAME
{
    void
    KeyboardMovement::Update()
    {
        auto wPressed{pressedKeys_.contains(SDLK_w)};
        auto sPressed{pressedKeys_.contains(SDLK_s)};
        auto aPressed{pressedKeys_.contains(SDLK_a)};
        auto qPressed{pressedKeys_.contains(SDLK_q)};

        auto now{NOW()};

        if (now > _<PLAYER>().ticksLastMovement_ +
                      INVERT8SPEED(_<PLAYER>().movementSpeed_) &&
            (wPressed || sPressed || aPressed || qPressed))
        {

            _<PLAYER>().destination_ = {-1, -1};

            if (wPressed)
            {
                if (pressedKeys_.contains(SDLK_LCTRL) ||
                    pressedKeys_.contains(SDLK_RCTRL))
                {
                    _<PLAYER>().TURN8NORTH();
                }
                else
                {
                    _<PLAYER>().TURN8NORTH();
                    _<PLAYER>().MOVE8NORTH();
                }
            }
            else if (sPressed)
            {
                if (pressedKeys_.contains(SDLK_LCTRL) ||
                    pressedKeys_.contains(SDLK_RCTRL))
                {
                    _<PLAYER>().TURN8EAST();
                }
                else
                {
                    _<PLAYER>().TURN8EAST();
                    _<PLAYER>().MOVE8EAST();
                }
            }
            else if (aPressed)
            {
                if (pressedKeys_.contains(SDLK_LCTRL) ||
                    pressedKeys_.contains(SDLK_RCTRL))
                {
                    _<PLAYER>().TURN8SOUTH();
                }
                else
                {
                    _<PLAYER>().TURN8SOUTH();
                    _<PLAYER>().MOVE8SOUTH();
                }
            }
            else if (qPressed)
            {
                if (pressedKeys_.contains(SDLK_LCTRL) ||
                    pressedKeys_.contains(SDLK_RCTRL))
                {
                    _<PLAYER>().TURN8WEST();
                }
                else
                {
                    _<PLAYER>().TURN8WEST();
                    _<PLAYER>().MOVE8WEST();
                }
            }

            _<PLAYER>().ticksLastMovement_ =
                now + rand() % 3 * (INVERT8SPEED(_<PLAYER>().movementSpeed_));
        }
    }

    void
    KeyboardMovement::OnKeyDown(SDL_Keycode key)
    {
        pressedKeys_.insert(key);
    }

    void
    KeyboardMovement::OnKeyUp(SDL_Keycode key)
    {
        pressedKeys_.erase(key);
    }
}