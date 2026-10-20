//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "PLAYER8INVENTORY.HPP"
#include "CORE/WORLD8STRUCTURE/OBJECT.HPP"

namespace FORRADIA8GAME {
    void
    PLAYER8INVENTORY::ADD8OBJECT(std::string_view objectName) {
        for (auto i = 0; i < kMaxObjects_; i++) {
            if (!objects_.contains(i)) {
                objects_[i] = std::make_shared<OBJECT>(objectName);

                return;
            }
        }
    }

    void
    PLAYER8INVENTORY::ADD8OBJECT(std::shared_ptr<OBJECT> object,
                                 int slotIndex) {
        objects_.insert({slotIndex, object});
    }

    std::shared_ptr<OBJECT>
    PLAYER8INVENTORY::GET8OBJECT(int index) {
        if (objects_.contains(index)) {
            return objects_.at(index);
        }

        return nullptr;
    }

    std::shared_ptr<OBJECT>
    PLAYER8INVENTORY::PICK8OBJECT(int index) {
        for (auto it = objects_.begin(); it != objects_.end();) {
            if (it->first == index) {
                auto result = it->second;

                objects_.erase(it++);

                return result;
            }

            ++it;
        }

        return nullptr;
    }

    bool
    PLAYER8INVENTORY::HAS8OBJECT(int index) {
        return objects_.contains(index);
    }
}