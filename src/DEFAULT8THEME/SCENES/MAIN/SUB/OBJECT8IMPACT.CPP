//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "OBJECT8IMPACT.HPP"
#include "CORE/ASSETS/IMAGE8BANK.HPP"
#include "CORE/CONFIGURATION/GAME8PROPERTIES.HPP"
#include "CORE/CONFIGURATION/OBJECT8INDEX.HPP"
#include "CORE/CORE8GAME8OBJECTS/PLAYER.HPP"
#include "CORE/CORE8GAME8OBJECTS/PLAYER8EQUIPMENT.HPP"
#include "CORE/WORLD8STRUCTURE/OBJECT.HPP"
#include "FIRST8PERSON8VIEW/FIRST8PERSON8VIEW.HPP"
#include "FIRST8PERSON8VIEW/FIRST8PERSON8VIEW8FUNCTIONS.HPP"
#include "CORE/CORE8GAME8OBJECTS/PLAYER8EQUIPMENT8SLOTS.HPP"

namespace FORRADIA8GAME {
    void
    OBJECT8IMPACT::ON8MOUSE8DOWN(Uint8 button) {
        if (button != SDL_BUTTON_LEFT)
            return;

        auto viewWidth{GAME8PROPERTIES::mkViewWidth};

        auto mousePosition{GET8MOUSE8POSITION()};

        if (mousePosition.x < viewWidth)
            return;

        auto now{NOW()};

        if (now < _<PLAYER>().mTicksLastImpact +
                      INVERT8SPEED(_<PLAYER>().mImpactSpeed))
            return;

        auto orderedObjects{GET8ORDERED8OBJECTS()};

        auto tileUnitsWidth{_<GAME8PROPERTIES>().mkTileUnitsWidth};

        constexpr auto kMargin{GAME8PROPERTIES::mkFirstPersonViewMargin};
        constexpr auto largeObjectScale{GAME8PROPERTIES::mkLargeObjectScale};
        constexpr auto smallObjectScale{GAME8PROPERTIES::mkSmallObjectScale};

        using namespace PLAYER8EQUIPMENT8SLOTS;

        auto rightHandObject{_<PLAYER>().mPlayerEquipment->mSlots[kRightHand]};
        auto leftHandObject{_<PLAYER>().mPlayerEquipment->mSlots[kLeftHand]};

        for (auto &entry : orderedObjects) {
            auto xPos{entry.second.position_.x};
            auto yPos{entry.second.position_.y};

            auto object{entry.second.object_};
            auto objectType{object->mType};

            auto impactActions{
                _<OBJECT8INDEX>().GET8OBJECT8IMPACT8ACTIONS(objectType)};

            OBJECT8IMPACT8ACTION *impactAction{nullptr};

            auto canImpact{false};

            for (auto &impactActionEntry : impactActions) {
                if (rightHandObject) {
                    if (HASH(impactActionEntry.objectName) ==
                        rightHandObject->mType) {
                        canImpact = true;
                        impactAction = &impactActionEntry;
                        break;
                    }
                }

                if (leftHandObject) {
                    if (HASH(impactActionEntry.objectName) ==
                        leftHandObject->mType) {
                        canImpact = true;
                        impactAction = &impactActionEntry;
                        break;
                    }
                }
            }

            if (!canImpact)
                continue;

            auto imageSize{_<IMAGE8BANK>().GET8IMAGE8SIZE(objectType)};

            float imageWidth;
            float imageHeight;

            auto isSmallObject{_<OBJECT8INDEX>().IS8SMALL8OBJECT(objectType)};

            if (isSmallObject) {
                imageWidth = imageSize.width / 60.0F * smallObjectScale *
                             (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                             tileUnitsWidth;
                imageHeight =
                    imageSize.height / 60.0F *
                    CONVERT8WIDTH8TO8HEIGHT(
                        smallObjectScale *
                        (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                        tileUnitsWidth);
            } else {
                imageWidth = imageSize.width / 60.0F * largeObjectScale *
                             (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                             tileUnitsWidth;
                imageHeight =
                    imageSize.height / 60.0F *
                    CONVERT8WIDTH8TO8HEIGHT(
                        largeObjectScale *
                        (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                        tileUnitsWidth);
            }

            auto tileWidth{viewWidth - 2 * kMargin.x -
                           static_cast<float>(tileUnitsWidth - yPos) /
                               tileUnitsWidth * viewWidth * 0.6F};
            auto tileLeft{1.0F - viewWidth + kMargin.x +
                          static_cast<float>(tileUnitsWidth - yPos) /
                              tileUnitsWidth * viewWidth * 0.3F};

            auto baseX{tileLeft +
                       static_cast<float>(xPos) / tileUnitsWidth * tileWidth};
            auto baseY{0.75F + kMargin.y +
                       static_cast<float>(yPos + 1) / tileUnitsWidth *
                           (0.25F - 2 * kMargin.y)};

            auto imageX{baseX - imageWidth / 2.0F};
            auto imageY{baseY - imageHeight};

            auto renderOffset{
                _<OBJECT8INDEX>().GET8FIRST8PERSON8VIEW8RENDER8OFFSET(
                    objectType)};

            imageX += renderOffset.x * tileWidth;

            constexpr auto kTileHeight{0.25F};

            imageY += renderOffset.y * kTileHeight;

            auto impactPointWidth{GAME8PROPERTIES::mkImpactPointWidth};
            auto impactPointHeight{CONVERT8WIDTH8TO8HEIGHT(impactPointWidth)};

            auto &impactPoints{object->mImpactPoints};

            auto completedImpactPointThisClick{false};

            for (auto &impactPoint : impactPoints) {
                auto impactPointCenterX{imageX +
                                        impactPoint.position.x * imageWidth};
                auto impactPointCenterY{imageY +
                                        impactPoint.position.y * imageHeight};

                auto impactPointX{impactPointCenterX - impactPointWidth / 2.0F};
                auto impactPointY{impactPointCenterY -
                                  impactPointHeight / 2.0F};

                auto rect{RECT8F{impactPointX, impactPointY, impactPointWidth,
                                 impactPointHeight}};

                if (rect.CONTAINS(mousePosition) && !impactPoint.completed) {
                    impactPoint.completed = true;

                    completedImpactPointThisClick = true;

                    _<PLAYER>().mTicksLastImpact = now;

                    _<FIRST8PERSON8VIEW>().completedObjectImpacts_.push_back(
                        {POINT8F{impactPointCenterX, impactPointCenterY}, now});

                    impactAction->singleImpactPointCompletedAction();
                }
            }

            if (!completedImpactPointThisClick)
                continue;

            auto allImpactPointsCompleted{!impactPoints.empty()};

            for (auto &impactPoint : impactPoints) {
                if (!impactPoint.completed) {
                    allImpactPointsCompleted = false;
                    break;
                }
            }

            if (allImpactPointsCompleted)
                impactAction->allImpactPointsCompletedAction(object);
        }
    }
}