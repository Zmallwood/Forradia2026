//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "ESSENCE8INDEX.HPP"

namespace FORRADIA8GAME {
    ESSENCE8INDEX::ESSENCE8INDEX() {
        ADD8ENTRY("GroundGrass", {"smell of fresh grass",
                                  "a small insect crawling in the grass"});
        ADD8ENTRY("GroundDirt", {"that the lack of grass is noticeable",
                                 "a small insect crawling in the dirt"});
        ADD8ENTRY("GroundRock", {"a sharp rock is poking out of the ground",
                                 "a small insect crawling on the rock"});
        ADD8ENTRY("GroundWater", {"that the water is clear and transparent",
                                  "a small fish is swimming in the water"});
        ADD8ENTRY("ObjectTree1", {"a bird is singing in the tree"});
        ADD8ENTRY("ObjectTree2", {"a bird is singing in the tree"});
    }

    void
    ESSENCE8INDEX::ADD8ENTRY(std::string_view name,
                             std::vector<std::string> descriptions) {
        mEntries.insert({HASH(name), descriptions});
    }

    std::vector<std::string>
    ESSENCE8INDEX::GET8ESSENCE8DESCRIPTIONS(int nameHash) {
        if (mEntries.contains(nameHash))
            return mEntries.at(nameHash);
        return {};
    }
}