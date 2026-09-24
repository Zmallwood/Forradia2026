/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "Combat.hpp"
#include "Core/Assets/ImageBank.hpp"
#include "Core/Configuration/GameProperties.hpp"
#include "Core/CoreGameObjects/Player.hpp"
#include "Core/WorldStructure/Creature.hpp"
#include "Core/WorldStructure/Tile.hpp"
#include "Core/WorldStructure/TileObjects.hpp"
#include "Core/WorldStructure/World.hpp"
#include "Core/WorldStructure/WorldArea.hpp"

namespace Forradia
{
    void Combat::OnMouseDown(Uint8 button)
    {
        auto viewWidth{GameProperties::k_viewWidth_};

        auto now{Now()};

        if (now - _<Player>().ticksLastHitOnOther_ <
            InvertSpeed(_<Player>().attackSpeed_))
        {
            return;
        }

        auto mousePosition{GetMousePosition()};

        if (mousePosition.x < viewWidth / 2.0f)
        {
            return;
        }

        auto worldArea{_<World>().currentWorldArea_};

        auto facedTile{_<Player>().facedTile_};

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

        constexpr auto k_margin{GameProperties::k_firstPersonViewMargin_};
        constexpr auto k_largeObjectScale{GameProperties::k_largeObjectScale_};

        auto creatureType{creature->type_};

        auto imageSize{_<ImageBank>().GetImageSize(creatureType)};

        auto imageWidth{imageSize.width / 60.0f * k_largeObjectScale};
        auto imageHeight{imageSize.height / 60.0f *
                         ConvertWidthToHeight(k_largeObjectScale)};

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

        auto isPixelVisible{_<ImageBank>().IsPixelVisible(creatureType, x, y)};

        if (!isPixelVisible)
        {
            return;
        }

        creature->Hit(1, PointF{x, y});

        _<Player>().ticksLastHitOnOther_ = now;

        tile->tileObjects_->AddObject("ObjectPoolOfBlood");
    }
}