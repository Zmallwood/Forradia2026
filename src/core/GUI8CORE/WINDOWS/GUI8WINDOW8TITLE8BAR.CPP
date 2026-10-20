//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "GUI8WINDOW8TITLE8BAR.HPP"
#include "CORE/RENDERING/TEXT/TEXT8RENDERER.HPP"
#include "GUI8WINDOW.HPP"

namespace FORRADIA8GAME
{
    GUI8WINDOW8TITLE8BAR::GUI8WINDOW8TITLE8BAR(std::string_view title,
                                               float width,
                                               GUI8WINDOW &guiWindow)
        : GUI8PANEL(0.0f, 0.0f, width, 0.05f), title_(title),
          guiWindow_(guiWindow)
    {
    }

    void
    GUI8WINDOW8TITLE8BAR::UPDATE8DERIVED()
    {
        GUI8PANEL::UPDATE8DERIVED();

        auto mousePosition = GET8MOUSE8POSITION();

        if (isMoving_)
        {
            auto delta = mousePosition - mousePositionStartMove_;

            auto newPosition = positionStartMove_ + delta;

            SET8POSITION(newPosition);
        }
    }

    bool
    GUI8WINDOW8TITLE8BAR::ON8MOUSE8DOWN(Uint8 mouseButton)
    {
        auto mousePosition = GET8MOUSE8POSITION();

        if (GET8BOUNDS().CONTAINS(mousePosition))
        {
            positionStartMove_ = GET8POSITION();

            mousePositionStartMove_ = GET8MOUSE8POSITION();

            isMoving_ = true;

            return true;
        }

        return false;
    }

    bool
    GUI8WINDOW8TITLE8BAR::ON8MOUSE8UP(Uint8 mouseButton, int clickSpeed)
    {
        auto mousePosition = GET8MOUSE8POSITION();

        if (GET8BOUNDS().CONTAINS(mousePosition))
        {
            isMoving_ = false;

            return true;
        }

        return false;
    }

    void
    GUI8WINDOW8TITLE8BAR::RENDER8DERIVED()
    {
        GUI8PANEL::RENDER8DERIVED();

        auto position = GET8POSITION();

        _<TEXT8RENDERER>().DRAW8STRING(title_, position.x + kMargin_.x,
                                       position.y + kMargin_.y, FONT8SIZES::_18,
                                       false);
    }

    std::string
    GUI8WINDOW8TITLE8BAR::GET8BACKGROUND8IMAGE()
    {
        return kDefaultBackgroundImage_;
    }

    POINT8F
    GUI8WINDOW8TITLE8BAR::GET8POSITION()
    {
        return guiWindow_.GET8POSITION();
    }

    void
    GUI8WINDOW8TITLE8BAR::SET8POSITION(POINT8F value)
    {
        guiWindow_.SET8POSITION(value);
    }
}