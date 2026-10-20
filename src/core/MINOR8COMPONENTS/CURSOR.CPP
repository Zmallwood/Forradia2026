//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "CURSOR.HPP"
#include "CORE/RENDERING/IMAGES/IMAGE8RENDERER.HPP"

namespace FORRADIA8GAME {
    CURSOR::CURSOR() {
        SDL_ShowCursor(SDL_DISABLE);
    }

    void
    CURSOR::RESET() {
        cursorStyle_ = CURSOR8STYLES::Default;
    }

    void
    CURSOR::RENDER() {
        auto mousePosition = GET8MOUSE8POSITION();

        auto cursorWidth = kCursorSize_;
        auto cursorHeight = CONVERT8WIDTH8TO8HEIGHT(cursorWidth);

        std::string cursorImage;

        switch (cursorStyle_) {
        case CURSOR8STYLES::Hovering:
            cursorImage = "CursorHovering";
            break;
        case CURSOR8STYLES::Default:
        default:
            cursorImage = "CursorDefault";
            break;
        }

        _<IMAGE8RENDERER>().DRAW8IMAGE(
            cursorImage, mousePosition.x - cursorWidth / 2,
            mousePosition.y - cursorHeight / 2, cursorWidth, cursorHeight);
    }
}