// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CORE/ASSETS/IMAGE8BANK.HPP"
#include "CORE/CONFIGURATION/CREATURE8INDEX.HPP"
#include "CORE/CONFIGURATION/GAME8PROPERTIES.HPP"
#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"
#include "CORE/GUI8CORE/GUI_TEXT_CONSOLE.HPP"
#include "CORE/WORLD8STRUCTURE/CREATURE.HPP"
#include "CORE/WORLD8STRUCTURE/TILE.HPP"
#include "CORE/WORLD8STRUCTURE/TILE_OBJECTS.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD_AREA.HPP"
#include "CREATURE_RESPAWNER.HPP"
#include "PLAYER_COMBAT_TO_OTHERS.HPP"

void PlayerCombatToOthers::OnMouseDown(Uint8 button)
{
    auto viewWidth{GAME8PROPERTIES::k_viewWidth_};

    auto tileUnitsWidth{_<GAME8PROPERTIES>().k_tileUnitsWidth_};

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

    auto worldArea{_<World>().currentWorldArea_};

    auto facedTile{_<PLAYER>().facedTileCoordinate_};

    auto tile{worldArea->GetTile(facedTile)};

    if (!tile)
    {
        return;
    }

    auto creature{tile->creature_};

    if (!creature)
    {
        return;
    }

    if (creature->IsDead())
    {
        return;
    }

    constexpr auto k_margin{GAME8PROPERTIES::k_firstPersonViewMargin_};
    constexpr auto k_largeObjectScale{GAME8PROPERTIES::k_largeObjectScale_};

    auto creatureType{creature->type_};

    auto imageSize{_<IMAGE8BANK>().GET8IMAGE8SIZE(creatureType)};

    auto imageWidth{imageSize.width / 60.0f * k_largeObjectScale};
    auto imageHeight{imageSize.height / 60.0f *
                     CONVERT8WIDTH8TO8HEIGHT(k_largeObjectScale)};

    auto tileWidth{viewWidth - 2 * k_margin.x - 0.5f * viewWidth * 0.6f};
    auto tileLeft{1.0f - viewWidth + k_margin.x + 0.5f * viewWidth * 0.3f};

    auto baseX{tileLeft + 0.5f * tileWidth};
    auto baseY{0.75f + k_margin.y + 0.5f * (0.25f - 2 * k_margin.y)};

    auto imageX{baseX - imageWidth / 2.0f};
    auto imageY{baseY - imageHeight};

    auto dx{mousePosition.x - imageX};
    auto dy{mousePosition.y - imageY};

    auto x{dx / imageWidth};
    auto y{dy / imageHeight};

    auto isPixelVisible{_<IMAGE8BANK>().IS8PIXEL8VISIBLE(creatureType, x, y)};

    if (!isPixelVisible)
    {
        return;
    }

    creature->Hit(1.0f, POINT8F{x, y});

    _<PLAYER>().ticksLastHitOnOther_ = now;

    tile->tileObjects_->AddObject("ObjectPoolOfBlood");

    if (creature->IsDead())
    {
        auto corpseType{
            _<CREATURE8INDEX>().GET8CREATURE8CORPSE8TYPE(creatureType)};

        tile->tileObjects_->AddObject(corpseType,
                                      {tileUnitsWidth / 2, tileUnitsWidth / 2});

        tile->creature_ = nullptr;

        worldArea->creaturesMirror_.erase(creature);

        auto creatureLabel{
            _<CREATURE8INDEX>().GET8CREATURE8LABEL(creatureType)};

        _<GUITextConsole>().PrintLine("You have killed a " + creatureLabel +
                                      ".");

        _<PLAYER>().ADD8EXPERIENCE(creature->experienceValue_);

        _<CreatureRespawner>().RespawnCreature(creatureType,
                                               creature->respawnTimeMillis_);
    }
}