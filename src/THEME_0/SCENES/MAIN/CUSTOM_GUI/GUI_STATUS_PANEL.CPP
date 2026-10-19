// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "GUI_STATUS_PANEL.HPP"
#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"
#include "CORE/RENDERING/TEXT/TEXT_RENDERER.HPP"
#include "GUI_HEALTH_METER.HPP"
#include "THEME_0/THEME_0_MATH/EXPERIENCE_MATH.HPP"

GUIStatusPanel::GUIStatusPanel() : GUIPanel(0.0f, 0.0f, 0.2f, 0.2f)
{
    AddComponent(std::make_shared<GUIHealthMeter>());
}

void GUIStatusPanel::RenderDerived()
{
    GUIPanel::RenderDerived();

    _<TextRenderer>().DrawString(_<Player>().name_, 0.015f, 0.01f,
                                 FontSizes::_18, false);

    auto playerLevel = CalculateCurrentLevel(_<Player>().experience_);

    std::string levelText = "Level " + std::to_string(playerLevel);

    _<TextRenderer>().DrawString(levelText, 0.015f, 0.04f, FontSizes::_24,
                                 false, COLORS::k_yellowGray);

    std::stringstream ssHealth;

    ssHealth << std::fixed << std::setprecision(1)
             << "Health: " << _<Player>().health_ << "/"
             << _<Player>().maxHealth_;

    _<TextRenderer>().DrawString(ssHealth.str(), 0.015f, 0.08f, FontSizes::_12,
                                 false, COLORS::k_wheat);
}