//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "GUI8WINDOW.HPP"
#include "GUI8WINDOW8TITLE8BAR.HPP"

namespace FORRADIA8GAME {
    GUI8WINDOW::GUI8WINDOW(std::string_view title, float x, float y,
                           float width, float height)
        : GUI8PANEL(x, y, width, height) {
        mIsVisible = false;
        mTitleBar = dynamic_pointer_cast<GUI8WINDOW8TITLE8BAR>(ADD8COMPONENT(
            std::make_shared<GUI8WINDOW8TITLE8BAR>(title, width, *this)));
    }

    void
    GUI8WINDOW::TOGGLE8VISIBILITY() {
        mIsVisible = !mIsVisible;
    }
}