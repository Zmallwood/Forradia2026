// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CORE/WORLD8STRUCTURE/OBJECT.HPP"
#include "PLAYER8INVENTORY.HPP"

void
PLAYER8INVENTORY::ADD8OBJECT(std::string_view objectName)
{
    for (auto i = 0; i < kMaxObjects_; i++)
    {
        if (!objects_.contains(i))
        {
            objects_[i] = std::make_shared<Object>(objectName);

            return;
        }
    }
}

void
PLAYER8INVENTORY::ADD8OBJECT(std::shared_ptr<Object> object, int slotIndex)
{
    objects_.insert({slotIndex, object});
}

std::shared_ptr<Object>
PLAYER8INVENTORY::GET8OBJECT(int index)
{
    if (objects_.contains(index))
    {
        return objects_.at(index);
    }

    return nullptr;
}

std::shared_ptr<Object>
PLAYER8INVENTORY::PICK8OBJECT(int index)
{
    for (auto it = objects_.begin(); it != objects_.end();)
    {
        if (it->first == index)
        {
            auto result = it->second;

            objects_.erase(it++);

            return result;
        }

        ++it;
    }

    return nullptr;
}

bool
PLAYER8INVENTORY::HAS8OBJECT(int index)
{
    return objects_.contains(index);
}