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

        AddEntry("ObjectPinkFlower", "Pink flower", ObjectFlags::k_smallObject);

        AddEntry("ObjectLeaf", "Leaf", ObjectFlags::k_smallObject);

        AddEntry("ObjectPoolOfBlood", "Pool of blood",
                 ObjectFlags::k_smallObject);

        AddEntry("ObjectTree1", "Tree",
                 ObjectFlags::k_blocksSight | ObjectFlags::k_unmovable);

        AddEntry("ObjectTree2", "Tree",
                 ObjectFlags::k_blocksSight | ObjectFlags::k_unmovable);

        AddEntry("ObjectBush1", "Bush",
                 ObjectFlags::k_blocksSight | ObjectFlags::k_unmovable);

        AddEntry("ObjectStoneBoulder", "Stone boulder",
                 ObjectFlags::k_blocksSight | ObjectFlags::k_unmovable);

        AddEntry("ObjectCreatureDeerCorpse", "Deer corpse", 0);

        AddEntry("ObjectCreatureBoarCorpse", "Boar corpse", 0);

        AddEntry("ObjectRedApple", "Red apple", ObjectFlags::k_smallObject);

        AddEntry("ObjectCopperSword", "Copper sword",
                 ObjectFlags::k_smallObject);

        AddEntry("ObjectWoodAxe", "Wood axe", ObjectFlags::k_smallObject);
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
            return entries_[objectHash].flags & ObjectFlags::k_smallObject != 0;
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

    bool ObjectIndex::ObjectBlocksSight(int objectHash)
    {
        if (entries_.contains(objectHash))
        {
            return entries_[objectHash].flags & ObjectFlags::k_blocksSight != 0;
        }

        return false;
    }

    bool ObjectIndex::ObjectUnmovable(int objectHash)
    {

        if (entries_.contains(objectHash))
        {
            return entries_[objectHash].flags & ObjectFlags::k_unmovable != 0;
        }

        return false;
    }
}