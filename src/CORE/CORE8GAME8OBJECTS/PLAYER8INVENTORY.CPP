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
        for (auto i = 0; i < mkMaxObjects; i++) {
            if (!mObjects.contains(i)) {
                mObjects[i] = std::make_shared<OBJECT>(objectName);
                return;
            }
        }
    }

    void
    PLAYER8INVENTORY::ADD8OBJECT(std::shared_ptr<OBJECT> object,
                                 int slotIndex) {
        mObjects.insert({slotIndex, object});
    }

    std::shared_ptr<OBJECT>
    PLAYER8INVENTORY::GET8OBJECT(int index) {
        if (mObjects.contains(index))
            return mObjects.at(index);
        return nullptr;
    }

    std::shared_ptr<OBJECT>
    PLAYER8INVENTORY::PICK8OBJECT(int index) {
        for (auto it = mObjects.begin(); it != mObjects.end();) {
            if (it->first == index) {
                auto result{it->second};
                mObjects.erase(it++);
                return result;
            }
            ++it;
        }
        return nullptr;
    }

    bool
    PLAYER8INVENTORY::HAS8OBJECT(int index) {
        return mObjects.contains(index);
    }
}