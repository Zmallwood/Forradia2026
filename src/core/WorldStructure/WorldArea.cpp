/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "WorldArea.hpp"
#include "Core/Configuration/GameProperties.hpp"
#include "Core/WorldStructure/Tile.hpp"

namespace Forradia
{
    WorldArea::WorldArea()
    {
        auto size{_<GameProperties>().k_worldAreaSize_};

        for (auto x = 0; x < size.width; x++)
        {
            tiles_.push_back(std::vector<std::shared_ptr<Tile>>());

            for (auto y = 0; y < size.height; y++)
            {
                tiles_.at(x).push_back(std::make_shared<Tile>());
            }
        }
    }

    Size WorldArea::GetSize()
    {
        auto width{static_cast<int>(tiles_.size())};
        auto height{0};

        if (width)
        {
            height = static_cast<int>(tiles_.at(0).size());
        }

        return {width, height};
    }

    bool WorldArea::IsValidCoordinate(int x, int y)
    {
        auto size{GetSize()};

        return x >= 0 && x < size.width && y >= 0 && y < size.height;
    }

    bool WorldArea::IsValidCoordinate(Point coordinate)
    {
        return IsValidCoordinate(coordinate.x, coordinate.y);
    }

    std::shared_ptr<Tile> WorldArea::GetTile(int x, int y)
    {
        if (IsValidCoordinate(x, y))
        {
            return tiles_.at(x).at(y);
        }

        return nullptr;
    }

    std::shared_ptr<Tile> WorldArea::GetTile(Point coordinate)
    {
        return GetTile(coordinate.x, coordinate.y);
    }
}