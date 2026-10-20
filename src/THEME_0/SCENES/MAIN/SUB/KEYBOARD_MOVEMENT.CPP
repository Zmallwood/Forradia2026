// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"
#include "KEYBOARD_MOVEMENT.HPP"

void KeyboardMovement::Update()
{
    auto wPressed{pressedKeys_.contains(SDLK_w)};
    auto sPressed{pressedKeys_.contains(SDLK_s)};
    auto aPressed{pressedKeys_.contains(SDLK_a)};
    auto qPressed{pressedKeys_.contains(SDLK_q)};

    auto now{NOW()};

    if (now > _<Player>().ticksLastMovement_ +
                  INVERT8SPEED(_<Player>().movementSpeed_) &&
        (wPressed || sPressed || aPressed || qPressed))
    {

        _<Player>().destination_ = {-1, -1};

        if (wPressed)
        {
            if (pressedKeys_.contains(SDLK_LCTRL) ||
                pressedKeys_.contains(SDLK_RCTRL))
            {
                _<Player>().TurnNorth();
            }
            else
            {
                _<Player>().TurnNorth();
                _<Player>().MoveNorth();
            }
        }
        else if (sPressed)
        {
            if (pressedKeys_.contains(SDLK_LCTRL) ||
                pressedKeys_.contains(SDLK_RCTRL))
            {
                _<Player>().TurnEast();
            }
            else
            {
                _<Player>().TurnEast();
                _<Player>().MoveEast();
            }
        }
        else if (aPressed)
        {
            if (pressedKeys_.contains(SDLK_LCTRL) ||
                pressedKeys_.contains(SDLK_RCTRL))
            {
                _<Player>().TurnSouth();
            }
            else
            {
                _<Player>().TurnSouth();
                _<Player>().MoveSouth();
            }
        }
        else if (qPressed)
        {
            if (pressedKeys_.contains(SDLK_LCTRL) ||
                pressedKeys_.contains(SDLK_RCTRL))
            {
                _<Player>().TurnWest();
            }
            else
            {
                _<Player>().TurnWest();
                _<Player>().MoveWest();
            }
        }

        _<Player>().ticksLastMovement_ =
            now + rand() % 3 * (INVERT8SPEED(_<Player>().movementSpeed_));
    }
}

void KeyboardMovement::OnKeyDown(SDL_Keycode key)
{
    pressedKeys_.insert(key);
}

void KeyboardMovement::OnKeyUp(SDL_Keycode key)
{
    pressedKeys_.erase(key);
}