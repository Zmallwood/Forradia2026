// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "ObjectImpact.hpp"
#include "Core/Assets/ImageBank.hpp"
#include "Core/Configuration/GameProperties.hpp"
#include "Core/Configuration/ObjectIndex.hpp"
#include "Core/CoreGameObjects/Player.hpp"
#include "Core/CoreGameObjects/PlayerEquipment.hpp"
#include "Core/WorldStructure/Object.hpp"
#include "FirstPersonView/FirstPersonView.hpp"
#include "FirstPersonView/FirstPersonViewFunctions.hpp"

void ObjectImpact::OnMouseDown(Uint8 button)
{
    if (button != SDL_BUTTON_LEFT)
    {
        return;
    }

    auto viewWidth{GameProperties::k_viewWidth_};

    auto mousePosition{GetMousePosition()};

    if (mousePosition.x < viewWidth)
    {
        return;
    }

    auto orderedObjects{GetOrderedObjects()};

    auto tileUnitsWidth{_<GameProperties>().k_tileUnitsWidth_};

    constexpr auto k_margin{GameProperties::k_firstPersonViewMargin_};
    constexpr auto largeObjectScale{GameProperties::k_largeObjectScale_};
    constexpr auto smallObjectScale{GameProperties::k_smallObjectScale_};

    auto now{Now()};

    auto rightHandObject{_<Player>().playerEquipment_->rightHandObject_};
    auto leftHandObject{_<Player>().playerEquipment_->leftHandObject_};

    for (auto &entry : orderedObjects)
    {
        auto xPos{entry.second.position_.x};
        auto yPos{entry.second.position_.y};

        auto object{entry.second.object_};
        auto objectType{object->type_};

        auto impactObjects{_<ObjectIndex>().GetImpactObjects(objectType)};

        auto canImpact{false};

        for (auto impactObject : impactObjects)
        {
            if (rightHandObject)
            {
                if (impactObject == rightHandObject->type_)
                {
                    canImpact = true;
                    break;
                }
            }

            if (leftHandObject)
            {
                if (impactObject == leftHandObject->type_)
                {
                    canImpact = true;
                    break;
                }
            }
        }

        if (!canImpact)
        {
            continue;
        }

        auto imageSize{_<ImageBank>().GetImageSize(objectType)};

        float imageWidth;
        float imageHeight;

        auto isSmallObject{_<ObjectIndex>().IsSmallObject(objectType)};

        if (isSmallObject)
        {
            imageWidth = imageSize.width / 60.0f * smallObjectScale *
                         (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                         tileUnitsWidth;
            imageHeight = imageSize.height / 60.0f *
                          ConvertWidthToHeight(
                              smallObjectScale *
                              (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                              tileUnitsWidth);
        }
        else
        {
            imageWidth = imageSize.width / 60.0f * largeObjectScale *
                         (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                         tileUnitsWidth;
            imageHeight = imageSize.height / 60.0f *
                          ConvertWidthToHeight(
                              largeObjectScale *
                              (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                              tileUnitsWidth);
        }

        auto tileWidth{viewWidth - 2 * k_margin.x -
                       static_cast<float>(tileUnitsWidth - yPos) /
                           tileUnitsWidth * viewWidth * 0.6f};
        auto tileLeft{1.0f - viewWidth + k_margin.x +
                      static_cast<float>(tileUnitsWidth - yPos) /
                          tileUnitsWidth * viewWidth * 0.3f};

        auto baseX{tileLeft +
                   static_cast<float>(xPos) / tileUnitsWidth * tileWidth};
        auto baseY{0.75f + k_margin.y +
                   static_cast<float>(yPos + 1) / tileUnitsWidth *
                       (0.25f - 2 * k_margin.y)};

        auto imageX{baseX - imageWidth / 2.0f};
        auto imageY{baseY - imageHeight};

        auto impactPointWidth{GameProperties::k_impactPointWidth_};
        auto impactPointHeight{ConvertWidthToHeight(impactPointWidth)};

        auto &impactPoints{object->impactPoints_};

        auto completedImpactPointThisClick{false};

        for (auto &impactPoint : impactPoints)
        {
            auto impactPointCenterX{imageX +
                                    impactPoint.position.x * imageWidth};
            auto impactPointCenterY{imageY +
                                    impactPoint.position.y * imageHeight};

            auto impactPointX{impactPointCenterX - impactPointWidth / 2.0f};
            auto impactPointY{impactPointCenterY - impactPointHeight / 2.0f};

            auto rect{RectF{impactPointX, impactPointY, impactPointWidth,
                            impactPointHeight}};

            if (rect.Contains(mousePosition) && !impactPoint.completed)
            {
                impactPoint.completed = true;

                completedImpactPointThisClick = true;

                _<FirstPersonView>().completedObjectImpacts_.push_back(
                    {PointF{impactPointCenterX, impactPointCenterY}, now});

                auto singleImpactPointCompletedAction{
                    _<ObjectIndex>().GetSingleImpactPointCompletedAction(
                        objectType)};

                singleImpactPointCompletedAction();
            }
        }

        if (!completedImpactPointThisClick)
        {
            continue;
        }

        auto allImpactPointsCompleted{!impactPoints.empty()};

        for (auto &impactPoint : impactPoints)
        {
            if (!impactPoint.completed)
            {
                allImpactPointsCompleted = false;
                break;
            }
        }

        if (allImpactPointsCompleted)
        {
            auto allImpactPointsCompletedAction{
                _<ObjectIndex>().GetAllImpactPointsCompletedAction(objectType)};

            allImpactPointsCompletedAction(object);
        }
    }
}