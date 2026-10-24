//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "GUI8BUTTON.HPP"
#include "CORE/MINOR8COMPONENTS/CURSOR.HPP"
#include "CORE/RENDERING/TEXT/TEXT8RENDERER.HPP"

namespace FORRADIA8GAME {
    GUI8BUTTON::GUI8BUTTON(std::string_view text, float x, float y, float width,
                           float height, std::function<void()> action,
                           std::string_view backgroundImage,
                           std::string_view hoveredBackgroundImage)
        : GUI8PANEL(x, y, width, height), mText(text), mAction(action),
          kBackgroundImage(backgroundImage),
          kHoveredBackgroundImage(hoveredBackgroundImage) {
    }

    void
    GUI8BUTTON::UPDATE8DERIVED() {
        GUI8PANEL::UPDATE8DERIVED();

        auto position{GET8POSITION()};

        auto size{mSize};

        RECT8F rect{position.x, position.y, size.width, size.height};

        if (rect.CONTAINS(GET8MOUSE8POSITION())) {
            mHovered = true;

            _<CURSOR>().mCursorStyle = CURSOR8STYLES::Hovering;
        } else {
            mHovered = false;
        }
    }

    void
    GUI8BUTTON::RENDER8DERIVED() {
        GUI8PANEL::RENDER8DERIVED();

        auto position{GET8POSITION()};

        auto size{mSize};

        _<TEXT8RENDERER>().DRAW8STRING(mText, position.x + size.width / 2,
                                       position.y + size.height / 2,
                                       FONT8SIZES::_15, true);
    }

    bool
    GUI8BUTTON::ON8MOUSE8DOWN(Uint8 mouseButton) {
        if (!mIsVisible)
            return false;

        auto mousePosition{GET8MOUSE8POSITION()};

        if (GET8BOUNDS().CONTAINS(mousePosition)) {
            mAction();

            return true;
        }

        return false;
    }

    std::string
    GUI8BUTTON::GET8BACKGROUND8IMAGE() {
        return mHovered ? kHoveredBackgroundImage : kBackgroundImage;
    }
}