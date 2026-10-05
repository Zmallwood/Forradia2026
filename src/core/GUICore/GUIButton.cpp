/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "GUIButton.hpp"
#include "Core/MinorComponents/Cursor.hpp"
#include "Core/Rendering/Text/TextRenderer.hpp"

GUIButton::GUIButton(std::string_view text, float x, float y, float width,
                     float height, std::function<void()> action,
                     std::string_view backgroundImage,
                     std::string_view hoveredBackgroundImage)
    : GUIPanel(x, y, width, height), text_(text), action_(action),
      k_backgroundImage_(backgroundImage),
      k_hoveredBackgroundImage_(hoveredBackgroundImage)
{
}

void GUIButton::UpdateDerived()
{
    GUIPanel::UpdateDerived();

    auto position{GetPosition()};

    auto size{size_};

    auto rect{RectF{position.x, position.y, size.width, size.height}};

    if (rect.Contains(GetMousePosition()))
    {
        hovered_ = true;

        _<Cursor>().cursorStyle_ = CursorStyles::Hovering;
    }
    else
    {
        hovered_ = false;
    }
}

void GUIButton::RenderDerived()
{
    GUIPanel::RenderDerived();

    auto position{GetPosition()};

    auto size{size_};

    _<TextRenderer>().DrawString(text_, position.x + size.width / 2,
                                 position.y + size.height / 2, FontSizes::_12,
                                 true);
}

bool GUIButton::OnMouseDown(Uint8 mouseButton)
{
    if (!isVisible_)
    {
        return false;
    }

    auto mousePosition{GetMousePosition()};

    if (GetBounds().Contains(mousePosition))
    {
        action_();

        return true;
    }

    return false;
}

std::string GUIButton::GetBackgroundImage()
{
    return hovered_ ? k_hoveredBackgroundImage_ : k_backgroundImage_;
}