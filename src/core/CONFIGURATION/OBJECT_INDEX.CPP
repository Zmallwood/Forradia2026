// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"
#include "CORE/GUI_CORE/GUI_TEXT_CONSOLE.HPP"
#include "CORE/WORLD_STRUCTURE/OBJECT.HPP"
#include "CORE/WORLD_STRUCTURE/TILE.HPP"
#include "CORE/WORLD_STRUCTURE/TILE_OBJECTS.HPP"
#include "CORE/WORLD_STRUCTURE/WORLD.HPP"
#include "CORE/WORLD_STRUCTURE/WORLD_AREA.HPP"
#include "OBJECT_FLAGS.HPP"
#include "OBJECT_INDEX.HPP"

ObjectIndex::ObjectIndex()
{
    AddEntry("ObjectStone", "Stone", ObjectFlags::k_smallObject);

    AddEntry("ObjectBranch", "Branch", ObjectFlags::k_smallObject);

    AddEntry("ObjectPinkFlower", "Pink flower", ObjectFlags::k_smallObject);

    AddEntry("ObjectLeaf", "Leaf", ObjectFlags::k_smallObject);

    AddEntry("ObjectPoolOfBlood", "Pool of blood", ObjectFlags::k_smallObject);

    auto allImpactPointsCompletedActionObjectTree1 =
        [](std::shared_ptr<Object> object)
    {
        auto worldArea = _<World>().currentWorldArea_;

        auto facedTileCoordinate = _<Player>().facedTileCoordinate_;

        auto facedTile = worldArea->GetTile(facedTileCoordinate);

        facedTile->tileObjects_->TransformObject(object, "ObjectFelledTree");

        _<GUITextConsole>().PrintLine("You have felled the tree.");

        _<Player>().AddExperience(13);
    };

    AddEntry(
        "ObjectTree1", "Tree",
        ObjectFlags::k_blocksSight | ObjectFlags::k_unmovable,
        {POINT_F{0.5f, 0.95f}, POINT_F{0.55f, 0.95f}, POINT_F{0.6f, 0.95f}},
        {"ObjectWoodAxe"}, []() {}, allImpactPointsCompletedActionObjectTree1);

    auto allImpactPointsCompletedActionObjectTree2 =
        allImpactPointsCompletedActionObjectTree1;

    AddEntry(
        "ObjectTree2", "Tree",
        ObjectFlags::k_blocksSight | ObjectFlags::k_unmovable,
        {POINT_F{0.5f, 0.8f}, POINT_F{0.53f, 0.8f}, POINT_F{0.56f, 0.8f}},
        {"ObjectWoodAxe"}, []() {}, allImpactPointsCompletedActionObjectTree2);

    AddEntry("ObjectBush1", "Bush",
             ObjectFlags::k_blocksSight | ObjectFlags::k_unmovable);

    AddEntry(
        "ObjectStoneBoulder", "Stone boulder",
        ObjectFlags::k_blocksSight | ObjectFlags::k_unmovable, {}, {}, []() {},
        [](std::shared_ptr<Object>) {}, "", POINT_F{0.0f, 0.3f},
        POINT_F{0.0f, 0.0f});

    AddEntry("ObjectCreatureDeerCorpse", "Deer corpse", 0);

    AddEntry("ObjectCreatureBoarCorpse", "Boar corpse", 0);

    AddEntry("ObjectRedApple", "Red apple", ObjectFlags::k_smallObject);

    AddEntry("ObjectCopperSword", "Copper sword", ObjectFlags::k_smallObject);

    AddEntry("ObjectWoodAxe", "Wood axe", ObjectFlags::k_smallObject);

    auto singleImpactPointCompletedActionObjectFelledTree = []()
    {
        auto worldArea = _<World>().currentWorldArea_;

        auto facedTileCoordinate = _<Player>().facedTileCoordinate_;

        auto facedTile = worldArea->GetTile(facedTileCoordinate);

        facedTile->tileObjects_->AddObject("ObjectWoodLog");

        _<GUITextConsole>().PrintLine("You have chopped some wood logs.");

        _<Player>().AddExperience(7);
    };

    auto allImpactPointsCompletedActionObjectFelledTree =
        [](std::shared_ptr<Object> object)
    {
        auto worldArea = _<World>().currentWorldArea_;

        auto facedTileCoordinate = _<Player>().facedTileCoordinate_;

        auto facedTile = worldArea->GetTile(facedTileCoordinate);

        facedTile->tileObjects_->RemoveObject(object);

        _<GUITextConsole>().PrintLine("You have chopped up the felled tree.");
    };

    AddEntry("ObjectFelledTree", "Felled tree", ObjectFlags::k_unmovable,
             {POINT_F{0.55f, 0.95f}, POINT_F{0.55f, 0.89f},
              POINT_F{0.55f, 0.83f}, POINT_F{0.55f, 0.77f}},
             {"ObjectWoodAxe"},
             singleImpactPointCompletedActionObjectFelledTree,
             allImpactPointsCompletedActionObjectFelledTree);

    auto allImpactPointsCompletedActionObjectWoodLog =
        [](std::shared_ptr<Object> object)
    {
        auto worldArea = _<World>().currentWorldArea_;

        auto facedTileCoordinate = _<Player>().facedTileCoordinate_;

        auto facedTile = worldArea->GetTile(facedTileCoordinate);

        facedTile->tileObjects_->TransformObject(object, "ObjectWoodPlank");

        _<GUITextConsole>().PrintLine("You have sawed the wood log.");
    };

    AddEntry(
        "ObjectWoodLog", "Wood log", ObjectFlags::k_smallObject,
        {POINT_F{0.5f, 0.93f}}, {"ObjectSaw"}, []() {},
        allImpactPointsCompletedActionObjectWoodLog);

    AddEntry("ObjectWoodPlank", "Wood plank", ObjectFlags::k_smallObject);

    AddEntry("ObjectSaw", "Saw", ObjectFlags::k_smallObject);

    auto allImpactPointsCompletedActionObjectWoodWallPlankNorth1 =
        [](std::shared_ptr<Object> object)
    {
        auto worldArea = _<World>().currentWorldArea_;

        auto facedTileCoordinate = _<Player>().facedTileCoordinate_;

        auto facedTile = worldArea->GetTile(facedTileCoordinate);

        facedTile->tileObjects_->TransformObject(object,
                                                 "ObjectWoodWallPlankNorth1");
    };

    AddEntry(
        "ObjectPlannedWoodWallNorthPlank1", "Planned wood wall north, plank 1",
        ObjectFlags::k_unmovable, {POINT_F{0.5f, 0.08f}, POINT_F{0.5f, 0.92f}},
        {"ObjectHammer"}, []() {},
        allImpactPointsCompletedActionObjectWoodWallPlankNorth1,
        "ObjectPlannedObject");

    auto allImpactPointsCompletedActionObjectWoodWallPlankNorth2 =
        [](std::shared_ptr<Object> object)
    {
        auto worldArea = _<World>().currentWorldArea_;

        auto facedTileCoordinate = _<Player>().facedTileCoordinate_;

        auto facedTile = worldArea->GetTile(facedTileCoordinate);

        facedTile->tileObjects_->TransformObject(object,
                                                 "ObjectWoodWallPlankNorth2");
    };

    AddEntry(
        "ObjectPlannedWoodWallNorthPlank2", "Planned wood wall north, plank 2",
        ObjectFlags::k_unmovable, {POINT_F{0.5f, 0.08f}, POINT_F{0.5f, 0.92f}},
        {"ObjectHammer"}, []() {},
        allImpactPointsCompletedActionObjectWoodWallPlankNorth2,
        "ObjectPlannedObject");

    auto allImpactPointsCompletedActionObjectWoodWallPlankNorth3 =
        [](std::shared_ptr<Object> object)
    {
        auto worldArea = _<World>().currentWorldArea_;

        auto facedTileCoordinate = _<Player>().facedTileCoordinate_;

        auto facedTile = worldArea->GetTile(facedTileCoordinate);

        facedTile->tileObjects_->TransformObject(object,
                                                 "ObjectWoodWallPlankNorth3");
    };

    AddEntry(
        "ObjectPlannedWoodWallNorthPlank3", "Planned wood wall north, plank 3",
        ObjectFlags::k_unmovable, {POINT_F{0.5f, 0.08f}, POINT_F{0.5f, 0.92f}},
        {"ObjectHammer"}, []() {},
        allImpactPointsCompletedActionObjectWoodWallPlankNorth3,
        "ObjectPlannedObject");

    auto allImpactPointsCompletedActionObjectWoodWallPlankNorth4 =
        [](std::shared_ptr<Object> object)
    {
        auto worldArea = _<World>().currentWorldArea_;

        auto facedTileCoordinate = _<Player>().facedTileCoordinate_;

        auto facedTile = worldArea->GetTile(facedTileCoordinate);

        facedTile->tileObjects_->TransformObject(object,
                                                 "ObjectWoodWallPlankNorth4");
    };

    AddEntry(
        "ObjectPlannedWoodWallNorthPlank4", "Planned wood wall north, plank 1",
        ObjectFlags::k_unmovable, {POINT_F{0.5f, 0.08f}, POINT_F{0.5f, 0.92f}},
        {"ObjectHammer"}, []() {},
        allImpactPointsCompletedActionObjectWoodWallPlankNorth4,
        "ObjectPlannedObject");

    AddEntry(
        "ObjectWoodWallPlankNorth1", "Wood wall", ObjectFlags::k_unmovable, {},
        {}, []() {}, [](std::shared_ptr<Object>) {},
        "ObjectWoodWallPlankNorth1WorldView", POINT_F{0.0f, 0.5f});

    AddEntry(
        "ObjectWoodWallPlankNorth2", "Wood wall", ObjectFlags::k_unmovable, {},
        {}, []() {}, [](std::shared_ptr<Object>) {},
        "ObjectWoodWallPlankNorth2WorldView", POINT_F{0.0f, 0.5f});

    AddEntry(
        "ObjectWoodWallPlankNorth3", "Wood wall", ObjectFlags::k_unmovable, {},
        {}, []() {}, [](std::shared_ptr<Object>) {},
        "ObjectWoodWallPlankNorth3WorldView", POINT_F{0.0f, 0.5f});

    AddEntry(
        "ObjectWoodWallPlankNorth4", "Wood wall", ObjectFlags::k_unmovable, {},
        {}, []() {}, [](std::shared_ptr<Object>) {},
        "ObjectWoodWallPlankNorth4WorldView", POINT_F{0.0f, 0.5f});

    auto allImpactPointsCompletedActionObjectWoodWallPlankEast1 =
        [](std::shared_ptr<Object> object)
    {
        auto worldArea = _<World>().currentWorldArea_;

        auto facedTileCoordinate = _<Player>().facedTileCoordinate_;

        auto facedTile = worldArea->GetTile(facedTileCoordinate);

        facedTile->tileObjects_->TransformObject(object,
                                                 "ObjectWoodWallPlankEast1");
    };

    AddEntry(
        "ObjectPlannedWoodWallEastPlank1", "Planned wood wall east, plank 1",
        ObjectFlags::k_unmovable, {POINT_F{0.5f, 0.08f}, POINT_F{0.5f, 0.92f}},
        {"ObjectHammer"}, []() {},
        allImpactPointsCompletedActionObjectWoodWallPlankEast1,
        "ObjectPlannedObject");

    auto allImpactPointsCompletedActionObjectWoodWallPlankEast2 =
        [](std::shared_ptr<Object> object)
    {
        auto worldArea = _<World>().currentWorldArea_;

        auto facedTileCoordinate = _<Player>().facedTileCoordinate_;

        auto facedTile = worldArea->GetTile(facedTileCoordinate);

        facedTile->tileObjects_->TransformObject(object,
                                                 "ObjectWoodWallPlankEast2");
    };

    AddEntry(
        "ObjectPlannedWoodWallEastPlank2", "Planned wood wall east, plank 2",
        ObjectFlags::k_unmovable, {POINT_F{0.5f, 0.08f}, POINT_F{0.5f, 0.92f}},
        {"ObjectHammer"}, []() {},
        allImpactPointsCompletedActionObjectWoodWallPlankEast2,
        "ObjectPlannedObject");

    auto allImpactPointsCompletedActionObjectWoodWallPlankEast3 =
        [](std::shared_ptr<Object> object)
    {
        auto worldArea = _<World>().currentWorldArea_;

        auto facedTileCoordinate = _<Player>().facedTileCoordinate_;

        auto facedTile = worldArea->GetTile(facedTileCoordinate);

        facedTile->tileObjects_->TransformObject(object,
                                                 "ObjectWoodWallPlankEast3");
    };

    AddEntry(
        "ObjectPlannedWoodWallEastPlank3", "Planned wood wall east, plank 3",
        ObjectFlags::k_unmovable, {POINT_F{0.5f, 0.08f}, POINT_F{0.5f, 0.92f}},
        {"ObjectHammer"}, []() {},
        allImpactPointsCompletedActionObjectWoodWallPlankEast3,
        "ObjectPlannedObject");

    auto allImpactPointsCompletedActionObjectWoodWallPlankEast4 =
        [](std::shared_ptr<Object> object)
    {
        auto worldArea = _<World>().currentWorldArea_;

        auto facedTileCoordinate = _<Player>().facedTileCoordinate_;

        auto facedTile = worldArea->GetTile(facedTileCoordinate);

        facedTile->tileObjects_->TransformObject(object,
                                                 "ObjectWoodWallPlankEast4");
    };

    AddEntry(
        "ObjectPlannedWoodWallEastPlank4", "Planned wood wall east, plank 4",
        ObjectFlags::k_unmovable, {POINT_F{0.5f, 0.08f}, POINT_F{0.5f, 0.92f}},
        {"ObjectHammer"}, []() {},
        allImpactPointsCompletedActionObjectWoodWallPlankEast4,
        "ObjectPlannedObject");

    AddEntry(
        "ObjectWoodWallPlankEast1", "Wood wall", ObjectFlags::k_unmovable, {},
        {}, []() {}, [](std::shared_ptr<Object>) {},
        "ObjectWoodWallPlankEast1WorldView", POINT_F{0.0f, 0.5f});

    AddEntry(
        "ObjectWoodWallPlankEast2", "Wood wall", ObjectFlags::k_unmovable, {},
        {}, []() {}, [](std::shared_ptr<Object>) {},
        "ObjectWoodWallPlankEast2WorldView", POINT_F{0.0f, 0.5f});

    AddEntry(
        "ObjectWoodWallPlankEast3", "Wood wall", ObjectFlags::k_unmovable, {},
        {}, []() {}, [](std::shared_ptr<Object>) {},
        "ObjectWoodWallPlankEast3WorldView", POINT_F{0.0f, 0.5f});

    AddEntry(
        "ObjectWoodWallPlankEast4", "Wood wall", ObjectFlags::k_unmovable, {},
        {}, []() {}, [](std::shared_ptr<Object>) {},
        "ObjectWoodWallPlankEast4WorldView", POINT_F{0.0f, 0.5f});

    auto allImpactPointsCompletedActionObjectWoodWallPlankSouth1 =
        [](std::shared_ptr<Object> object)
    {
        auto worldArea = _<World>().currentWorldArea_;

        auto facedTileCoordinate = _<Player>().facedTileCoordinate_;

        auto facedTile = worldArea->GetTile(facedTileCoordinate);

        facedTile->tileObjects_->TransformObject(object,
                                                 "ObjectWoodWallPlankSouth1");
    };

    AddEntry(
        "ObjectPlannedWoodWallSouthPlank1", "Planned wood wall south, plank 1",
        ObjectFlags::k_unmovable, {POINT_F{0.5f, 0.08f}, POINT_F{0.5f, 0.92f}},
        {"ObjectHammer"}, []() {},
        allImpactPointsCompletedActionObjectWoodWallPlankSouth1,
        "ObjectPlannedObject");

    auto allImpactPointsCompletedActionObjectWoodWallPlankSouth2 =
        [](std::shared_ptr<Object> object)
    {
        auto worldArea = _<World>().currentWorldArea_;

        auto facedTileCoordinate = _<Player>().facedTileCoordinate_;

        auto facedTile = worldArea->GetTile(facedTileCoordinate);

        facedTile->tileObjects_->TransformObject(object,
                                                 "ObjectWoodWallPlankSouth2");
    };

    AddEntry(
        "ObjectPlannedWoodWallSouthPlank2", "Planned wood wall south, plank 2",
        ObjectFlags::k_unmovable, {POINT_F{0.5f, 0.08f}, POINT_F{0.5f, 0.92f}},
        {"ObjectHammer"}, []() {},
        allImpactPointsCompletedActionObjectWoodWallPlankSouth2,
        "ObjectPlannedObject");

    auto allImpactPointsCompletedActionObjectWoodWallPlankSouth3 =
        [](std::shared_ptr<Object> object)
    {
        auto worldArea = _<World>().currentWorldArea_;

        auto facedTileCoordinate = _<Player>().facedTileCoordinate_;

        auto facedTile = worldArea->GetTile(facedTileCoordinate);

        facedTile->tileObjects_->TransformObject(object,
                                                 "ObjectWoodWallPlankSouth3");
    };

    AddEntry(
        "ObjectPlannedWoodWallSouthPlank3", "Planned wood wall south, plank 3",
        ObjectFlags::k_unmovable, {POINT_F{0.5f, 0.08f}, POINT_F{0.5f, 0.92f}},
        {"ObjectHammer"}, []() {},
        allImpactPointsCompletedActionObjectWoodWallPlankSouth3,
        "ObjectPlannedObject");

    auto allImpactPointsCompletedActionObjectWoodWallPlankSouth4 =
        [](std::shared_ptr<Object> object)
    {
        auto worldArea = _<World>().currentWorldArea_;

        auto facedTileCoordinate = _<Player>().facedTileCoordinate_;

        auto facedTile = worldArea->GetTile(facedTileCoordinate);

        facedTile->tileObjects_->TransformObject(object,
                                                 "ObjectWoodWallPlankSouth4");
    };

    AddEntry(
        "ObjectPlannedWoodWallSouthPlank4", "Planned wood wall south, plank 4",
        ObjectFlags::k_unmovable, {POINT_F{0.5f, 0.08f}, POINT_F{0.5f, 0.92f}},
        {"ObjectHammer"}, []() {},
        allImpactPointsCompletedActionObjectWoodWallPlankSouth4,
        "ObjectPlannedObject");

    AddEntry(
        "ObjectWoodWallPlankSouth1", "Wood wall", ObjectFlags::k_unmovable, {},
        {}, []() {}, [](std::shared_ptr<Object>) {},
        "ObjectWoodWallPlankSouth1WorldView", POINT_F{0.0f, 0.5f});

    AddEntry(
        "ObjectWoodWallPlankSouth2", "Wood wall", ObjectFlags::k_unmovable, {},
        {}, []() {}, [](std::shared_ptr<Object>) {},
        "ObjectWoodWallPlankSouth2WorldView", POINT_F{0.0f, 0.5f});

    AddEntry(
        "ObjectWoodWallPlankSouth3", "Wood wall", ObjectFlags::k_unmovable, {},
        {}, []() {}, [](std::shared_ptr<Object>) {},
        "ObjectWoodWallPlankSouth3WorldView", POINT_F{0.0f, 0.5f});

    AddEntry(
        "ObjectWoodWallPlankSouth4", "Wood wall", ObjectFlags::k_unmovable, {},
        {}, []() {}, [](std::shared_ptr<Object>) {},
        "ObjectWoodWallPlankSouth4WorldView", POINT_F{0.0f, 0.5f});

    auto allImpactPointsCompletedActionObjectWoodWallPlankWest1 =
        [](std::shared_ptr<Object> object)
    {
        auto worldArea = _<World>().currentWorldArea_;

        auto facedTileCoordinate = _<Player>().facedTileCoordinate_;

        auto facedTile = worldArea->GetTile(facedTileCoordinate);

        facedTile->tileObjects_->TransformObject(object,
                                                 "ObjectWoodWallPlankWest1");
    };

    AddEntry(
        "ObjectPlannedWoodWallWestPlank1", "Planned wood wall west, plank 1",
        ObjectFlags::k_unmovable, {POINT_F{0.5f, 0.08f}, POINT_F{0.5f, 0.92f}},
        {"ObjectHammer"}, []() {},
        allImpactPointsCompletedActionObjectWoodWallPlankWest1,
        "ObjectPlannedObject");

    auto allImpactPointsCompletedActionObjectWoodWallPlankWest2 =
        [](std::shared_ptr<Object> object)
    {
        auto worldArea = _<World>().currentWorldArea_;

        auto facedTileCoordinate = _<Player>().facedTileCoordinate_;

        auto facedTile = worldArea->GetTile(facedTileCoordinate);

        facedTile->tileObjects_->TransformObject(object,
                                                 "ObjectWoodWallPlankWest2");
    };

    AddEntry(
        "ObjectPlannedWoodWallWestPlank2", "Planned wood wall west, plank 2",
        ObjectFlags::k_unmovable, {POINT_F{0.5f, 0.08f}, POINT_F{0.5f, 0.92f}},
        {"ObjectHammer"}, []() {},
        allImpactPointsCompletedActionObjectWoodWallPlankWest2,
        "ObjectPlannedObject");

    auto allImpactPointsCompletedActionObjectWoodWallPlankWest3 =
        [](std::shared_ptr<Object> object)
    {
        auto worldArea = _<World>().currentWorldArea_;

        auto facedTileCoordinate = _<Player>().facedTileCoordinate_;

        auto facedTile = worldArea->GetTile(facedTileCoordinate);

        facedTile->tileObjects_->TransformObject(object,
                                                 "ObjectWoodWallPlankWest3");
    };

    AddEntry(
        "ObjectPlannedWoodWallWestPlank3", "Planned wood wall west, plank 3",
        ObjectFlags::k_unmovable, {POINT_F{0.5f, 0.08f}, POINT_F{0.5f, 0.92f}},
        {"ObjectHammer"}, []() {},
        allImpactPointsCompletedActionObjectWoodWallPlankWest3,
        "ObjectPlannedObject");

    auto allImpactPointsCompletedActionObjectWoodWallPlankWest4 =
        [](std::shared_ptr<Object> object)
    {
        auto worldArea = _<World>().currentWorldArea_;

        auto facedTileCoordinate = _<Player>().facedTileCoordinate_;

        auto facedTile = worldArea->GetTile(facedTileCoordinate);

        facedTile->tileObjects_->TransformObject(object,
                                                 "ObjectWoodWallPlankWest4");
    };

    AddEntry(
        "ObjectPlannedWoodWallWestPlank4", "Planned wood wall west, plank 4",
        ObjectFlags::k_unmovable, {POINT_F{0.5f, 0.08f}, POINT_F{0.5f, 0.92f}},
        {"ObjectHammer"}, []() {},
        allImpactPointsCompletedActionObjectWoodWallPlankWest4,
        "ObjectPlannedObject");

    AddEntry(
        "ObjectWoodWallPlankWest1", "Wood wall", ObjectFlags::k_unmovable, {},
        {}, []() {}, [](std::shared_ptr<Object>) {},
        "ObjectWoodWallPlankWest1WorldView", POINT_F{0.0f, 0.5f});

    AddEntry(
        "ObjectWoodWallPlankWest2", "Wood wall", ObjectFlags::k_unmovable, {},
        {}, []() {}, [](std::shared_ptr<Object>) {},
        "ObjectWoodWallPlankWest2WorldView", POINT_F{0.0f, 0.5f});

    AddEntry(
        "ObjectWoodWallPlankWest3", "Wood wall", ObjectFlags::k_unmovable, {},
        {}, []() {}, [](std::shared_ptr<Object>) {},
        "ObjectWoodWallPlankWest3WorldView", POINT_F{0.0f, 0.5f});

    AddEntry(
        "ObjectWoodWallPlankWest4", "Wood wall", ObjectFlags::k_unmovable, {},
        {}, []() {}, [](std::shared_ptr<Object>) {},
        "ObjectWoodWallPlankWest4WorldView", POINT_F{0.0f, 0.5f});

    auto allImpactPointsCompletedActionObjectWoodFloor =
        [](std::shared_ptr<Object> object)
    {
        auto worldArea = _<World>().currentWorldArea_;

        auto facedTileCoordinate = _<Player>().facedTileCoordinate_;

        auto facedTile = worldArea->GetTile(facedTileCoordinate);

        facedTile->tileObjects_->RemoveObject(object);

        facedTile->ground_ = Hash("GroundWoodFloor");
    };

    AddEntry(
        "ObjectPlannedWoodFloor", "Planned wood floor",
        ObjectFlags::k_unmovable,
        {POINT_F{0.25f, 0.25f}, POINT_F{0.75f, 0.25f}, POINT_F{0.25f, 0.75f},
         POINT_F{0.75f, 0.75f}},
        {"ObjectHammer"}, []() {},
        allImpactPointsCompletedActionObjectWoodFloor, "ObjectPlannedObject",
        POINT_F{0.0f, 0.0f}, POINT_F{0.0f, 0.3f});
}

