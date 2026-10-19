// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "FPS_COUNTER.HPP"
#include "CORE/RENDERING/TEXT/TEXT_RENDERER.HPP"

void FPSCounter::Update()
{
    auto now = Now();

    if (now > ticksLastUpdate_ + k_oneSecondMillis)
    {
        fps_ = framesCounter_;
        framesCounter_ = 0;
        ticksLastUpdate_ = now;
    }

    ++framesCounter_;
}

void FPSCounter::Render()
{
    std::string text = "FPS: " + std::to_string(fps_);

    _<TextRenderer>().DrawString(text, 0.95f, 0.03f);
}