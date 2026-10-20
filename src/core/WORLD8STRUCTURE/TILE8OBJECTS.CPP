//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "CORE/CONFIGURATION/GAME8PROPERTIES.HPP"
#include "OBJECT.HPP"
#include "TILE8OBJECTS.HPP"

void
TILE8OBJECTS::CLEAR()
{
    objects_.clear();
}

void
TILE8OBJECTS::ADD8OBJECT(int objectType, POINT position)
{
    if (position.x == -1 || position.y == -1)
    {
        position.x = rand() % _<GAME8PROPERTIES>().kTileUnitsWidth_;
        position.y = rand() % _<GAME8PROPERTIES>().kTileUnitsWidth_;
    }

    objects_.insert({position, std::make_shared<OBJECT>(objectType)});
}

void
TILE8OBJECTS::ADD8OBJECT(std::string_view objectName, POINT position)
{
    ADD8OBJECT(HASH(objectName), position);
}

void
TILE8OBJECTS::ADD8OBJECT(std::shared_ptr<OBJECT> object, POINT position)
{
    objects_.insert({position, object});
}

int
TILE8OBJECTS::COUNT()
{
    return objects_.size();
}

std::shared_ptr<OBJECT>
TILE8OBJECTS::PICK8OBJECT(std::shared_ptr<OBJECT> object)
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

void
TILE8OBJECTS::TRANSFORM8OBJECT(std::shared_ptr<OBJECT> object,
                               std::string_view newObjectType)
{
    POINT position = {-1, -1};

    for (auto it = objects_.begin(); it != objects_.end(); ++it)
    {
        if (it->second == object)
        {
            position = it->first;

            objects_.erase(it);

            break;
        }
    }

    if (position != POINT{-1, -1})
    {
        ADD8OBJECT(newObjectType, position);
    }
}

void
TILE8OBJECTS::REMOVE8OBJECT(std::shared_ptr<OBJECT> object)
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

bool
TILE8OBJECTS::HAS8OBJECT8OF8TYPE(std::string_view objectType)
{
    for (auto it = objects_.begin(); it != objects_.end(); ++it)
    {
        if (it->second->type_ == HASH(objectType))
        {
            return true;
        }
    }

    return false;
}