void ObjectIndex::AddEntry(
    std::string_view name, std::string_view label, int flags,
    std::vector<POINT_F> impactPoints, std::vector<std::string> impactObjects,
    std::function<void()> singleImpactPointCompletedAction,
    std::function<void(std::shared_ptr<Object>)> allImpactPointsCompletedAction,
    std::string_view worldViewObjectType, POINT_F worldViewRenderOffset,
    POINT_F firstPersonViewRenderOffset)
{
    std::vector<int> impactObjectHashes;

    for (auto &impactObject : impactObjects)
    {
        impactObjectHashes.push_back(Hash(impactObject));
    }

    int worldViewObjectTypeHash = 0;

    if (worldViewObjectType != "")
    {
        worldViewObjectTypeHash = Hash(worldViewObjectType);
    }

    entries_.insert({Hash(name),
                     {label.data(), flags, impactPoints, impactObjectHashes,
                      singleImpactPointCompletedAction,
                      allImpactPointsCompletedAction, worldViewObjectTypeHash,
                      worldViewRenderOffset, firstPersonViewRenderOffset}});
}

bool ObjectIndex::IsSmallObject(int objectHash)
{
    if (entries_.contains(objectHash))
    {
        return (entries_.at(objectHash).flags & ObjectFlags::k_smallObject) !=
               0;
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
        return (entries_.at(objectHash).flags & ObjectFlags::k_blocksSight) !=
               0;
    }

    return false;
}

bool ObjectIndex::ObjectUnmovable(int objectHash)
{
    if (entries_.contains(objectHash))
    {
        return (entries_.at(objectHash).flags & ObjectFlags::k_unmovable) != 0;
    }

    return false;
}

std::vector<POINT_F> ObjectIndex::GetImpactPoints(int objectHash)
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

int ObjectIndex::GetWorldViewObjectType(int objectHash)
{
    if (entries_.contains(objectHash))
    {
        return entries_.at(objectHash).worldViewObjectType;
    }

    return 0;
}

POINT_F ObjectIndex::GetWorldViewRenderOffset(int objectHash)
{
    if (entries_.contains(objectHash))
    {
        return entries_.at(objectHash).worldViewRenderOffset;
    }

    return POINT_F{0.0f, 0.0f};
}

POINT_F ObjectIndex::GetFirstPersonViewRenderOffset(int objectHash)
{
    if (entries_.contains(objectHash))
    {
        return entries_.at(objectHash).firstPersonViewRenderOffset;
    }

    return POINT_F{0.0f, 0.0f};
}