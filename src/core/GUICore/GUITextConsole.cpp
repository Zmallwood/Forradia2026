/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "GUITextConsole.hpp"
#include "Core/Rendering/Text/TextRenderer.hpp"

GUITextConsole::GUITextConsole() : GUIPanel(0.0f, 0.8f, 0.4f, 0.2f)
{
}

void GUITextConsole::PrintLine(std::string_view line)
{
    lines_.push_back(line.data());
}

void GUITextConsole::RenderDerived()
{
    GUIPanel::RenderDerived();

    auto position{GetPosition()};

    auto size{size_};

    auto maxNumLines{static_cast<int>(size.height / k_lineHeight_) - 1};

    auto iStart{std::max(0, static_cast<int>(lines_.size() - maxNumLines))};

    auto rowIndex{0};

    for (auto line = iStart; line < lines_.size(); line++)
    {
        if (line > lines_.size() - 1)
            break;

        auto text{lines_[line]};

        _<TextRenderer>().DrawString(text, position.x + 0.01F,
                                     position.y + 0.01F +
                                         rowIndex * k_lineHeight_);

        rowIndex++;
    }
}