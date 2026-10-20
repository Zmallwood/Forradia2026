// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CORE/GUI8CORE/GUI.HPP"
#include "I8SCENE.HPP"

I8SCENE::I8SCENE() : gui_(std::make_shared<GUI>())
{
}

void
I8SCENE::INITIALIZE()
{
    INITIALIZE8DERIVED();
}

void
I8SCENE::ON8ENTER()
{
    ON8ENTER8DERIVED();
}

void
I8SCENE::UPDATE()
{
    gui_->UPDATE();

    UPDATE8DERIVED();
}

void
I8SCENE::RENDER()
{
    RENDER8BEFORE8GUI8DERIVED();

    gui_->RENDER();

    RENDER8AFTER8GUI8DERIVED();
}

void
I8SCENE::ON8KEY8DOWN(SDL_Keycode key)
{
    if (gui_->ON8KEY8DOWN(key))
    {
        return;
    }

    ON8KEY8DOWN8DERIVED(key);
}

void
I8SCENE::ON8KEY8UP(SDL_Keycode key)
{
    if (gui_->ON8KEY8UP(key))
    {
        return;
    }

    ON8KEY8UP8DERIVED(key);
}

void
I8SCENE::ON8MOUSE8DOWN(Uint8 button)
{
    if (gui_->ON8MOUSE8DOWN(button))
    {
        return;
    }

    ON8MOUSE8DOWN8DERIVED(button);
}

void
I8SCENE::ON8MOUSE8UP(Uint8 button, int clickSpeed)
{
    if (gui_->ON8MOUSE8UP(button, clickSpeed))
    {
        return;
    }

    ON8MOUSE8UP8DERIVED(button, clickSpeed);
}