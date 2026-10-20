// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CORE/ASSETS/IMAGE8BANK.HPP"
#include "CORE/CONFIGURATION/GAME8PROPERTIES.HPP"
#include "CORE/CONFIGURATION/OBJECT8INDEX.HPP"
#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"
#include "CORE/CORE_GAME_OBJECTS/PLAYER8EQUIPMENT.HPP"
#include "CORE/RENDERING/COLORS/COLOR8RENDERER.HPP"
#include "CORE/RENDERING/IMAGES/IMAGE8RENDERER.HPP"
#include "CORE/SDL8DEVICE/SDL8DEVICE.HPP"
#include "CORE/WORLD8STRUCTURE/CREATURE.HPP"
#include "CORE/WORLD8STRUCTURE/NPC.HPP"
#include "CORE/WORLD8STRUCTURE/OBJECT.HPP"
#include "CORE/WORLD8STRUCTURE/TILE.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD8AREA.HPP"
#include "FIRST_PERSON_VIEW.HPP"
#include "FIRST_PERSON_VIEW_FUNCTIONS.HPP"

void
FirstPersonView::Update()
{
    auto now = NOW();

    for (auto it = completedObjectImpacts_.begin();
         it != completedObjectImpacts_.end();)
    {
        if (now > it->ticksCompleted + kImpactPointEffectDuration_)
        {
            it = completedObjectImpacts_.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void
FirstPersonView::Render()
{
    _<SDL8DEVICE>().CLIP(0.5f, 0.0f, 0.5f, 1.0f);

    auto viewWidth = GAME8PROPERTIES::kViewWidth_;

    _<COLOR8RENDERER>().FILL8RECT(1.0f - viewWidth, 0.0f, viewWidth, 1.0f,
                                  COLORS::kVeryDarkBlue);

    auto now = NOW();

    std::string groundImageName;

    auto worldArea = _<WORLD>().currentWorldArea_;
    auto facedTile = worldArea->GET8TILE(_<PLAYER>().facedTileCoordinate_);

    if (!facedTile)
    {
        return;
    }

    auto rightHandObject = _<PLAYER>().playerEquipment_->rightHandObject_;
    auto leftHandObject = _<PLAYER>().playerEquipment_->leftHandObject_;

    auto groundType = facedTile->ground_;

    switch (groundType)
    {
    case HASH("GroundGrass"):
    {
        groundImageName = "GroundFirstPersonGrass";

        break;
    }
    case HASH("GroundWater"):
    {
        auto waterAnimIndex = (NOW() % 450) / 150;

        groundImageName =
            "GroundFirstPersonWater_" + std::to_string(waterAnimIndex);

        break;
    }
    case HASH("GroundDirt"):
    {
        groundImageName = "GroundFirstPersonDirt";

        break;
    }
    case HASH("GroundRock"):
    {
        groundImageName = "GroundFirstPersonRock";

        break;
    }
    case HASH("GroundCobblestone"):
    {
        groundImageName = "GroundFirstPersonCobblestone";

        break;
    }
    case HASH("GroundWoodFloor"):
    {
        groundImageName = "GroundFirstPersonWoodFloor";

        break;
    }
    }

    constexpr auto kMargin = GAME8PROPERTIES::kFirstPersonViewMargin_;

    _<IMAGE8RENDERER>().DRAW8IMAGE(
        groundImageName, 1.0f - viewWidth + kMargin.x, 0.75f + kMargin.y,
        viewWidth - 2 * kMargin.x, 0.25f - 2 * kMargin.y);

    auto tileUnitsWidth = _<GAME8PROPERTIES>().kTileUnitsWidth_;

    auto orderedObjects = GetOrderedObjects();

    constexpr auto largeObjectScale = GAME8PROPERTIES::kLargeObjectScale_;
    constexpr auto smallObjectScale = GAME8PROPERTIES::kSmallObjectScale_;

    for (auto entry : orderedObjects)
    {
        auto xPos = entry.second.position_.x;
        auto yPos = entry.second.position_.y;

        if (yPos * tileUnitsWidth + xPos >= tileUnitsWidth * tileUnitsWidth / 2)
        {
            break;
        }

        auto objectType = entry.second.object_->type_;

        auto imageSize = _<IMAGE8BANK>().GET8IMAGE8SIZE(objectType);

        float imageWidth;
        float imageHeight;

        auto isSmallObject = _<OBJECT8INDEX>().IS8SMALL8OBJECT(objectType);

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

        auto tileWidth = viewWidth - 2 * kMargin.x -
                         static_cast<float>(tileUnitsWidth - yPos) /
                             tileUnitsWidth * viewWidth * 0.6f;
        auto tileLeft = 1.0f - viewWidth + kMargin.x +
                        static_cast<float>(tileUnitsWidth - yPos) /
                            tileUnitsWidth * viewWidth * 0.3f;

        auto baseX =
            tileLeft + static_cast<float>(xPos) / tileUnitsWidth * tileWidth;
        auto baseY = 0.75f + kMargin.y +
                     static_cast<float>(yPos + 1) / tileUnitsWidth *
                         (0.25f - 2 * kMargin.y);

        auto imageX = baseX - imageWidth / 2.0f;
        auto imageY = baseY - imageHeight;

        auto renderOffset =
            _<OBJECT8INDEX>().GET8FIRST8PERSON8VIEW8RENDER8OFFSET(objectType);

        imageX += renderOffset.x * tileWidth;

        constexpr auto kTileHeight{0.25f};

        imageY += renderOffset.y * kTileHeight;

        _<IMAGE8RENDERER>().DRAW8IMAGE(objectType, imageX, imageY, imageWidth,
                                       imageHeight);

        auto impactObjects = _<OBJECT8INDEX>().GET8IMPACT8OBJECTS(objectType);

        auto canImpact = false;

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

        if (canImpact)
        {
            auto impactPoints = entry.second.object_->impactPoints_;

            for (auto impactPoint : impactPoints)
            {
                auto impactPointWidth = GAME8PROPERTIES::kImpactPointWidth_;
                auto impactPointHeight =
                    CONVERT8WIDTH8TO8HEIGHT(impactPointWidth);
                auto impactPointX = imageX +
                                    impactPoint.position.x * imageWidth -
                                    impactPointWidth / 2.0f;
                auto impactPointY = imageY +
                                    impactPoint.position.y * imageHeight -
                                    impactPointHeight / 2.0f;

                auto color =
                    impactPoint.completed ? COLORS::kGreen : COLORS::kRed;

                _<COLOR8RENDERER>().FILL8RECT(impactPointX, impactPointY,
                                              impactPointWidth,
                                              impactPointHeight, color);
            }
        }
    }

    auto npc = facedTile->npc_;

    if (npc)
    {
        auto npcType = npc->type_;

        auto imageSize = _<IMAGE8BANK>().GET8IMAGE8SIZE(npcType);

        auto imageWidth = imageSize.width / 60.0f * largeObjectScale;
        auto imageHeight = imageSize.height / 60.0f *
                           CONVERT8WIDTH8TO8HEIGHT(largeObjectScale);

        auto tileWidth = viewWidth - 2 * kMargin.x - 0.5f * viewWidth * 0.6f;
        auto tileLeft = 1.0f - viewWidth + kMargin.x + 0.5f * viewWidth * 0.3f;

        auto baseX = tileLeft + 0.5f * tileWidth;
        auto baseY = 0.75f + kMargin.y + 0.5f * (0.25f - 2 * kMargin.y);

        auto imageX = baseX - imageWidth / 2.0f;
        auto imageY = baseY - imageHeight;

        _<IMAGE8RENDERER>().DRAW8IMAGE(npcType, imageX, imageY, imageWidth,
                                       imageHeight);
    }

    auto creature = facedTile->creature_;

    if (creature)
    {
        auto creatureType = creature->type_;

        auto imageSize = _<IMAGE8BANK>().GET8IMAGE8SIZE(creatureType);

        auto imageWidth = imageSize.width / 60.0f * largeObjectScale;
        auto imageHeight = imageSize.height / 60.0f *
                           CONVERT8WIDTH8TO8HEIGHT(largeObjectScale);

        auto tileWidth = viewWidth - 2 * kMargin.x - 0.5f * viewWidth * 0.6f;
        auto tileLeft = 1.0f - viewWidth + kMargin.x + 0.5f * viewWidth * 0.3f;

        auto baseX = tileLeft + 0.5f * tileWidth;
        auto baseY = 0.75f + kMargin.y + 0.5f * (0.25f - 2 * kMargin.y);

        auto imageX = baseX - imageWidth / 2.0f;
        auto imageY = baseY - imageHeight;

        _<IMAGE8RENDERER>().DRAW8IMAGE(creatureType, imageX, imageY, imageWidth,
                                       imageHeight);

        if (now - creature->ticksLastHitOnSelf_ < kHitOtherEffectDuration_)
        {
            auto lastHitPosition = creature->lastHitPosition_;

            auto hitEffectImageSize =
                _<IMAGE8BANK>().GET8IMAGE8SIZE(HASH("HitEffect"));

            constexpr auto kHitEffectScale = 0.1f;

            auto hitEffectWidth =
                hitEffectImageSize.width / 60.0f * kHitEffectScale;
            auto hitEffectHeight = hitEffectImageSize.height / 60.0f *
                                   CONVERT8WIDTH8TO8HEIGHT(kHitEffectScale);

            auto hitEffectBaseX = imageX + lastHitPosition.x * imageWidth;
            auto hitEffectBaseY = imageY + lastHitPosition.y * imageHeight;

            auto hitEffectX = hitEffectBaseX - hitEffectWidth / 2.0f;
            auto hitEffectY = hitEffectBaseY - hitEffectHeight / 2.0f;

            _<IMAGE8RENDERER>().DRAW8IMAGE("HitEffect", hitEffectX, hitEffectY,
                                           hitEffectWidth, hitEffectHeight);
        }
    }

    for (auto entry : orderedObjects)
    {
        auto xPos = entry.second.position_.x;
        auto yPos = entry.second.position_.y;

        if (yPos * tileUnitsWidth + xPos < tileUnitsWidth * tileUnitsWidth / 2)
        {
            continue;
        }

        auto objectType = entry.second.object_->type_;

        auto imageSize = _<IMAGE8BANK>().GET8IMAGE8SIZE(objectType);

        float imageWidth;
        float imageHeight;

        auto isSmallObject = _<OBJECT8INDEX>().IS8SMALL8OBJECT(objectType);

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

        auto tileWidth = viewWidth - 2 * kMargin.x -
                         static_cast<float>(tileUnitsWidth - yPos) /
                             tileUnitsWidth * viewWidth * 0.6f;
        auto tileLeft = 1.0f - viewWidth + kMargin.x +
                        static_cast<float>(tileUnitsWidth - yPos) /
                            tileUnitsWidth * viewWidth * 0.3f;

        auto baseX =
            tileLeft + static_cast<float>(xPos) / tileUnitsWidth * tileWidth;
        auto baseY = 0.75f + kMargin.y +
                     static_cast<float>(yPos + 1) / tileUnitsWidth *
                         (0.25f - 2 * kMargin.y);

        auto imageX = baseX - imageWidth / 2.0f;
        auto imageY = baseY - imageHeight;

        auto renderOffset =
            _<OBJECT8INDEX>().GET8FIRST8PERSON8VIEW8RENDER8OFFSET(objectType);

        imageX += renderOffset.x * tileWidth;

        constexpr auto kTileHeight = 0.25f;

        imageY += renderOffset.y * kTileHeight;

        _<IMAGE8RENDERER>().DRAW8IMAGE(objectType, imageX, imageY, imageWidth,
                                       imageHeight);

        auto impactObjects = _<OBJECT8INDEX>().GET8IMPACT8OBJECTS(objectType);

        auto canImpact = false;

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

        if (canImpact)
        {
            auto impactPoints = entry.second.object_->impactPoints_;

            for (auto impactPoint : impactPoints)
            {
                auto impactPointWidth = GAME8PROPERTIES::kImpactPointWidth_;
                auto impactPointHeight =
                    CONVERT8WIDTH8TO8HEIGHT(impactPointWidth);
                auto impactPointX = imageX +
                                    impactPoint.position.x * imageWidth -
                                    impactPointWidth / 2.0f;
                auto impactPointY = imageY +
                                    impactPoint.position.y * imageHeight -
                                    impactPointHeight / 2.0f;

                auto color =
                    impactPoint.completed ? COLORS::kGreen : COLORS::kRed;

                _<COLOR8RENDERER>().FILL8RECT(impactPointX, impactPointY,
                                              impactPointWidth,
                                              impactPointHeight, color);
            }
        }
    }

    for (auto completedObjectImpact : completedObjectImpacts_)
    {
        if (now - completedObjectImpact.ticksCompleted <
            kImpactPointEffectDuration_)
        {
            auto hitEffectImageSize =
                _<IMAGE8BANK>().GET8IMAGE8SIZE(HASH("HitEffect"));

            constexpr auto kHitEffectScale = 0.1f;

            auto hitEffectWidth =
                hitEffectImageSize.width / 60.0f * kHitEffectScale;
            auto hitEffectHeight = hitEffectImageSize.height / 60.0f *
                                   CONVERT8WIDTH8TO8HEIGHT(kHitEffectScale);

            auto impactPointX = completedObjectImpact.position.x;
            auto impactPointY = completedObjectImpact.position.y;

            auto hitEffectX = impactPointX - hitEffectWidth / 2.0f;
            auto hitEffectY = impactPointY - hitEffectHeight / 2.0f;

            _<IMAGE8RENDERER>().DRAW8IMAGE("HitEffect", hitEffectX, hitEffectY,
                                           hitEffectWidth, hitEffectHeight);
        }
    }

    constexpr auto kHandScale = 0.1f;

    auto handWidth = kHandScale;
    auto handHeight = CONVERT8WIDTH8TO8HEIGHT(kHandScale * 6 / 4);
    auto handSpacing = 0.1f;

    auto leftHandX =
        1.0f - viewWidth + 0.5f * viewWidth - handSpacing - handWidth / 2;
    auto rightHandX =
        1.0f - viewWidth + 0.5f * viewWidth + handSpacing - handWidth / 2;

    auto ticksLastMovement = _<PLAYER>().ticksLastMovement_;

    auto ticksOneStep = INVERT8SPEED(_<PLAYER>().movementSpeed_);

    auto delta = NOW() - ticksLastMovement;

    auto handAnimation = 0.0f;

    if (delta < ticksOneStep)
    {
        handAnimation =
            std::sin(static_cast<float>(delta) / ticksOneStep * M_PI) * 0.02f;
    }

    auto handYOffset = 0.07f;

    auto handY = 1.0f - handHeight + handYOffset + handAnimation;

    if (rightHandObject)
    {
        auto imageSize = _<IMAGE8BANK>().GET8IMAGE8SIZE(rightHandObject->type_);

        auto imageWidth = imageSize.width / 60.0f * kWieldedObjectScale_;
        auto imageHeight = imageSize.height / 60.0f *
                           CONVERT8WIDTH8TO8HEIGHT(kWieldedObjectScale_);

        auto rightHandX = 1.0f - viewWidth + 0.5f * viewWidth + handSpacing -
                          imageWidth / 2.0f;
        auto rightHandY = handY - imageHeight / 2.0f;

        _<IMAGE8RENDERER>().DRAW8IMAGE(rightHandObject->type_, rightHandX,
                                       rightHandY, imageWidth, imageHeight,
                                       kHandsOpacity_);
    }

    if (leftHandObject)
    {
        auto imageSize = _<IMAGE8BANK>().GET8IMAGE8SIZE(leftHandObject->type_);

        auto imageWidth = imageSize.width / 60.0f * kWieldedObjectScale_;
        auto imageHeight = imageSize.height / 60.0f *
                           CONVERT8WIDTH8TO8HEIGHT(kWieldedObjectScale_);

        auto leftHandX = 1.0f - viewWidth + 0.5f * viewWidth - handSpacing -
                         imageWidth / 2.0f;
        auto leftHandY = handY - imageHeight / 2.0f;

        _<IMAGE8RENDERER>().DRAW8IMAGE(leftHandObject->type_, leftHandX,
                                       leftHandY, imageWidth, imageHeight,
                                       kHandsOpacity_, true);
    }

    _<IMAGE8RENDERER>().DRAW8IMAGE("HandLeft", leftHandX, handY, handWidth,
                                   handHeight, kHandsOpacity_);
    _<IMAGE8RENDERER>().DRAW8IMAGE("HandRight", rightHandX, handY, handWidth,
                                   handHeight, kHandsOpacity_);

    _<COLOR8RENDERER>().DRAW8LINE(viewWidth, 0.0f, viewWidth, 1.0f,
                                  COLORS::kWhite);

    if (now < _<PLAYER>().ticksLastHitOnSelf_ + kHitSelfEffectDuration_)
    {
        _<COLOR8RENDERER>().FILL8RECT(viewWidth, 0.0f, viewWidth, 1.0f,
                                      COLORS::kRed);
    }

    if (now <
        _<PLAYER>().ticksLastImpact_ + INVERT8SPEED(_<PLAYER>().impactSpeed_))
    {
        constexpr auto kImpactReloadWidth = 0.1f;
        constexpr auto kImpactReloadHeight = 0.01f;

        auto progress = static_cast<float>(now - _<PLAYER>().ticksLastImpact_) /
                        INVERT8SPEED(_<PLAYER>().impactSpeed_);

        auto filledWidth = kImpactReloadWidth * (1.0f - progress);

        auto x = 1.0f - viewWidth + 0.25f - kImpactReloadWidth / 2;
        auto y = 0.5f - kImpactReloadHeight / 2;

        _<COLOR8RENDERER>().FILL8RECT(x, y, kImpactReloadWidth,
                                      kImpactReloadHeight, COLORS::kBlack);

        _<COLOR8RENDERER>().FILL8RECT(x, y, filledWidth, kImpactReloadHeight,
                                      COLORS::kGold);
    }

    _<SDL8DEVICE>().RESET8CLIP();
}