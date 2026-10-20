// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CORE/ASSETS/IMAGE8BANK.HPP"
#include "CORE/CONFIGURATION/GAME8PROPERTIES.HPP"
#include "CORE/CONFIGURATION/OBJECT8INDEX.HPP"
#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"
#include "CORE/CORE_GAME_OBJECTS/PLAYER8EQUIPMENT.HPP"
#include "CORE/WORLD8STRUCTURE/OBJECT.HPP"
#include "FIRST8PERSON8VIEW/FIRST_PERSON_VIEW.HPP"
#include "FIRST8PERSON8VIEW/FIRST_PERSON_VIEW_FUNCTIONS.HPP"
#include "OBJECT_IMPACT.HPP"

void ObjectImpact::OnMouseDown(Uint8 button)
{
    if (button != SDL_BUTTON_LEFT)
    {
        return;
    }

    auto viewWidth{GAME8PROPERTIES::kViewWidth_};

    auto mousePosition{GET8MOUSE8POSITION()};

    if (mousePosition.x < viewWidth)
    {
        return;
    }

    auto now{NOW()};

    if (now <
        _<PLAYER>().ticksLastImpact_ + INVERT8SPEED(_<PLAYER>().impactSpeed_))
    {
        return;
    }

    auto orderedObjects{GetOrderedObjects()};

    auto tileUnitsWidth{_<GAME8PROPERTIES>().kTileUnitsWidth_};

    constexpr auto kMargin{GAME8PROPERTIES::kFirstPersonViewMargin_};
    constexpr auto largeObjectScale{GAME8PROPERTIES::kLargeObjectScale_};
    constexpr auto smallObjectScale{GAME8PROPERTIES::kSmallObjectScale_};

    auto rightHandObject{_<PLAYER>().playerEquipment_->rightHandObject_};
    auto leftHandObject{_<PLAYER>().playerEquipment_->leftHandObject_};

    for (auto &entry : orderedObjects)
    {
        auto xPos{entry.second.position_.x};
        auto yPos{entry.second.position_.y};

        auto object{entry.second.object_};
        auto objectType{object->type_};

        auto impactObjects{_<OBJECT8INDEX>().GET8IMPACT8OBJECTS(objectType)};

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

        auto imageSize{_<IMAGE8BANK>().GET8IMAGE8SIZE(objectType)};

        float imageWidth;
        float imageHeight;

        auto isSmallObject{_<OBJECT8INDEX>().IS8SMALL8OBJECT(objectType)};

        if (isSmallObject)
        {
            imageWidth = imageSize.width / 60.0f * smallObjectScale *
                         (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                         tileUnitsWidth;
            imageHeight = imageSize.height / 60.0f *
                          CONVERT8WIDTH8TO8HEIGHT(
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
                          CONVERT8WIDTH8TO8HEIGHT(
                              largeObjectScale *
                              (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                              tileUnitsWidth);
        }

        auto tileWidth{viewWidth - 2 * kMargin.x -
                       static_cast<float>(tileUnitsWidth - yPos) /
                           tileUnitsWidth * viewWidth * 0.6f};
        auto tileLeft{1.0f - viewWidth + kMargin.x +
                      static_cast<float>(tileUnitsWidth - yPos) /
                          tileUnitsWidth * viewWidth * 0.3f};

        auto baseX{tileLeft +
                   static_cast<float>(xPos) / tileUnitsWidth * tileWidth};
        auto baseY{0.75f + kMargin.y +
                   static_cast<float>(yPos + 1) / tileUnitsWidth *
                       (0.25f - 2 * kMargin.y)};

        auto imageX{baseX - imageWidth / 2.0f};
        auto imageY{baseY - imageHeight};

        auto renderOffset{
            _<OBJECT8INDEX>().GET8FIRST8PERSON8VIEW8RENDER8OFFSET(objectType)};

        imageX += renderOffset.x * tileWidth;

        constexpr auto kTileHeight{0.25f};

        imageY += renderOffset.y * kTileHeight;

        auto impactPointWidth{GAME8PROPERTIES::kImpactPointWidth_};
        auto impactPointHeight{CONVERT8WIDTH8TO8HEIGHT(impactPointWidth)};

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

            auto rect{RECT8F{impactPointX, impactPointY, impactPointWidth,
                             impactPointHeight}};

            if (rect.CONTAINS(mousePosition) && !impactPoint.completed)
            {
                impactPoint.completed = true;

                completedImpactPointThisClick = true;

                _<PLAYER>().ticksLastImpact_ = now;

                _<FirstPersonView>().completedObjectImpacts_.push_back(
                    {POINT8F{impactPointCenterX, impactPointCenterY}, now});

                auto singleImpactPointCompletedAction{
                    _<OBJECT8INDEX>().GET8SINGLE8IMPACT8POINT8COMPLETED8ACTION(
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
                _<OBJECT8INDEX>().GET8ALL8IMPACT8POINTS8COMPLETED8ACTION(
                    objectType)};

            allImpactPointsCompletedAction(object);
        }
    }
}