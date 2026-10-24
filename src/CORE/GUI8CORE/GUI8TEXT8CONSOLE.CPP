//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "GUI8TEXT8CONSOLE.HPP"
#include "CORE/RENDERING/TEXT/TEXT8RENDERER.HPP"

namespace FORRADIA8GAME {
    GUI8TEXT8CONSOLE::GUI8TEXT8CONSOLE() : GUI8PANEL(0.0F, 0.8F, 0.4F, 0.2F) {
    }

    void
    GUI8TEXT8CONSOLE::PRINT8LINE(std::string_view line) {
        mLines.push_back(line.data());
    }

    void
    GUI8TEXT8CONSOLE::RENDER8DERIVED() {
        GUI8PANEL::RENDER8DERIVED();

        auto position{GET8POSITION()};
        auto size{mSize};

        auto maxNumLines{static_cast<int>(size.height / mkLineHeight) - 1};

        auto iStart{std::max(0, static_cast<int>(mLines.size() - maxNumLines))};

        auto rowIndex{0};

        for (auto line = iStart; line < mLines.size(); line++) {
            if (line > mLines.size() - 1)
                break;

            auto text{mLines[line]};

            _<TEXT8RENDERER>().DRAW8STRING(text, position.x + 0.01F,
                                           position.y + 0.01F +
                                               rowIndex * mkLineHeight);

            rowIndex++;
        }
    }
}