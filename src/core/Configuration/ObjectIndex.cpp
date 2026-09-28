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
        AddEntry("ObjectStone", "Stone", ObjectFlags::k_smallObject);

        AddEntry("ObjectBranch", "Branch", ObjectFlags::k_smallObject);

        AddEntry("ObjectPinkFlower", "Pink Flower", ObjectFlags::k_smallObject);

        AddEntry("ObjectLeaf", "Leaf", ObjectFlags::k_smallObject);

        AddEntry("ObjectPoolOfBlood", "Pool of Blood",
                 ObjectFlags::k_smallObject);

        AddEntry("ObjectTree1", "Tree", 0);

        AddEntry("ObjectTree2", "Tree", 0);
    }

    void ObjectIndex::AddEntry(std::string_view name, std::string_view label,
                               int flags)
    {
        entries_.insert({Hash(name), {label.data(), flags}});
    }

    bool ObjectIndex::IsSmallObject(int objectHash)
    {
        if (entries_.contains(objectHash))
        {
            return entries_[objectHash].flags & ObjectFlags::k_smallObject;
        }

        return false;
    }

    std::string ObjectIndex::GetObjectLabel(int objectHash)
    {
        if (entries_.contains(objectHash))
        {
            return entries_[objectHash].label;
        }

        return "";
    }
}