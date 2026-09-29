/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "GUIStatusPanel.hpp"
#include "Core/CoreGameObjects/Player.hpp"
#include "Core/Rendering/Text/TextRenderer.hpp"
#include "Theme0/Theme0Math/ExperienceMath.hpp"

namespace Forradia
{
    GUIStatusPanel::GUIStatusPanel() : GUIPanel(0.0f, 0.0f, 0.2f, 0.2f)
    {
    }

    void GUIStatusPanel::RenderDerived()
    {
        GUIPanel::RenderDerived();

        _<TextRenderer>().DrawString(_<Player>().name_, 0.015f, 0.01f,
                                     FontSizes::_18, false);

        auto playerLevel{CalculateCurrentLevel(_<Player>().experience_)};

        std::string levelText{"Level " + std::to_string(playerLevel)};

        _<TextRenderer>().DrawString(levelText, 0.015f, 0.04f, FontSizes::_24,
                                     false, Colors::k_yellowGray);
    }
}