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
        : GUI8PANEL(x, y, width, height), text_(text), action_(action),
          kBackgroundImage_(backgroundImage),
          kHoveredBackgroundImage_(hoveredBackgroundImage) {
    }

    void
    GUI8BUTTON::UPDATE8DERIVED() {
        GUI8PANEL::UPDATE8DERIVED();

        auto position = GET8POSITION();

        auto size = size_;

        auto rect = RECT8F{position.x, position.y, size.width, size.height};

        if (rect.CONTAINS(GET8MOUSE8POSITION())) {
            hovered_ = true;

            _<CURSOR>().cursorStyle_ = CURSOR8STYLES::Hovering;
        } else {
            hovered_ = false;
        }
    }

    void
    GUI8BUTTON::RENDER8DERIVED() {
        GUI8PANEL::RENDER8DERIVED();

        auto position = GET8POSITION();

        auto size = size_;

        _<TEXT8RENDERER>().DRAW8STRING(text_, position.x + size.width / 2,
                                       position.y + size.height / 2,
                                       FONT8SIZES::_12, true);
    }

    bool
    GUI8BUTTON::ON8MOUSE8DOWN(Uint8 mouseButton) {
        if (!isVisible_)
            return false;

        auto mousePosition = GET8MOUSE8POSITION();

        if (GET8BOUNDS().CONTAINS(mousePosition)) {
            action_();

            return true;
        }

        return false;
    }

    std::string
    GUI8BUTTON::GET8BACKGROUND8IMAGE() {
        return hovered_ ? kHoveredBackgroundImage_ : kBackgroundImage_;
    }
}