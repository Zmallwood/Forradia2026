//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "WORLD8VIEW.HPP"
#include "CORE/ASSETS/IMAGE8BANK.HPP"
#include "CORE/CONFIGURATION/GAME8PROPERTIES.HPP"
#include "CORE/CONFIGURATION/OBJECT8INDEX.HPP"
#include "CORE/CORE8GAME8OBJECTS/PLAYER.HPP"
#include "CORE/RENDERING/COLORS/COLOR8RENDERER.HPP"
#include "CORE/RENDERING/IMAGES/IMAGE8RENDERER.HPP"
#include "CORE/SDL8DEVICE/SDL8DEVICE.HPP"
#include "CORE/WORLD8STRUCTURE/CREATURE.HPP"
#include "CORE/WORLD8STRUCTURE/NPC.HPP"
#include "CORE/WORLD8STRUCTURE/OBJECT.HPP"
#include "CORE/WORLD8STRUCTURE/TILE.HPP"
#include "CORE/WORLD8STRUCTURE/TILE8OBJECTS.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD8AREA.HPP"
#include "DEFAULT8THEME/SCENES/MAIN/SUB/TILE8HOVERING.HPP"

namespace FORRADIA8GAME {
    void
    WORLD8VIEW::RENDER() {
        _<SDL8DEVICE>().CLIP(0.0F, 0.0F, 0.5F, 1.0F);

        auto viewWidth{GAME8PROPERTIES::mkViewWidth};

        _<COLOR8RENDERER>().FILL8RECT(0.0F, 0.0F, viewWidth, 1.0F,
                                      COLORS::kBlack);

        auto worldArea{_<WORLD>().currentWorldArea_};

        POINT playerPosition{static_cast<int>(_<PLAYER>().mPosition.x),
                             static_cast<int>(_<PLAYER>().mPosition.y)};

        auto playerXInt{static_cast<int>(_<PLAYER>().mPosition.x)};
        auto playerYInt{static_cast<int>(_<PLAYER>().mPosition.y)};

        auto playerMoveDx{_<PLAYER>().mPosition.x - playerPosition.x};
        auto playerMoveDy{_<PLAYER>().mPosition.y - playerPosition.y};

        auto playerTile{worldArea->GET8TILE(playerPosition)};

        auto playerElevation{0};

        if (playerTile)
            playerElevation = playerTile->elevation_;

        auto hoveredCoordinate{_<TILE8HOVERING>().hoveredCoordinate_};

        auto facedTile{_<PLAYER>().mFacedTileCoordinate};

        auto tileWidth{_<GAME8PROPERTIES>().mkTileWidth};
        auto tileHeight{CONVERT8WIDTH8TO8HEIGHT(tileWidth)};

        auto tileGridSize{GAME8PROPERTIES::mkTileGridSize};

        auto yOffset{_<GAME8PROPERTIES>().mkWorldViewYOffset};

        auto numGridRows{tileGridSize - 11};
        auto numGridColumns{tileGridSize - 11};

        auto playerLoopX{5};
        auto playerLoopY{5};

        for (auto y = -numGridRows; y < 11 + numGridRows; y++) {
            for (auto x = -numGridColumns; x < 11 + numGridColumns; x++) {
                auto xCoordinate{playerPosition.x - 5 + x};
                auto yCoordinate{playerPosition.y - 5 + y};

                if (!worldArea->IS8VALID8COORDINATE(xCoordinate, yCoordinate))
                    continue;

                auto tile{worldArea->GET8TILE(xCoordinate, yCoordinate)};

                auto elevation{tile->elevation_};

                POINT coordinateNorth{xCoordinate, yCoordinate - 1};
                POINT coordinateEast{xCoordinate + 1, yCoordinate};
                POINT coordinateSouth{xCoordinate, yCoordinate + 1};
                POINT coordinateWest{xCoordinate - 1, yCoordinate};

                POINT coordinateNorthEast{xCoordinate + 1, yCoordinate - 1};
                POINT coordinateSouthEast{xCoordinate + 1, yCoordinate + 1};
                POINT coordinateSouthWest{xCoordinate - 1, yCoordinate + 1};
                POINT coordinateNorthWest{xCoordinate - 1, yCoordinate - 1};

                auto elevationNorth{elevation};
                auto elevationEast{elevation};
                auto elevationSouth{elevation};
                auto elevationWest{elevation};

                auto elevationNorthEast{elevation};
                auto elevationSouthEast{elevation};
                auto elevationSouthWest{elevation};
                auto elevationNorthWest{elevation};

                if (worldArea->IS8VALID8COORDINATE(coordinateNorth))
                    elevationNorth =
                        worldArea->GET8TILE(coordinateNorth)->elevation_;

                if (worldArea->IS8VALID8COORDINATE(coordinateEast))
                    elevationEast =
                        worldArea->GET8TILE(coordinateEast)->elevation_;

                if (worldArea->IS8VALID8COORDINATE(coordinateSouth))
                    elevationSouth =
                        worldArea->GET8TILE(coordinateSouth)->elevation_;

                if (worldArea->IS8VALID8COORDINATE(coordinateWest))
                    elevationWest =
                        worldArea->GET8TILE(coordinateWest)->elevation_;

                if (worldArea->IS8VALID8COORDINATE(coordinateNorthEast))
                    elevationNorthEast =
                        worldArea->GET8TILE(coordinateNorthEast)->elevation_;

                if (worldArea->IS8VALID8COORDINATE(coordinateSouthEast))
                    elevationSouthEast =
                        worldArea->GET8TILE(coordinateSouthEast)->elevation_;

                if (worldArea->IS8VALID8COORDINATE(coordinateSouthWest))
                    elevationSouthWest =
                        worldArea->GET8TILE(coordinateSouthWest)->elevation_;

                if (worldArea->IS8VALID8COORDINATE(coordinateNorthWest))
                    elevationNorthWest =
                        worldArea->GET8TILE(coordinateNorthWest)->elevation_;

                auto tileX{0.25F - tileWidth / 2 + x * tileWidth / 2 -
                           y * tileWidth / 2 - playerMoveDx * tileWidth / 2 +
                           playerMoveDy * tileWidth / 2};

                auto tileYOriginal{0.5F - 5.5F * tileHeight +
                                   x * tileHeight / 2 + y * tileHeight / 2 +
                                   playerElevation * tileHeight / 4 -
                                   playerMoveDx * tileHeight / 2 -
                                   playerMoveDy * tileHeight / 2 + yOffset};

                auto tileY{tileYOriginal};

                tileY = tileYOriginal;

                auto ground{tile->ground_};

                for (auto i = 0; i < elevation; i++) {
                    if (ground == HASH("GroundRock"))
                        _<IMAGE8RENDERER>().DRAW8IMAGE(
                            "ElevationRock", tileX, tileY + tileHeight / 4,
                            tileWidth, tileHeight * 3 / 4);
                    else if (ground == HASH("GroundWater"))
                        _<IMAGE8RENDERER>().DRAW8IMAGE(
                            "ElevationWater", tileX, tileY + tileHeight / 4,
                            tileWidth, tileHeight * 3 / 4);
                    else
                        _<IMAGE8RENDERER>().DRAW8IMAGE(
                            "Elevation", tileX, tileY + tileHeight / 4,
                            tileWidth, tileHeight * 3 / 4);

                    if (i >= elevationNorth && i >= elevationNorthEast &&
                        i >= elevationEast)
                        _<IMAGE8RENDERER>().DRAW8IMAGE(
                            "ElevationEdgeRight", tileX, tileY + tileHeight / 4,
                            tileWidth, tileHeight * 3 / 4);

                    if (i >= elevationSouth && i >= elevationSouthWest &&
                        i >= elevationWest)
                        _<IMAGE8RENDERER>().DRAW8IMAGE(
                            "ElevationEdgeLeft", tileX, tileY + tileHeight / 4,
                            tileWidth, tileHeight * 3 / 4);

                    if (i >= elevationSouth && i >= elevationEast)
                        _<IMAGE8RENDERER>().DRAW8IMAGE(
                            "ElevationEdgeMiddle", tileX,
                            tileY + tileHeight / 4, tileWidth,
                            tileHeight * 3 / 4);

                    if (i >= elevationEast && i < elevationNorthEast)
                        _<IMAGE8RENDERER>().DRAW8IMAGE(
                            "ElevationEdgeRight", tileX, tileY + tileHeight / 4,
                            tileWidth, tileHeight * 3 / 4);

                    tileY -= tileHeight / 4;
                }

                if (ground == HASH("GroundWater")) {
                    auto waterAnimIndex{
                        ((NOW() + 10 * xCoordinate * yCoordinate) % 900) / 300};

                    std::string groundImageName{"GroundWater_" +
                                                std::to_string(waterAnimIndex)};

                    ground = HASH(groundImageName);
                }

                if (ground == HASH("GroundGrass")) {
                    auto grassIndex{((10 * xCoordinate * yCoordinate) % 900) /
                                    300};

                    std::string groundImageName{"GroundGrass_" +
                                                std::to_string(grassIndex)};

                    ground = HASH(groundImageName);
                }

                _<IMAGE8RENDERER>().DRAW8IMAGE(ground, tileX, tileY,
                                               tileWidth + kSmallValue,
                                               tileHeight + kSmallValue);

                auto roadOrientation{tile->roadOrientation_};

                switch (roadOrientation) {
                case ROAD8ORIENTATION::Horizontal:
                    _<IMAGE8RENDERER>().DRAW8IMAGE("RoadCobblestoneHorizontal",
                                                   tileX, tileY, tileWidth,
                                                   tileHeight);
                    break;
                case ROAD8ORIENTATION::Vertical:
                    _<IMAGE8RENDERER>().DRAW8IMAGE("RoadCobblestoneVertical",
                                                   tileX, tileY, tileWidth,
                                                   tileHeight);
                    break;
                case ROAD8ORIENTATION::CornerNorthEast:
                    _<IMAGE8RENDERER>().DRAW8IMAGE(
                        "RoadCobblestoneCornerNorthEast", tileX, tileY,
                        tileWidth, tileHeight);
                    break;
                case ROAD8ORIENTATION::CornerSouthEast:
                    _<IMAGE8RENDERER>().DRAW8IMAGE(
                        "RoadCobblestoneCornerSouthEast", tileX, tileY,
                        tileWidth, tileHeight);
                    break;
                case ROAD8ORIENTATION::CornerSouthWest:
                    _<IMAGE8RENDERER>().DRAW8IMAGE(
                        "RoadCobblestoneCornerSouthWest", tileX, tileY,
                        tileWidth, tileHeight);
                    break;
                case ROAD8ORIENTATION::CornerNorthWest:
                    _<IMAGE8RENDERER>().DRAW8IMAGE(
                        "RoadCobblestoneCornerNorthWest", tileX, tileY,
                        tileWidth, tileHeight);
                    break;
                case ROAD8ORIENTATION::TIntersectionNorth:
                    _<IMAGE8RENDERER>().DRAW8IMAGE(
                        "RoadCobblestoneTIntersectionNorth", tileX, tileY,
                        tileWidth, tileHeight);
                    break;
                case ROAD8ORIENTATION::TIntersectionSouth:
                    _<IMAGE8RENDERER>().DRAW8IMAGE(
                        "RoadCobblestoneTIntersectionSouth", tileX, tileY,
                        tileWidth, tileHeight);
                    break;
                case ROAD8ORIENTATION::TIntersectionEast:
                    _<IMAGE8RENDERER>().DRAW8IMAGE(
                        "RoadCobblestoneTIntersectionEast", tileX, tileY,
                        tileWidth, tileHeight);
                    break;
                case ROAD8ORIENTATION::TIntersectionWest:
                    _<IMAGE8RENDERER>().DRAW8IMAGE(
                        "RoadCobblestoneTIntersectionWest", tileX, tileY,
                        tileWidth, tileHeight);
                    break;
                case ROAD8ORIENTATION::CrossIntersection:
                    _<IMAGE8RENDERER>().DRAW8IMAGE(
                        "RoadCobblestoneCrossIntersection", tileX, tileY,
                        tileWidth, tileHeight);
                    break;
                case ROAD8ORIENTATION::Fill:
                    _<IMAGE8RENDERER>().DRAW8IMAGE("RoadCobblestoneFill", tileX,
                                                   tileY, tileWidth,
                                                   tileHeight);
                    break;
                }

                if (elevation != elevationNorth)
                    _<IMAGE8RENDERER>().DRAW8IMAGE("ElevationEdgeNorth", tileX,
                                                   tileY, tileWidth,
                                                   tileHeight);

                if (elevation != elevationEast)
                    _<IMAGE8RENDERER>().DRAW8IMAGE("ElevationEdgeEast", tileX,
                                                   tileY, tileWidth,
                                                   tileHeight);

                if (elevation != elevationSouth)
                    _<IMAGE8RENDERER>().DRAW8IMAGE("ElevationEdgeSouth", tileX,
                                                   tileY, tileWidth,
                                                   tileHeight);

                if (elevation != elevationWest)
                    _<IMAGE8RENDERER>().DRAW8IMAGE("ElevationEdgeWest", tileX,
                                                   tileY, tileWidth,
                                                   tileHeight);

                if (xCoordinate == facedTile.x && yCoordinate == facedTile.y)
                    _<IMAGE8RENDERER>().DRAW8IMAGE("FacedTile", tileX, tileY,
                                                   tileWidth, tileHeight);

                if (xCoordinate == hoveredCoordinate.x &&
                    yCoordinate == hoveredCoordinate.y)

                    _<IMAGE8RENDERER>().DRAW8IMAGE("HoveredTile", tileX, tileY,
                                                   tileWidth, tileHeight);

                auto objects{tile->tileObjects_->objects_};

                for (auto entry : objects) {
                    auto object{entry.second};

                    auto objectType{object->mType};

                    auto worldViewObjectType{
                        _<OBJECT8INDEX>().GET8WORLD8VIEW8OBJECT8TYPE(
                            objectType)};

                    auto usedObjectType{objectType};

                    if (worldViewObjectType != 0)
                        usedObjectType = worldViewObjectType;

                    auto isSmallObject{
                        _<OBJECT8INDEX>().IS8SMALL8OBJECT(usedObjectType)};

                    if (isSmallObject)
                        continue;

                    auto animationFrames{
                        _<OBJECT8INDEX>().GET8ANIMATION8FRAMES(usedObjectType)};

                    if (animationFrames) {
                        auto objectName{
                            _<OBJECT8INDEX>().GET8OBJECT8NAME(usedObjectType)};

                        auto animationIndex{
                            (NOW() / 2 + 10 * xCoordinate * yCoordinate) %
                            (animationFrames * 100) / 100};

                        std::string animationName{
                            objectName + "_" + std::to_string(animationIndex)};

                        usedObjectType = HASH(animationName);
                    }

                    auto imageSize{
                        _<IMAGE8BANK>().GET8IMAGE8SIZE(usedObjectType)};

                    auto objectWidth{imageSize.width / 60.0F * tileWidth};
                    auto objectHeight{imageSize.height / 60.0F * tileHeight};

                    auto renderOffset{
                        _<OBJECT8INDEX>().GET8WORLD8VIEW8RENDER8OFFSET(
                            objectType)};

                    auto objectX{tileX + tileWidth / 2 - objectWidth / 2 +
                                 renderOffset.x * tileWidth};
                    auto objectY{tileY + tileHeight / 2 - objectHeight +
                                 renderOffset.y * tileHeight};

                    _<IMAGE8RENDERER>().DRAW8IMAGE(usedObjectType, objectX,
                                                   objectY, objectWidth,
                                                   objectHeight);
                }

                auto npc{tile->npc_};

                if (npc) {
                    auto npcType{npc->mType};

                    auto imageSize{_<IMAGE8BANK>().GET8IMAGE8SIZE(npcType)};

                    auto npcWidth{imageSize.width / 60.0F * tileWidth};
                    auto npcHeight{imageSize.height / 60.0F * tileHeight};

                    auto npcX{tileX + tileWidth / 2 - npcWidth / 2};
                    auto npcY{tileY + tileHeight / 2 - npcHeight};

                    _<IMAGE8RENDERER>().DRAW8IMAGE(npcType, npcX, npcY,
                                                   npcWidth, npcHeight);
                }

                auto creature{tile->creature_};

                if (creature) {
                    auto creatureType{creature->mType};

                    auto imageSize{
                        _<IMAGE8BANK>().GET8IMAGE8SIZE(creatureType)};

                    auto creatureWidth{imageSize.width / 60.0F * tileWidth};
                    auto creatureHeight{imageSize.height / 60.0F * tileHeight};

                    auto creatureX{tileX + tileWidth / 2 - creatureWidth / 2};
                    auto creatureY{tileY + tileHeight / 2 - creatureHeight};

                    _<IMAGE8RENDERER>().DRAW8IMAGE(creatureType, creatureX,
                                                   creatureY, creatureWidth,
                                                   creatureHeight);
                }

                if (xCoordinate == static_cast<int>(_<PLAYER>().mPosition.x) &&
                    yCoordinate == static_cast<int>(_<PLAYER>().mPosition.y)) {
                    auto tileXPlayer{0.25F - tileWidth / 2 + 5 * tileWidth / 2 -
                                     5 * tileWidth / 2};

                    auto tileYPlayer{0.5F - 5.5F * tileHeight +
                                     5 * tileHeight / 2 + 5 * tileHeight / 2 +
                                     yOffset};

                    std::string imageName{"Player"};

                    auto isWalking{
                        NOW() < _<PLAYER>().mTicksLastMovement +
                                    INVERT8SPEED(_<PLAYER>().mMovementSpeed)};

                    if (isWalking) {
                        auto animIndex{(NOW() % (7 * 150)) / 150};

                        imageName =
                            "PlayerWalking_" + std::to_string(animIndex);
                    }

                    _<IMAGE8RENDERER>().DRAW8IMAGE(imageName, tileXPlayer,
                                                   tileYPlayer - tileHeight,
                                                   tileWidth, tileHeight);
                }
            }
        }

        _<IMAGE8RENDERER>().DRAW8IMAGE("Filter1", 0.0F, 0.0F, viewWidth, 1.0F,
                                       1.0F, false, SDL_BLENDMODE_MUL);

        _<SDL8DEVICE>().RESET8CLIP();
    }
}