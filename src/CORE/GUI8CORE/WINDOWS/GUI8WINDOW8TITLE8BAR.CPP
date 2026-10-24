//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "GUI8WINDOW8TITLE8BAR.HPP"
#include "CORE/RENDERING/TEXT/TEXT8RENDERER.HPP"
#include "GUI8WINDOW.HPP"

namespace FORRADIA8GAME {
    GUI8WINDOW8TITLE8BAR::GUI8WINDOW8TITLE8BAR(std::string_view title,
                                               float width,
                                               GUI8WINDOW &guiWindow)
        : GUI8PANEL(0.0F, 0.0F, width, 0.05F), mTitle(title),
          mGUIWindow(guiWindow) {
    }

    void
    GUI8WINDOW8TITLE8BAR::UPDATE8DERIVED() {
        GUI8PANEL::UPDATE8DERIVED();

        auto mousePosition{GET8MOUSE8POSITION()};

        if (mIsMoving) {
            auto delta{mousePosition - mMousePositionStartMove};
            auto newPosition{mPositionStartMove + delta};

            SET8POSITION(newPosition);
        }
    }

    bool
    GUI8WINDOW8TITLE8BAR::ON8MOUSE8DOWN(Uint8 mouseButton) {
        auto mousePosition{GET8MOUSE8POSITION()};

        if (GET8BOUNDS().CONTAINS(mousePosition)) {
            mPositionStartMove = GET8POSITION();
            mMousePositionStartMove = GET8MOUSE8POSITION();
            mIsMoving = true;
            return true;
        }

        return false;
    }

    bool
    GUI8WINDOW8TITLE8BAR::ON8MOUSE8UP(Uint8 mouseButton, int clickSpeed) {
        auto mousePosition{GET8MOUSE8POSITION()};

        if (GET8BOUNDS().CONTAINS(mousePosition)) {
            mIsMoving = false;
            return true;
        }

        return false;
    }

    void
    GUI8WINDOW8TITLE8BAR::RENDER8DERIVED() {
        GUI8PANEL::RENDER8DERIVED();

        auto position{GET8POSITION()};

        _<TEXT8RENDERER>().DRAW8STRING(mTitle, position.x + mkMargin.x,
                                       position.y + mkMargin.y, FONT8SIZES::_20,
                                       false);
    }

    std::string
    GUI8WINDOW8TITLE8BAR::GET8BACKGROUND8IMAGE() {
        return mkDefaultBackgroundImage;
    }

    POINT8F
    GUI8WINDOW8TITLE8BAR::GET8POSITION() {
        return mGUIWindow.GET8POSITION();
    }

    void
    GUI8WINDOW8TITLE8BAR::SET8POSITION(POINT8F value) {
        mGUIWindow.SET8POSITION(value);
    }
}