/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "PlayerInventory.hpp"
#include "Core/WorldStructure/Object.hpp"

namespace Forradia
{
    void PlayerInventory::AddObject(std::string_view objectName)
    {
        objects_.push_back(std::make_shared<Object>(objectName));
    }

    std::shared_ptr<Object> PlayerInventory::GetObject(int index)
    {
        if (index >= 0 && index < objects_.size())
        {
            return objects_.at(index);
        }

        return nullptr;
    }

    std::shared_ptr<Object> PlayerInventory::PickObject(int index)
    {
        if (index >= 0 && index < objects_.size())
        {
            auto result{objects_.at(index)};

            objects_.erase(objects_.begin() + index);

            return result;
        }

        return nullptr;
    }
}