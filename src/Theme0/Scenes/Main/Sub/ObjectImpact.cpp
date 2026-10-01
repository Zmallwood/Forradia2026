/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "ObjectImpact.hpp"
#include "Core/Assets/ImageBank.hpp"
#include "Core/Configuration/GameProperties.hpp"
#include "Core/Configuration/ObjectIndex.hpp"
#include "Core/WorldStructure/Object.hpp"
#include "FirstPersonHovering.hpp"

namespace Forradia
{
    void ObjectImpact::OnMouseDown(Uint8 button)
    {
        if (button != SDL_BUTTON_LEFT)
        {
            return;
        }

        auto hoveredObject{_<FirstPersonHovering>().hoveredObject_};

        if (!hoveredObject)
        {
            return;
        }

        constexpr auto largeObjectScale{GameProperties::k_largeObjectScale_};
        constexpr auto smallObjectScale{GameProperties::k_smallObjectScale_};

        auto mousePosition{GetMousePosition()};

        auto hoveringMouseOffset{
            _<FirstPersonHovering>().hoveredThingMouseOffset_};

        auto imageSize{_<ImageBank>().GetImageSize(hoveredObject->type_)};

        float imageWidth;
        float imageHeight;

        auto isSmallObject{
            _<ObjectIndex>().IsSmallObject(hoveredObject->type_)};

        if (isSmallObject)
        {
            imageWidth = imageSize.width / 60.0f * smallObjectScale;
            imageHeight = imageSize.height / 60.0f *
                          ConvertWidthToHeight(smallObjectScale);
        }
        else
        {
            imageWidth = imageSize.width / 60.0f * largeObjectScale;
            imageHeight = imageSize.height / 60.0f *
                          ConvertWidthToHeight(largeObjectScale);
        }

        auto imageX{mousePosition.x - hoveringMouseOffset.x -
                    imageWidth / 2.0f};
        auto imageY{mousePosition.y - hoveringMouseOffset.y - imageHeight};

        auto impactPointWidth{GameProperties::k_impactPointWidth_};
        auto impactPointHeight{ConvertWidthToHeight(impactPointWidth)};

        auto &impactPoints{hoveredObject->impactPoints_};

        for (auto &impactPoint : impactPoints)
        {
            auto impactPointX{imageX + impactPoint.position.x * imageWidth -
                              impactPointWidth / 2.0f};
            auto impactPointY{imageY + impactPoint.position.y * imageHeight -
                              impactPointHeight / 2.0f};

            auto rect{RectF{impactPointX, impactPointY, impactPointWidth,
                            impactPointHeight}};

            if (rect.Contains(mousePosition))
            {
                impactPoint.completed = true;
            }
        }
    }
}