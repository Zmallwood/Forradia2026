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
        entries_.insert({Hash("object_stone"), {ObjectFlags::k_smallObject}});

        entries_.insert({Hash("object_branch"), {ObjectFlags::k_smallObject}});

        entries_.insert(
            {Hash("object_pink_flower"), {ObjectFlags::k_smallObject}});

        entries_.insert({Hash("object_leaf"), {ObjectFlags::k_smallObject}});
    }

    bool ObjectIndex::IsSmallObject(int objectHash)
    {
        return entries_[objectHash].flags & ObjectFlags::k_smallObject;
    }
}