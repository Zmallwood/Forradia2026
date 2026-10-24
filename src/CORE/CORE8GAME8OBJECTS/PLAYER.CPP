//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "PLAYER.HPP"
#include "CORE/CONFIGURATION/GAME8PROPERTIES.HPP"
#include "CORE/GUI8CORE/GUI8TEXT8CONSOLE.HPP"
#include "CORE/WORLD8STRUCTURE/TILE.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD8AREA.HPP"
#include "PLAYER8EQUIPMENT.HPP"
#include "PLAYER8INVENTORY.HPP"
#include "DEFAULT8THEME/SCENES/WORLD8GENERATION/SUB/SUB/STARTING8AREA8GENERATOR.HPP"

namespace FORRADIA8GAME {
    PLAYER::PLAYER()
        : mPlayerInventory(std::make_shared<PLAYER8INVENTORY>()),
          mPlayerEquipment(std::make_shared<PLAYER8EQUIPMENT>()) {
        mPlayerInventory->ADD8OBJECT("ObjectRedApple");
        mPlayerInventory->ADD8OBJECT("ObjectCopperSword");
        mPlayerInventory->ADD8OBJECT("ObjectWoodAxe");
        mPlayerInventory->ADD8OBJECT("ObjectSaw");
        mPlayerInventory->ADD8OBJECT("ObjectHammer");
        mPlayerInventory->ADD8OBJECT("ObjectFlintAndSteel");
    }

    void
    PLAYER::SPAWN8ONSUITABLE8LOCATION() {
        auto worldArea{_<WORLD>().currentWorldArea_};

        auto worldAreaSize{worldArea->GET8SIZE()};

        auto roadNetworkCenter{_<STARTING8AREA8GENERATOR>().roadNetworkCenter_};

        mPosition = {static_cast<float>(roadNetworkCenter.x) + 0.5F,
                     static_cast<float>(roadNetworkCenter.y) + 0.5F};

        auto tile{worldArea->GET8TILE(static_cast<int>(mPosition.x),
                                      static_cast<int>(mPosition.y))};

        while (tile->ground_ == HASH("GroundWater")) {
            mPosition = {4.0F + (rand() % (worldAreaSize.width - 5)),
                         4.0F + (rand() % (worldAreaSize.height - 5))};

            tile = worldArea->GET8TILE(static_cast<int>(mPosition.x),
                                       static_cast<int>(mPosition.y));
        }

        mFacedTileCoordinate = {static_cast<int>(mPosition.x),
                                static_cast<int>(mPosition.y) + 1};
    }

    void
    PLAYER::MOVE8NORTH() {
        auto newX{mPosition.x};
        auto newY{mPosition.y - mStepSize};

        auto newTile{_<WORLD>().currentWorldArea_->GET8TILE(
            {static_cast<int>(newX), static_cast<int>(newY)})};

        if (newTile &&
            (newTile->ground_ == HASH("GroundWater") || newTile->creature_))
            return;

        mPosition = {newX, newY};

        mFacedTileCoordinate = {static_cast<int>(mPosition.x),
                                static_cast<int>(mPosition.y) - 1};

        mFacingDirection = WORLD8DIRECTIONS::North;
    }

    void
    PLAYER::MOVE8EAST() {
        auto newX{mPosition.x + mStepSize};
        auto newY{mPosition.y};

        auto newTile{_<WORLD>().currentWorldArea_->GET8TILE(
            {static_cast<int>(newX), static_cast<int>(newY)})};

        if (newTile &&
            (newTile->ground_ == HASH("GroundWater") || newTile->creature_))
            return;

        mPosition = {newX, newY};

        mFacedTileCoordinate = {static_cast<int>(mPosition.x) + 1,
                                static_cast<int>(mPosition.y)};

        mFacingDirection = WORLD8DIRECTIONS::East;
    }

    void
    PLAYER::MOVE8SOUTH() {
        auto newX{mPosition.x};
        auto newY{mPosition.y + mStepSize};

        auto newTile{_<WORLD>().currentWorldArea_->GET8TILE(
            {static_cast<int>(newX), static_cast<int>(newY)})};

        if (newTile &&
            (newTile->ground_ == HASH("GroundWater") || newTile->creature_))
            return;

        mPosition = {newX, newY};

        mFacedTileCoordinate = {static_cast<int>(mPosition.x),
                                static_cast<int>(mPosition.y) + 1};

        mFacingDirection = WORLD8DIRECTIONS::South;
    }

    void
    PLAYER::MOVE8WEST() {
        auto newX{mPosition.x - mStepSize};
        auto newY{mPosition.y};

        auto newTile{_<WORLD>().currentWorldArea_->GET8TILE(
            {static_cast<int>(newX), static_cast<int>(newY)})};

        if (newTile &&
            (newTile->ground_ == HASH("GroundWater") || newTile->creature_))
            return;

        mPosition = {newX, newY};

        mFacedTileCoordinate = {static_cast<int>(mPosition.x) - 1,
                                static_cast<int>(mPosition.y)};

        mFacingDirection = WORLD8DIRECTIONS::West;
    }

    void
    PLAYER::TURN8NORTH() {
        mFacedTileCoordinate = {static_cast<int>(mPosition.x),
                                static_cast<int>(mPosition.y) - 1};

        mFacingDirection = WORLD8DIRECTIONS::North;
    }

    void
    PLAYER::TURN8EAST() {
        mFacedTileCoordinate = {static_cast<int>(mPosition.x) + 1,
                                static_cast<int>(mPosition.y)};

        mFacingDirection = WORLD8DIRECTIONS::East;
    }

    void
    PLAYER::TURN8SOUTH() {
        mFacedTileCoordinate = {static_cast<int>(mPosition.x),
                                static_cast<int>(mPosition.y) + 1};

        mFacingDirection = WORLD8DIRECTIONS::South;
    }

    void
    PLAYER::TURN8WEST() {
        mFacedTileCoordinate = {static_cast<int>(mPosition.x) - 1,
                                static_cast<int>(mPosition.y)};

        mFacingDirection = WORLD8DIRECTIONS::West;
    }

    void
    PLAYER::ADD8EXPERIENCE(int amount) {
        mExperience += amount;

        _<GUI8TEXT8CONSOLE>().PRINT8LINE(
            "You gained " + std::to_string(amount) + " experience points.");
    }

    void
    PLAYER::HIT(float damage) {
        mHealth -= damage;

        mTicksLastHitOnSelf = NOW();

        std::stringstream ssDamage;

        ssDamage << std::fixed << std::setprecision(1) << damage;

        _<GUI8TEXT8CONSOLE>().PRINT8LINE("You took " + ssDamage.str() +
                                         " damage.");
    }
}