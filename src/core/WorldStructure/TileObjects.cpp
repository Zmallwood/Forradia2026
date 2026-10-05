// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "TileObjects.hpp"
#include "Core/Configuration/GameProperties.hpp"
#include "Object.hpp"

void TileObjects::Clear()
{
    objects_.clear();
}

void TileObjects::AddObject(int objectType, Point position)
{
    if (position.x == -1 || position.y == -1)
    {
        position.x = rand() % _<GameProperties>().k_tileUnitsWidth_;
        position.y = rand() % _<GameProperties>().k_tileUnitsWidth_;
    }

    objects_.insert({position, std::make_shared<Object>(objectType)});
}

void TileObjects::AddObject(std::string_view objectName, Point position)
{
    AddObject(Hash(objectName), position);
}

void TileObjects::AddObject(std::shared_ptr<Object> object, Point position)
{
    objects_.insert({position, object});
}

int TileObjects::Count()
{
    return objects_.size();
}

std::shared_ptr<Object> TileObjects::PickObject(std::shared_ptr<Object> object)
{
    for (auto it = objects_.begin(); it != objects_.end(); ++it)
    {
        if (it->second == object)
        {
            objects_.erase(it);

            return object;
        }
    }

    return nullptr;
}

void TileObjects::TransformObject(std::shared_ptr<Object> object,
                                  std::string_view newObjectType)
{
    Point position{-1, -1};

    for (auto it = objects_.begin(); it != objects_.end(); ++it)
    {
        if (it->second == object)
        {
            position = it->first;

            objects_.erase(it);

            break;
        }
    }

    if (position != Point{-1, -1})
    {
        AddObject(newObjectType, position);
    }
}

void TileObjects::RemoveObject(std::shared_ptr<Object> object)
{
    for (auto it = objects_.begin(); it != objects_.end(); ++it)
    {
        if (it->second == object)
        {
            objects_.erase(it);

            return;
        }
    }
}