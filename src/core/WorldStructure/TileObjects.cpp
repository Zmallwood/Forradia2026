/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "TileObjects.hpp"
#include "Core/Configuration/GameProperties.hpp"
#include "Object.hpp"

namespace Forradia
{
    void TileObjects::Clear()
    {
        objects_.clear();
    }

    void TileObjects::AddObject(std::string_view objectName, Point position)
    {
        if (position.x == -1 || position.y == -1)
        {
            position.x = rand() % _<GameProperties>().k_tileUnitsWidth_;
            position.y = rand() % _<GameProperties>().k_tileUnitsWidth_;
        }

        objects_.insert({position, std::make_shared<Object>(Hash(objectName))});
    }

    int TileObjects::Count()
    {
        return objects_.size();
    }
}