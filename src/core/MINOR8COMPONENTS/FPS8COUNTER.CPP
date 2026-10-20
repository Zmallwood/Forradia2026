// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "FPS8COUNTER.HPP"
#include "CORE/RENDERING/TEXT/TEXT_RENDERER.HPP"

void FPS8COUNTER::UPDATE()
{
    auto now = NOW();

    if (now > ticksLastUpdate_ + kOneSecondMillis)
    {
        fps_ = framesCounter_;
        framesCounter_ = 0;
        ticksLastUpdate_ = now;
    }

    ++framesCounter_;
}

void FPS8COUNTER::RENDER()
{
    std::string text = "FPS: " + std::to_string(fps_);

    _<TextRenderer>().DrawString(text, 0.95f, 0.03f);
}