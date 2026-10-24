//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "GUI8PANEL.HPP"
#include "CORE/RENDERING/IMAGES/IMAGE8RENDERER.HPP"

namespace FORRADIA8GAME {
    GUI8PANEL::GUI8PANEL(float x, float y, float width, float height)
        : GUI8COMPONENT(x, y), mSize(width, height) {
    }

    bool
    GUI8PANEL::ON8MOUSE8DOWN(Uint8 mouseButton) {
        auto result{GUI8COMPONENT::ON8MOUSE8DOWN(mouseButton)};

        if (result)
            return true;

        if (!mIsVisible || !mIsEnabled)
            return false;

        return GET8BOUNDS().CONTAINS(GET8MOUSE8POSITION());
    }

    void
    GUI8PANEL::RENDER8DERIVED() {
        auto position{GET8POSITION()};

        _<IMAGE8RENDERER>().DRAW8IMAGE(GET8BACKGROUND8IMAGE(), position.x,
                                       position.y, mSize.width, mSize.height);
    }

    std::string
    GUI8PANEL::GET8BACKGROUND8IMAGE() {
        return kDefaultBackgroundImage;
    }

    RECT8F
    GUI8PANEL::GET8BOUNDS() {
        auto position{GET8POSITION()};

        return {position.x, position.y, mSize.width, mSize.height};
    }
}