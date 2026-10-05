// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "PlayerInventory.hpp"
#include "Core/WorldStructure/Object.hpp"

void PlayerInventory::AddObject(std::string_view objectName)
{
    for (auto i = 0; i < k_maxObjects_; i++)
    {
        if (!objects_.contains(i))
        {
            objects_[i] = std::make_shared<Object>(objectName);

            return;
        }
    }
}

void PlayerInventory::AddObject(std::shared_ptr<Object> object, int slotIndex)
{
    objects_.insert({slotIndex, object});
}

std::shared_ptr<Object> PlayerInventory::GetObject(int index)
{
    if (objects_.contains(index))
    {
        return objects_.at(index);
    }

    return nullptr;
}

std::shared_ptr<Object> PlayerInventory::PickObject(int index)
{
    for (auto it = objects_.begin(); it != objects_.end();)
    {
        if (it->first == index)
        {
            auto result{it->second};

            objects_.erase(it++);

            return result;
        }

        ++it;
    }

    return nullptr;
}

bool PlayerInventory::HasObject(int index)
{
    return objects_.contains(index);
}