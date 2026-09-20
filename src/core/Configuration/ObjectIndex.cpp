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
        entries_.insert(
            {GetHash("object_stone"), {ObjectFlags::k_smallObject}});

        entries_.insert(
            {GetHash("object_branch"), {ObjectFlags::k_smallObject}});

        entries_.insert(
            {GetHash("object_pink_flower"), {ObjectFlags::k_smallObject}});

        entries_.insert({GetHash("object_leaf"), {ObjectFlags::k_smallObject}});
    }

    bool ObjectIndex::IsSmallObject(int object_hash)
    {
        return entries_[object_hash].flags & ObjectFlags::k_smallObject;
    }
}