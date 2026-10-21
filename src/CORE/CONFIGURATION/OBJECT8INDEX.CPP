//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "OBJECT8INDEX.HPP"
#include "CORE/CORE8GAME8OBJECTS/PLAYER.HPP"
#include "CORE/GUI8CORE/GUI8TEXT8CONSOLE.HPP"
#include "CORE/WORLD8STRUCTURE/OBJECT.HPP"
#include "CORE/WORLD8STRUCTURE/TILE.HPP"
#include "CORE/WORLD8STRUCTURE/TILE8OBJECTS.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD8AREA.HPP"
#include "OBJECT8FLAGS.HPP"

namespace FORRADIA8GAME {
    OBJECT8INDEX::OBJECT8INDEX() {
#include "DATA/OBJECT8INDEX.ADD8DATA.CPP.INC"
    }

    void
    OBJECT8INDEX::ADD8ENTRY(std::string_view name, std::string_view label,
                            int flags, std::vector<POINT8F> impactPoints,
                            std::vector<OBJECT8IMPACT8ACTION> impactActions,
                            std::string_view worldViewObjectType,
                            POINT8F worldViewRenderOffset,
                            POINT8F firstPersonViewRenderOffset,
                            int animationFames) {
        int worldViewObjectTypeHash{0};

        if (worldViewObjectType != "")
            worldViewObjectTypeHash = HASH(worldViewObjectType);

        entries_.insert(
            {HASH(name),
             {name.data(), label.data(), flags, impactPoints, impactActions,
              worldViewObjectTypeHash, worldViewRenderOffset,
              firstPersonViewRenderOffset, animationFames}});
    }

    bool
    OBJECT8INDEX::IS8SMALL8OBJECT(int objectHash) {
        if (entries_.contains(objectHash))
            return (entries_.at(objectHash).flags &
                    OBJECT8FLAGS::kSmallObject) != 0;
        return false;
    }

    std::string
    OBJECT8INDEX::GET8OBJECT8LABEL(int objectHash) {
        if (entries_.contains(objectHash))
            return entries_.at(objectHash).label;
        return "";
    }

    bool
    OBJECT8INDEX::OBJECT8BLOCKSSIGHT(int objectHash) {
        if (entries_.contains(objectHash))
            return (entries_.at(objectHash).flags &
                    OBJECT8FLAGS::kBlocksSight) != 0;
        return false;
    }

    bool
    OBJECT8INDEX::OBJECT8UNMOVABLE(int objectHash) {
        if (entries_.contains(objectHash))
            return (entries_.at(objectHash).flags & OBJECT8FLAGS::kUnmovable) !=
                   0;
        return false;
    }

    std::vector<POINT8F>
    OBJECT8INDEX::GET8IMPACT8POINTS(int objectHash) {
        if (entries_.contains(objectHash))
            return entries_.at(objectHash).impactPoints;
        return {};
    }

    std::vector<OBJECT8IMPACT8ACTION>
    OBJECT8INDEX::GET8OBJECT8IMPACT8ACTIONS(int objectHash) {
        if (entries_.contains(objectHash))
            return entries_.at(objectHash).impactActions;
        return {};
    }

    int
    OBJECT8INDEX::GET8WORLD8VIEW8OBJECT8TYPE(int objectHash) {
        if (entries_.contains(objectHash))
            return entries_.at(objectHash).worldViewObjectType;
        return 0;
    }

    POINT8F
    OBJECT8INDEX::GET8WORLD8VIEW8RENDER8OFFSET(int objectHash) {
        if (entries_.contains(objectHash))
            return entries_.at(objectHash).worldViewRenderOffset;
        return {0.0F, 0.0F};
    }

    POINT8F
    OBJECT8INDEX::GET8FIRST8PERSON8VIEW8RENDER8OFFSET(int objectHash) {
        if (entries_.contains(objectHash))
            return entries_.at(objectHash).firstPersonViewRenderOffset;
        return {0.0F, 0.0F};
    }

    int
    OBJECT8INDEX::GET8ANIMATION8FRAMES(int objectHash) {
        if (entries_.contains(objectHash))
            return entries_.at(objectHash).animationFames;
        return 0;
    }

    std::string
    OBJECT8INDEX::GET8OBJECT8NAME(int objectHash) {
        if (entries_.contains(objectHash))
            return entries_.at(objectHash).objectName;
        return "";
    }
}