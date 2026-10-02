/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "ObjectIndex.hpp"
#include "Core/CoreGameObjects/Player.hpp"
#include "Core/GUICore/GUITextConsole.hpp"
#include "Core/WorldStructure/Object.hpp"
#include "Core/WorldStructure/Tile.hpp"
#include "Core/WorldStructure/TileObjects.hpp"
#include "Core/WorldStructure/World.hpp"
#include "Core/WorldStructure/WorldArea.hpp"
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

        auto allImpactPointsCompletedActionObjectTree1 =
            [](std::shared_ptr<Object> object)
        {
            auto worldArea{_<World>().currentWorldArea_};

            auto facedTileCoordinate{_<Player>().facedTileCoordinate_};

            auto facedTile{worldArea->GetTile(facedTileCoordinate)};

            facedTile->tileObjects_->TransformObject(object,
                                                     "ObjectFelledTree");

            _<GUITextConsole>().PrintLine("You have felled the tree.");

            _<Player>().AddExperience(13);
        };

        AddEntry(
            "ObjectTree1", "Tree",
            ObjectFlags::k_blocksSight | ObjectFlags::k_unmovable,
            {PointF{0.5f, 0.95f}, PointF{0.55f, 0.95f}, PointF{0.6f, 0.95f}},
            {"ObjectWoodAxe"}, []() {},
            allImpactPointsCompletedActionObjectTree1);

        auto allImpactPointsCompletedActionObjectTree2 =
            allImpactPointsCompletedActionObjectTree1;

        AddEntry(
            "ObjectTree2", "Tree",
            ObjectFlags::k_blocksSight | ObjectFlags::k_unmovable,
            {PointF{0.5f, 0.8f}, PointF{0.53f, 0.8f}, PointF{0.56f, 0.8f}},
            {"ObjectWoodAxe"}, []() {},
            allImpactPointsCompletedActionObjectTree2);

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

        auto singleImpactPointCompletedActionObjectFelledTree = []()
        {
            auto worldArea{_<World>().currentWorldArea_};

            auto facedTileCoordinate{_<Player>().facedTileCoordinate_};

            auto facedTile{worldArea->GetTile(facedTileCoordinate)};

            facedTile->tileObjects_->AddObject("ObjectWoodLog");

            _<GUITextConsole>().PrintLine("You have chopped some wood logs.");

            _<Player>().AddExperience(7);
        };

        auto allImpactPointsCompletedActionObjectFelledTree =
            [](std::shared_ptr<Object> object)
        {
            auto worldArea{_<World>().currentWorldArea_};

            auto facedTileCoordinate{_<Player>().facedTileCoordinate_};

            auto facedTile{worldArea->GetTile(facedTileCoordinate)};

            facedTile->tileObjects_->RemoveObject(object);

            _<GUITextConsole>().PrintLine(
                "You have chopped up the felled tree.");
        };

        AddEntry("ObjectFelledTree", "Felled tree", ObjectFlags::k_unmovable,
                 {PointF{0.55f, 0.95f}, PointF{0.55f, 0.89f},
                  PointF{0.55f, 0.83f}, PointF{0.55f, 0.77f}},
                 {"ObjectWoodAxe"},
                 singleImpactPointCompletedActionObjectFelledTree,
                 allImpactPointsCompletedActionObjectFelledTree);
    }

    void ObjectIndex::AddEntry(
        std::string_view name, std::string_view label, int flags,
        std::vector<PointF> impactPoints,
        std::vector<std::string> impactObjects,
        std::function<void()> singleImpactPointCompletedAction,
        std::function<void(std::shared_ptr<Object>)>
            allImpactPointsCompletedAction)
    {
        std::vector<int> impactObjectHashes;

        for (auto &impactObject : impactObjects)
        {
            impactObjectHashes.push_back(Hash(impactObject));
        }

        entries_.insert({Hash(name),
                         {label.data(), flags, impactPoints, impactObjectHashes,
                          singleImpactPointCompletedAction,
                          allImpactPointsCompletedAction}});
    }

    bool ObjectIndex::IsSmallObject(int objectHash)
    {
        if (entries_.contains(objectHash))
        {
            return (entries_.at(objectHash).flags &
                    ObjectFlags::k_smallObject) != 0;
        }

        return false;
    }

    std::string ObjectIndex::GetObjectLabel(int objectHash)
    {
        if (entries_.contains(objectHash))
        {
            return entries_.at(objectHash).label;
        }

        return "";
    }

    bool ObjectIndex::ObjectBlocksSight(int objectHash)
    {
        if (entries_.contains(objectHash))
        {
            return (entries_.at(objectHash).flags &
                    ObjectFlags::k_blocksSight) != 0;
        }

        return false;
    }

    bool ObjectIndex::ObjectUnmovable(int objectHash)
    {
        if (entries_.contains(objectHash))
        {
            return (entries_.at(objectHash).flags & ObjectFlags::k_unmovable) !=
                   0;
        }

        return false;
    }

    std::vector<PointF> ObjectIndex::GetImpactPoints(int objectHash)
    {
        if (entries_.contains(objectHash))
        {
            return entries_.at(objectHash).impactPoints;
        }

        return {};
    }

    std::vector<int> ObjectIndex::GetImpactObjects(int objectHash)
    {
        if (entries_.contains(objectHash))
        {
            return entries_.at(objectHash).impactObjects;
        }

        return {};
    }

    std::function<void()>
    ObjectIndex::GetSingleImpactPointCompletedAction(int objectHash)
    {
        if (entries_.contains(objectHash))
        {
            return entries_.at(objectHash).singleImpactPointCompletedAction;
        }

        return []() {};
    }

    std::function<void(std::shared_ptr<Object>)>
    ObjectIndex::GetAllImpactPointsCompletedAction(int objectHash)
    {
        if (entries_.contains(objectHash))
        {
            return entries_.at(objectHash).allImpactPointsCompletedAction;
        }

        return [](std::shared_ptr<Object>) {};
    }
}