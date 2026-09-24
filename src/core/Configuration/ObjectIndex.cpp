/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "ObjectIndex.hpp"
#include "ObjectFlags.hpp"

namespace Forradia
{
    ObjectIndex::ObjectIndex()
    {
        entries_.insert({Hash("ObjectStone"), {ObjectFlags::k_smallObject}});

        entries_.insert({Hash("ObjectBranch"), {ObjectFlags::k_smallObject}});

        entries_.insert(
            {Hash("ObjectPinkFlower"), {ObjectFlags::k_smallObject}});

        entries_.insert({Hash("ObjectLeaf"), {ObjectFlags::k_smallObject}});

        entries_.insert({Hash("ObjectPoolOfBlood"), {ObjectFlags::k_smallObject}});
    }

    bool ObjectIndex::IsSmallObject(int objectHash)
    {
        return entries_[objectHash].flags & ObjectFlags::k_smallObject;
    }
}