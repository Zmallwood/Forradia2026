//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "FPS8COUNTER.HPP"
#include "CORE/RENDERING/TEXT/TEXT8RENDERER.HPP"

namespace FORRADIA8GAME {
    void
    FPS8COUNTER::UPDATE() {
        auto now = NOW();

        if (now > ticksLastUpdate_ + kOneSecondMillis) {
            fps_ = framesCounter_;
            framesCounter_ = 0;
            ticksLastUpdate_ = now;
        }

        ++framesCounter_;
    }

    void
    FPS8COUNTER::RENDER() {
        std::string text = "FPS: " + std::to_string(fps_);

        _<TEXT8RENDERER>().DRAW8STRING(text, 0.95f, 0.03f);
    }
}