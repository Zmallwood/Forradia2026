//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "PLAYER8COMBAT8TO8OTHERS.HPP"
#include "CORE/ASSETS/IMAGE8BANK.HPP"
#include "CORE/CONFIGURATION/CREATURE8INDEX.HPP"
#include "CORE/CONFIGURATION/GAME8PROPERTIES.HPP"
#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"
#include "CORE/GUI8CORE/GUI8TEXT8CONSOLE.HPP"
#include "CORE/WORLD8STRUCTURE/CREATURE.HPP"
#include "CORE/WORLD8STRUCTURE/TILE.HPP"
#include "CORE/WORLD8STRUCTURE/TILE8OBJECTS.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD8AREA.HPP"
#include "CREATURE8RESPAWNER.HPP"

namespace FORRADIA8GAME
{
    void
    PLAYER8COMBAT8TO8OTHERS::ON8MOUSE8DOWN(Uint8 button)
    {
        auto viewWidth{GAME8PROPERTIES::kViewWidth_};

        auto tileUnitsWidth{_<GAME8PROPERTIES>().kTileUnitsWidth_};

        auto now{NOW()};

        if (now - _<PLAYER>().ticksLastHitOnOther_ <
            INVERT8SPEED(_<PLAYER>().attackSpeed_))
        {
            return;
        }

        auto mousePosition{GET8MOUSE8POSITION()};

        if (mousePosition.x < viewWidth / 2.0f)
        {
            return;
        }

        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTile{_<PLAYER>().facedTileCoordinate_};

        auto tile{worldArea->GET8TILE(facedTile)};

        if (!tile)
        {
            return;
        }

        auto creature{tile->creature_};

        if (!creature)
        {
            return;
        }

        if (creature->IS8DEAD())
        {
            return;
        }

        constexpr auto kMargin{GAME8PROPERTIES::kFirstPersonViewMargin_};
        constexpr auto kLargeObjectScale{GAME8PROPERTIES::kLargeObjectScale_};

        auto creatureType{creature->type_};

        auto imageSize{_<IMAGE8BANK>().GET8IMAGE8SIZE(creatureType)};

        auto imageWidth{imageSize.width / 60.0f * kLargeObjectScale};
        auto imageHeight{imageSize.height / 60.0f *
                         CONVERT8WIDTH8TO8HEIGHT(kLargeObjectScale)};

        auto tileWidth{viewWidth - 2 * kMargin.x - 0.5f * viewWidth * 0.6f};
        auto tileLeft{1.0f - viewWidth + kMargin.x + 0.5f * viewWidth * 0.3f};

        auto baseX{tileLeft + 0.5f * tileWidth};
        auto baseY{0.75f + kMargin.y + 0.5f * (0.25f - 2 * kMargin.y)};

        auto imageX{baseX - imageWidth / 2.0f};
        auto imageY{baseY - imageHeight};

        auto dx{mousePosition.x - imageX};
        auto dy{mousePosition.y - imageY};

        auto x{dx / imageWidth};
        auto y{dy / imageHeight};

        auto isPixelVisible{
            _<IMAGE8BANK>().IS8PIXEL8VISIBLE(creatureType, x, y)};

        if (!isPixelVisible)
        {
            return;
        }

        creature->HIT(1.0f, POINT8F{x, y});

        _<PLAYER>().ticksLastHitOnOther_ = now;

        tile->tileObjects_->ADD8OBJECT("ObjectPoolOfBlood");

        if (creature->IS8DEAD())
        {
            auto corpseType{
                _<CREATURE8INDEX>().GET8CREATURE8CORPSE8TYPE(creatureType)};

            tile->tileObjects_->ADD8OBJECT(
                corpseType, {tileUnitsWidth / 2, tileUnitsWidth / 2});

            tile->creature_ = nullptr;

            worldArea->creaturesMirror_.erase(creature);

            auto creatureLabel{
                _<CREATURE8INDEX>().GET8CREATURE8LABEL(creatureType)};

            _<GUI8TEXT8CONSOLE>().PRINT8LINE("You have killed a " +
                                             creatureLabel + ".");

            _<PLAYER>().ADD8EXPERIENCE(creature->experienceValue_);

            _<CREATURE8RESPAWNER>().RESPAWN8CREATURE(
                creatureType, creature->respawnTimeMillis_);
        }
    }
}