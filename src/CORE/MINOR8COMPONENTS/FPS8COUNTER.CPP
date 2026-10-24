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
        auto now{NOW()};
        if (now > mTicksLastUpdate + kOneSecondMillis) {
            mFPS = mFramesCounter;
            mFramesCounter = 0;
            mTicksLastUpdate = now;
        }
        ++mFramesCounter;
    }

    void
    FPS8COUNTER::RENDER() {
        std::string text{"FPS: " + std::to_string(mFPS)};
        _<TEXT8RENDERER>().DRAW8STRING(text, 0.95F, 0.03F);
    }
}