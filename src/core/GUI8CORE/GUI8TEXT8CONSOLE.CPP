// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CORE/RENDERING/TEXT/TEXT_RENDERER.HPP"
#include "GUI8TEXT8CONSOLE.HPP"

GUI8TEXT8CONSOLE::GUI8TEXT8CONSOLE() : GUI8PANEL(0.0f, 0.8f, 0.4f, 0.2f)
{
}

void GUI8TEXT8CONSOLE::PRINT8LINE(std::string_view line)
{
    lines_.push_back(line.data());
}

void GUI8TEXT8CONSOLE::RENDER8DERIVED()
{
    GUI8PANEL::RENDER8DERIVED();

    auto position = GET8POSITION();

    auto size = size_;

    auto maxNumLines = static_cast<int>(size.height / k_lineHeight_) - 1;

    auto iStart = std::max(0, static_cast<int>(lines_.size() - maxNumLines));

    auto rowIndex = 0;

    for (auto line = iStart; line < lines_.size(); line++)
    {
        if (line > lines_.size() - 1)
        {
            break;
        }

        auto text = lines_[line];

        _<TextRenderer>().DrawString(text, position.x + 0.01F,
                                     position.y + 0.01F +
                                         rowIndex * k_lineHeight_);

        rowIndex++;
    }
}