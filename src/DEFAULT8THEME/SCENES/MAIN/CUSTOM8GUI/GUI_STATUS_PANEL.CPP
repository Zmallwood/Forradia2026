// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"
#include "CORE/RENDERING/TEXT/TEXT_RENDERER.HPP"
#include "DEFAULT8THEME/THEME8MATH/EXPERIENCE_MATH.HPP"
#include "GUI_HEALTH_METER.HPP"
#include "GUI_STATUS_PANEL.HPP"

GUIStatusPanel::GUIStatusPanel() : GUI8PANEL(0.0f, 0.0f, 0.2f, 0.2f)
{
    ADD8COMPONENT(std::make_shared<GUIHealthMeter>());
}

void GUIStatusPanel::RENDER8DERIVED()
{
    GUI8PANEL::RENDER8DERIVED();

    _<TextRenderer>().DrawString(_<PLAYER>().name_, 0.015f, 0.01f,
                                 FontSizes::_18, false);

    auto playerLevel = CalculateCurrentLevel(_<PLAYER>().experience_);

    std::string levelText = "Level " + std::to_string(playerLevel);

    _<TextRenderer>().DrawString(levelText, 0.015f, 0.04f, FontSizes::_24,
                                 false, COLORS::k_yellowGray);

    std::stringstream ssHealth;

    ssHealth << std::fixed << std::setprecision(1)
             << "Health: " << _<PLAYER>().health_ << "/"
             << _<PLAYER>().maxHealth_;

    _<TextRenderer>().DrawString(ssHealth.str(), 0.015f, 0.08f, FontSizes::_12,
                                 false, COLORS::k_wheat);
}