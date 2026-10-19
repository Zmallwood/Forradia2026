// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "WorldGenerator.hpp"
#include "Core/CoreGameObjects/Player.hpp"
#include "Core/WorldStructure/Creature.hpp"
#include "Core/WorldStructure/NPC.hpp"
#include "Core/WorldStructure/Tile.hpp"
#include "Core/WorldStructure/TileObjects.hpp"
#include "Core/WorldStructure/World.hpp"
#include "Core/WorldStructure/WorldArea.hpp"

void WorldGenerator::GenerateNewWorld()
{
    ClearWithGrass();

    auto worldArea{_<World>().currentWorldArea_};
    auto size{worldArea->GetSize()};

    for (auto y = 0; y < size.height; y++)
    {
        for (auto x = 0; x < size.width; x++)
        {
            auto tile{worldArea->GetTile(x, y)};
            tile->elevation_ = 1;
        }
    }

    for (auto y = 1; y < size.height - 1; y++)
    {
        for (auto x = 1; x < size.width - 1; x++)
        {
            auto tile{worldArea->GetTile(x, y)};

            auto tileNW{worldArea->GetTile(x - 1, y - 1)};
            auto tileN{worldArea->GetTile(x, y - 1)};
            auto tileNE{worldArea->GetTile(x + 1, y - 1)};
            auto tileW{worldArea->GetTile(x - 1, y)};

            auto groundNW{tileNW->ground_};
            auto groundN{tileN->ground_};
            auto groundNE{tileNE->ground_};
            auto groundW{tileW->ground_};

            if (groundNW == Hash("GroundGrass") &&
                groundN == Hash("GroundGrass") &&
                groundNE == Hash("GroundGrass") &&
                groundW == Hash("GroundGrass"))
            {
                auto makeWater{rand() % 1000 < 3};

                if (makeWater)
                {
                    tile->ground_ = Hash("GroundWater");

                    tileW->ground_ = Hash("GroundWater");

                    tile->elevation_ = 0;
                    tileW->elevation_ = 0;
                }
            }
        }
    }

    auto fnMakeWater = std::function<void(int, int)>(
        [&](int x, int y)
        {
            auto tile{worldArea->GetTile(x, y)};

            auto tileNW{worldArea->GetTile(x - 1, y - 1)};
            auto tileN{worldArea->GetTile(x, y - 1)};
            auto tileNE{worldArea->GetTile(x + 1, y - 1)};
            auto tileW{worldArea->GetTile(x - 1, y)};
            auto tileE{worldArea->GetTile(x + 1, y)};
            auto tileSW{worldArea->GetTile(x - 1, y + 1)};
            auto tileS{worldArea->GetTile(x, y + 1)};
            auto tileSE{worldArea->GetTile(x + 1, y + 1)};

            auto groundNW{tileNW->ground_};
            auto groundN{tileN->ground_};
            auto groundNE{tileNE->ground_};
            auto groundW{tileW->ground_};
            auto groundE{tileE->ground_};
            auto groundSW{tileSW->ground_};
            auto groundS{tileS->ground_};
            auto groundSE{tileSE->ground_};

            auto numWaterTiles{0};

            if (groundNW == Hash("GroundWater"))
            {
                numWaterTiles++;
            }
            if (groundN == Hash("GroundWater"))
            {
                numWaterTiles++;
            }
            if (groundNE == Hash("GroundWater"))
            {
                numWaterTiles++;
            }
            if (groundW == Hash("GroundWater"))
            {
                numWaterTiles++;
            }
            if (groundE == Hash("GroundWater"))
            {
                numWaterTiles++;
            }
            if (groundSW == Hash("GroundWater"))
            {
                numWaterTiles++;
            }
            if (groundS == Hash("GroundWater"))
            {
                numWaterTiles++;
            }
            if (groundSE == Hash("GroundWater"))
            {
                numWaterTiles++;
            }

            if (numWaterTiles == 2)
            {
                auto makeWater{rand() % 1000 < 500};

                if (makeWater)
                {
                    tile->ground_ = Hash("GroundWater");

                    tile->elevation_ = 0;
                }
            }
            else if (numWaterTiles > 2)
            {
                auto makeWater{rand() % 1000 < 600};

                if (makeWater)
                {
                    tile->ground_ = Hash("GroundWater");

                    tile->elevation_ = 0;
                }
            }
        });

    Traverse1(fnMakeWater);
    Traverse2(fnMakeWater);
    Traverse3(fnMakeWater);
    Traverse4(fnMakeWater);

    for (auto y = 1; y < size.height - 1; y++)
    {
        for (auto x = 1; x < size.width - 1; x++)
        {
            auto tile{worldArea->GetTile(x, y)};

            auto tileNW{worldArea->GetTile(x - 1, y - 1)};
            auto tileN{worldArea->GetTile(x, y - 1)};
            auto tileNE{worldArea->GetTile(x + 1, y - 1)};
            auto tileW{worldArea->GetTile(x - 1, y)};

            auto groundNW{tileNW->ground_};
            auto groundN{tileN->ground_};
            auto groundNE{tileNE->ground_};
            auto groundW{tileW->ground_};

            if (groundNW == Hash("GroundGrass") &&
                groundN == Hash("GroundGrass") &&
                groundNE == Hash("GroundGrass") &&
                groundW == Hash("GroundGrass"))
            {
                auto makeDirt{rand() % 1000 < 3};

                if (makeDirt)
                {
                    tile->ground_ = Hash("GroundDirt");

                    tileW->ground_ = Hash("GroundDirt");

                    tile->elevation_ = 1;
                    tileW->elevation_ = 1;
                }
            }
        }
    }

    auto fnMakeDirt = std::function<void(int, int)>(
        [&](int x, int y)
        {
            auto tile{worldArea->GetTile(x, y)};

            auto tileNW{worldArea->GetTile(x - 1, y - 1)};
            auto tileN{worldArea->GetTile(x, y - 1)};
            auto tileNE{worldArea->GetTile(x + 1, y - 1)};
            auto tileW{worldArea->GetTile(x - 1, y)};
            auto tileE{worldArea->GetTile(x + 1, y)};
            auto tileSW{worldArea->GetTile(x - 1, y + 1)};
            auto tileS{worldArea->GetTile(x, y + 1)};
            auto tileSE{worldArea->GetTile(x + 1, y + 1)};

            auto groundNW{tileNW->ground_};
            auto groundN{tileN->ground_};
            auto groundNE{tileNE->ground_};
            auto groundW{tileW->ground_};
            auto groundE{tileE->ground_};
            auto groundSW{tileSW->ground_};
            auto groundS{tileS->ground_};
            auto groundSE{tileSE->ground_};

            auto numDirtTiles{0};

            if (groundNW == Hash("GroundDirt"))
            {
                numDirtTiles++;
            }
            if (groundN == Hash("GroundDirt"))
            {
                numDirtTiles++;
            }
            if (groundNE == Hash("GroundDirt"))
            {
                numDirtTiles++;
            }
            if (groundW == Hash("GroundDirt"))
            {
                numDirtTiles++;
            }
            if (groundE == Hash("GroundDirt"))
            {
                numDirtTiles++;
            }
            if (groundSW == Hash("GroundDirt"))
            {
                numDirtTiles++;
            }
            if (groundS == Hash("GroundDirt"))
            {
                numDirtTiles++;
            }
            if (groundSE == Hash("GroundDirt"))
            {
                numDirtTiles++;
            }

            if (numDirtTiles == 2)
            {
                auto makeDirt{rand() % 1000 < 500};

                if (makeDirt)
                {
                    tile->ground_ = Hash("GroundDirt");

                    tile->elevation_ = 1;
                }
            }
            else if (numDirtTiles > 2)
            {
                auto makeDirt{rand() % 1000 < 600};

                if (makeDirt)
                {
                    tile->ground_ = Hash("GroundDirt");

                    tile->elevation_ = 1;
                }
            }
        });

    Traverse1(fnMakeDirt);
    Traverse2(fnMakeDirt);
    Traverse3(fnMakeDirt);
    Traverse4(fnMakeDirt);

    for (auto y = 1; y < size.height - 1; y++)
    {
        for (auto x = 1; x < size.width - 1; x++)
        {
            auto tile{worldArea->GetTile(x, y)};

            auto tileNW{worldArea->GetTile(x - 1, y - 1)};
            auto tileN{worldArea->GetTile(x, y - 1)};
            auto tileNE{worldArea->GetTile(x + 1, y - 1)};
            auto tileW{worldArea->GetTile(x - 1, y)};

            auto groundNW{tileNW->ground_};
            auto groundN{tileN->ground_};
            auto groundNE{tileNE->ground_};
            auto groundW{tileW->ground_};

            if (groundNW != Hash("GroundWater") &&
                groundN != Hash("GroundWater") &&
                groundNE != Hash("GroundWater") &&
                groundW != Hash("GroundWater"))
            {
                auto increaseElevation{rand() % 1000 < 3};

                if (increaseElevation && tile->ground_ != Hash("GroundWater"))
                {
                    tile->elevation_++;

                    tileW->elevation_++;

                    tile->ground_ = Hash("GroundRock");

                    tileW->ground_ = Hash("GroundRock");
                }
            }
        }
    }

    auto fnMakeMountains = std::function<void(int, int)>(
        [&](int x, int y)
        {
            auto tile{worldArea->GetTile(x, y)};

            auto tileNW{worldArea->GetTile(x - 1, y - 1)};
            auto tileN{worldArea->GetTile(x, y - 1)};
            auto tileNE{worldArea->GetTile(x + 1, y - 1)};
            auto tileW{worldArea->GetTile(x - 1, y)};
            auto tileE{worldArea->GetTile(x + 1, y)};
            auto tileSW{worldArea->GetTile(x - 1, y + 1)};
            auto tileS{worldArea->GetTile(x, y + 1)};
            auto tileSE{worldArea->GetTile(x + 1, y + 1)};

            auto elevationNW{tileNW->elevation_};
            auto elevationN{tileN->elevation_};
            auto elevationNE{tileNE->elevation_};
            auto elevationW{tileW->elevation_};
            auto elevationE{tileE->elevation_};
            auto elevationSW{tileSW->elevation_};
            auto elevationS{tileS->elevation_};
            auto elevationSE{tileSE->elevation_};

            auto elevation{tile->elevation_};

            auto numElevationTiles{0};

            if (tile->ground_ != Hash("GroundWater"))
            {
                if (elevation <= elevationNW && elevationNW > 1)
                {
                    numElevationTiles++;
                }
                if (elevation <= elevationN && elevationN > 1)
                {
                    numElevationTiles++;
                }
                if (elevation <= elevationNE && elevationNE > 1)
                {
                    numElevationTiles++;
                }
                if (elevation <= elevationW && elevationW > 1)
                {
                    numElevationTiles++;
                }
                if (elevation <= elevationE && elevationE > 1)
                {
                    numElevationTiles++;
                }
                if (elevation <= elevationSW && elevationSW > 1)
                {
                    numElevationTiles++;
                }
                if (elevation <= elevationS && elevationS > 1)
                {
                    numElevationTiles++;
                }
                if (elevation <= elevationSE && elevationSE > 1)
                {
                    numElevationTiles++;
                }
            }

            auto maxElevation{std::max(
                elevationNW,
                std::max(
                    elevationN,
                    std::max(
                        elevationNE,
                        std::max(elevationW,
                                 std::max(elevationE,
                                          std::max(elevationSW,
                                                   std::max(elevationS,
                                                            elevationSE)))))))};

            auto usedElevation{elevation};

            if (maxElevation - elevation > 0)
            {
                usedElevation =
                    elevation + rand() % (maxElevation - elevation / 4);
            }

            usedElevation = std::max(usedElevation, elevation + 1);

            if (numElevationTiles == 2)
            {
                auto increaseElevation{rand() % 1000 < 500};

                if (increaseElevation)
                {
                    tile->elevation_ =
                        usedElevation + std::max(0, 1 - rand() % 7);

                    tile->ground_ = Hash("GroundRock");
                }
            }
            else if (numElevationTiles > 2)
            {
                auto increaseElevation{rand() % 1000 < 700};

                if (increaseElevation)
                {
                    tile->elevation_ =
                        usedElevation + std::max(0, 1 - rand() % 4);

                    tile->ground_ = Hash("GroundRock");
                }
            }
        });

    Traverse1(fnMakeMountains);
    Traverse2(fnMakeMountains);
    Traverse3(fnMakeMountains);
    Traverse4(fnMakeMountains);

    auto numHills = 60 + rand() % 10;

    for (auto i = 0; i < numHills; i++)
    {
        auto xCenter{rand() % size.width};
        auto yCenter{rand() % size.height};
        auto radius{3 + rand() % 14};

        for (auto r = radius; r >= 0; r -= (1 + rand() % 2))
        {
            for (auto y = yCenter - radius; y <= yCenter + radius; y++)
            {
                for (auto x = xCenter - radius; x <= xCenter + radius; x++)
                {
                    if (!worldArea->IsValidCoordinate(x, y))
                    {
                        continue;
                    }

                    auto dx = x - xCenter;
                    auto dy = y - yCenter;

                    if (dx * dx + dy * dy <= r * r)
                    {
                        auto tile{worldArea->GetTile(x, y)};

                        if (tile->ground_ == Hash("GroundWater"))
                        {
                            continue;
                        }

                        if (tile->elevation_ >= 5)
                        {
                            continue;
                        }

                        tile->elevation_++;
                    }
                }
            }
        }
    }

    for (auto y = 1; y < size.height - 1; y++)
    {
        for (auto x = 1; x < size.width - 1; x++)
        {
            auto tile{worldArea->GetTile(x, y)};

            auto tileNW{worldArea->GetTile(x - 1, y - 1)};
            auto tileN{worldArea->GetTile(x, y - 1)};
            auto tileNE{worldArea->GetTile(x + 1, y - 1)};
            auto tileW{worldArea->GetTile(x - 1, y)};

            auto groundNW{tileNW->ground_};
            auto groundN{tileN->ground_};
            auto groundNE{tileNE->ground_};
            auto groundW{tileW->ground_};

            if (groundNW != Hash("GroundWater") &&
                groundN != Hash("GroundWater") &&
                groundNE != Hash("GroundWater") &&
                groundW != Hash("GroundWater") &&
                groundNW != Hash("GroundRock") &&
                groundN != Hash("GroundRock") &&
                groundNE != Hash("GroundRock") && groundW != Hash("GroundRock"))
            {
                auto makeTree{rand() % 1000 < 5};

                if (makeTree)
                {
                    if (rand() % 2)
                    {
                        tile->tileObjects_->Clear();

                        tile->tileObjects_->AddObject("ObjectTree1");

                        tileW->tileObjects_->Clear();

                        tileW->tileObjects_->AddObject("ObjectTree1");
                    }
                    else
                    {
                        tile->tileObjects_->Clear();

                        tile->tileObjects_->AddObject("ObjectTree2");

                        tileW->tileObjects_->Clear();

                        tileW->tileObjects_->AddObject("ObjectTree2");
                    }
                }
            }
        }
    }

    auto fnMakeTrees = std::function<void(int, int)>(
        [&](int x, int y)
        {
            auto tile{worldArea->GetTile(x, y)};

            auto tileNW{worldArea->GetTile(x - 1, y - 1)};
            auto tileN{worldArea->GetTile(x, y - 1)};
            auto tileNE{worldArea->GetTile(x + 1, y - 1)};
            auto tileW{worldArea->GetTile(x - 1, y)};
            auto tileE{worldArea->GetTile(x + 1, y)};
            auto tileSW{worldArea->GetTile(x - 1, y + 1)};
            auto tileS{worldArea->GetTile(x, y + 1)};
            auto tileSE{worldArea->GetTile(x + 1, y + 1)};

            auto hasTreeNW{
                tileNW->tileObjects_->HasObjectOfType("ObjectTree1") ||
                tileNW->tileObjects_->HasObjectOfType("ObjectTree2")};
            auto hasTreeN{tileN->tileObjects_->HasObjectOfType("ObjectTree1") ||
                          tileN->tileObjects_->HasObjectOfType("ObjectTree2")};
            auto hasTreeNE{
                tileNE->tileObjects_->HasObjectOfType("ObjectTree1") ||
                tileNE->tileObjects_->HasObjectOfType("ObjectTree2")};
            auto hasTreeW{tileW->tileObjects_->HasObjectOfType("ObjectTree1") ||
                          tileW->tileObjects_->HasObjectOfType("ObjectTree2")};
            auto hasTreeE{tileE->tileObjects_->HasObjectOfType("ObjectTree1") ||
                          tileE->tileObjects_->HasObjectOfType("ObjectTree2")};
            auto hasTreeSW{
                tileSW->tileObjects_->HasObjectOfType("ObjectTree1") ||
                tileSW->tileObjects_->HasObjectOfType("ObjectTree2")};
            auto hasTreeS{tileS->tileObjects_->HasObjectOfType("ObjectTree1") ||
                          tileS->tileObjects_->HasObjectOfType("ObjectTree2")};
            auto hasTreeSE{
                tileSE->tileObjects_->HasObjectOfType("ObjectTree1") ||
                tileSE->tileObjects_->HasObjectOfType("ObjectTree2")};

            auto numTreeTiles{0};

            if (tile->ground_ != Hash("GroundWater") &&
                tile->ground_ != Hash("GroundRock"))
            {
                if (hasTreeNW)
                {
                    numTreeTiles++;
                }
                if (hasTreeN)
                {
                    numTreeTiles++;
                }
                if (hasTreeNE)
                {
                    numTreeTiles++;
                }
                if (hasTreeW)
                {
                    numTreeTiles++;
                }
                if (hasTreeE)
                {
                    numTreeTiles++;
                }
                if (hasTreeSW)
                {
                    numTreeTiles++;
                }
                if (hasTreeS)
                {
                    numTreeTiles++;
                }
                if (hasTreeSE)
                {
                    numTreeTiles++;
                }
            }

            if (numTreeTiles == 2)
            {
                auto makeTree{rand() % 1000 < 700};

                if (makeTree)
                {
                    if (rand() % 2 % 2)
                    {
                        tile->tileObjects_->Clear();

                        tile->tileObjects_->AddObject("ObjectTree1");
                    }
                    else if (rand() % 2)
                    {
                        tile->tileObjects_->Clear();

                        tile->tileObjects_->AddObject("ObjectTree2");
                    }
                }
            }
            else if (numTreeTiles > 2)
            {
                auto makeTree{rand() % 1000 < 900};

                if (makeTree)
                {
                    if (rand() % 2)
                    {
                        tile->tileObjects_->Clear();
                        tile->tileObjects_->AddObject("ObjectTree1");
                    }
                    else if (rand() % 2)
                    {
                        tile->tileObjects_->Clear();
                        tile->tileObjects_->AddObject("ObjectTree2");
                    }
                }
            }
        });

    Traverse1(fnMakeTrees);
    Traverse2(fnMakeTrees);
    Traverse3(fnMakeTrees);
    Traverse4(fnMakeTrees);

    // GenerateDirt();

    // GenerateWater();

    // GenerateElevation();

    // GenerateRock();

    GenerateLargeObjects();

    GenerateSmallObjects();

    GenerateCreatures();
}

void WorldGenerator::Traverse1(std::function<void(int, int)> callback)
{
    auto worldArea{_<World>().currentWorldArea_};
    auto size{worldArea->GetSize()};

    for (auto y = 1; y < size.height - 1; y++)
    {
        for (auto x = 1; x < size.width - 1; x++)
        {
            callback(x, y);
        }
    }
}

void WorldGenerator::Traverse2(std::function<void(int, int)> callback)
{
    auto worldArea{_<World>().currentWorldArea_};
    auto size{worldArea->GetSize()};

    for (auto x = 1; x < size.width - 1; x++)
    {
        for (auto y = 1; y < size.height - 1; y++)
        {
            callback(x, y);
        }
    }
}

void WorldGenerator::Traverse3(std::function<void(int, int)> callback)
{
    auto worldArea{_<World>().currentWorldArea_};
    auto size{worldArea->GetSize()};

    for (auto y = size.height - 2; y > 0; y--)
    {
        for (auto x = 1; x < size.width - 1; x++)
        {
            callback(x, y);
        }
    }
}

void WorldGenerator::Traverse4(std::function<void(int, int)> callback)
{
    auto worldArea{_<World>().currentWorldArea_};
    auto size{worldArea->GetSize()};

    for (auto x = size.width - 2; x > 0; x--)
    {
        for (auto y = 1; y < size.height - 1; y++)
        {
            callback(x, y);
        }
    }
}

void WorldGenerator::ClearWithGrass()
{
    auto worldArea{_<World>().currentWorldArea_};
    auto size{worldArea->GetSize()};

    for (auto y = 0; y < size.height; y++)
    {
        for (auto x = 0; x < size.width; x++)
        {
            auto tile{worldArea->GetTile(x, y)};

            tile->ground_ = Hash("GroundGrass");
        }
    }
}

// void WorldGenerator::GenerateDirt()
// {
//     auto worldArea{_<World>().currentWorldArea_};
//     auto size{worldArea->GetSize()};

//     auto numDirtPatches{15 + rand() % 8};

//     for (auto i = 0; i < numDirtPatches; i++)
//     {
//         auto xCenter{rand() % size.width};
//         auto yCenter{rand() % size.height};
//         auto radius{3 + rand() % 14};

//         for (auto y = yCenter - radius; y <= yCenter + radius; y++)
//         {
//             for (auto x = xCenter - radius; x <= xCenter + radius; x++)
//             {
//                 if (!worldArea->IsValidCoordinate(x, y))
//                 {
//                     continue;
//                 }

//                 auto dx{x - xCenter};
//                 auto dy{y - yCenter};

//                 if (dx * dx + dy * dy <= radius * radius)
//                 {
//                     auto tile{worldArea->GetTile(x, y)};

//                     tile->ground_ = Hash("GroundDirt");
//                 }
//             }
//         }
//     }
// }

// void WorldGenerator::GenerateWater()
// {
//     auto worldArea{_<World>().currentWorldArea_};
//     auto size{worldArea->GetSize()};

//     auto numLakes{40 + rand() % 20};

//     for (auto i = 0; i < numLakes; i++)
//     {
//         auto xCenter{rand() % size.width};
//         auto yCenter{rand() % size.height};
//         auto radius{3 + rand() % 6};

//         for (auto y = yCenter - radius; y <= yCenter + radius; y++)
//         {
//             for (auto x = xCenter - radius; x <= xCenter + radius; x++)
//             {
//                 if (!worldArea->IsValidCoordinate(x, y))
//                 {
//                     continue;
//                 }

//                 auto dx{x - xCenter};
//                 auto dy{y - yCenter};

//                 if (dx * dx + dy * dy <= radius * radius)
//                 {
//                     auto tile{worldArea->GetTile(x, y)};

//                     tile->ground_ = Hash("GroundWater");
//                 }
//             }
//         }
//     }
// }

// void WorldGenerator::GenerateElevation()
// {
//     auto worldArea{_<World>().currentWorldArea_};
//     auto size{worldArea->GetSize()};

//     for (auto y = 0; y < size.height; y++)
//     {
//         for (auto x = 0; x < size.width; x++)
//         {
//             auto tile{worldArea->GetTile(x, y)};

//             if (tile->ground_ != Hash("GroundWater"))
//             {
//                 tile->elevation_ = 1;
//             }
//         }
//     }

//     auto numHills{20 + rand() % 10};

//     for (auto i = 0; i < numHills; i++)
//     {
//         auto xCenter{rand() % size.width};
//         auto yCenter{rand() % size.height};
//         auto radius{3 + rand() % 9};

//         for (auto r = radius; r >= 0; r--)
//         {
//             for (auto y = yCenter - r; y <= yCenter + r; y++)
//             {
//                 for (auto x = xCenter - r; x <= xCenter + r; x++)
//                 {
//                     if (!worldArea->IsValidCoordinate(x, y))
//                     {
//                         continue;
//                     }

//                     auto dx{x - xCenter};
//                     auto dy{y - yCenter};

//                     if (dx * dx + dy * dy <= r * r)
//                     {
//                         auto tile{worldArea->GetTile(x, y)};

//                         if (tile->ground_ == Hash("GroundWater"))
//                         {
//                             continue;
//                         }

//                         ++tile->elevation_;
//                     }
//                 }
//             }
//         }
//     }
// }

// void WorldGenerator::GenerateRock()
// {
//     auto worldArea{_<World>().currentWorldArea_};
//     auto size{worldArea->GetSize()};

//     auto numRockPatches{60 + rand() % 5};

//     for (auto i = 0; i < numRockPatches; i++)
//     {
//         auto xCenter{rand() % size.width};
//         auto yCenter{rand() % size.height};
//         auto radius{3 + rand() % 9};

//         for (auto y = yCenter - radius; y <= yCenter + radius; y++)
//         {
//             for (auto x = xCenter - radius; x <= xCenter + radius; x++)
//             {
//                 if (!worldArea->IsValidCoordinate(x, y))
//                 {
//                     continue;
//                 }

//                 auto dx{x - xCenter};
//                 auto dy{y - yCenter};

//                 if (dx * dx + dy * dy <= radius * radius)
//                 {
//                     auto tile{worldArea->GetTile(x, y)};

//                     if (tile->elevation_ >= 2)
//                     {
//                         tile->ground_ = Hash("GroundRock");
//                     }
//                 }
//             }
//         }
//     }
// }

void WorldGenerator::GenerateLargeObjects()
{
    auto worldArea{_<World>().currentWorldArea_};
    auto size{worldArea->GetSize()};

    // auto numTree2Groups{100 + rand() % 10};

    // for (auto i = 0; i < numTree2Groups; i++)
    // {
    //     auto x{rand() % size.width};
    //     auto y{rand() % size.height};

    //     auto numTree2s{60 + rand() % 10};

    //     for (auto j = 0; j < numTree2s; j++)
    //     {
    //         x += rand() % 3 - rand() % 3;
    //         y += rand() % 3 - rand() % 3;

    //         if (!worldArea->IsValidCoordinate(x, y))
    //         {
    //             continue;
    //         }

    //         auto tile{worldArea->GetTile(x, y)};

    //         if (tile->ground_ == Hash("GroundWater") ||
    //             tile->ground_ == Hash("GroundRock"))
    //         {
    //             continue;
    //         }

    //         tile->tileObjects_->Clear();

    //         tile->tileObjects_->AddObject("ObjectTree2");
    //     }
    // }

    // auto numTree1Groups{100 + rand() % 10};

    // for (auto i = 0; i < numTree1Groups; i++)
    // {
    //     auto x{rand() % size.width};
    //     auto y{rand() % size.height};

    //     auto numTree1s{60 + rand() % 10};

    //     for (auto j = 0; j < numTree1s; j++)
    //     {
    //         x += rand() % 3 - rand() % 3;
    //         y += rand() % 3 - rand() % 3;

    //         if (!worldArea->IsValidCoordinate(x, y))
    //         {
    //             continue;
    //         }

    //         auto tile{worldArea->GetTile(x, y)};

    //         if (tile->ground_ == Hash("GroundWater") ||
    //             tile->ground_ == Hash("GroundRock"))
    //         {
    //             continue;
    //         }

    //         tile->tileObjects_->Clear();

    //         tile->tileObjects_->AddObject("ObjectTree1");
    //     }
    // }

    auto numBush1s{100 + rand() % 30};

    for (auto i = 0; i < numBush1s; i++)
    {
        auto x{rand() % size.width};
        auto y{rand() % size.height};

        auto tile{worldArea->GetTile(x, y)};

        if (tile->ground_ == Hash("GroundWater") ||
            tile->ground_ == Hash("GroundDirt") ||
            tile->ground_ == Hash("GroundRock"))
        {
            continue;
        }

        tile->tileObjects_->AddObject("ObjectBush1");
    }

    auto numStoneBoulders{100 + rand() % 50};

    for (auto i = 0; i < numStoneBoulders; i++)
    {
        auto x{rand() % size.width};
        auto y{rand() % size.height};

        auto tile{worldArea->GetTile(x, y)};

        if (tile->ground_ == Hash("GroundGrass") ||
            tile->ground_ == Hash("GroundDirt"))
        {
            continue;
        }

        tile->tileObjects_->AddObject("ObjectStoneBoulder");
    }

    auto numTree1s{100 + rand() % 50};

    for (auto i = 0; i < numTree1s; i++)
    {
        auto x{rand() % size.width};
        auto y{rand() % size.height};

        auto tile{worldArea->GetTile(x, y)};

        if (tile->ground_ == Hash("GroundGrass") ||
            tile->ground_ == Hash("GroundDirt"))
        {
            tile->tileObjects_->AddObject("ObjectTree1");
        }
    }

    auto numTree2s{100 + rand() % 50};

    for (auto i = 0; i < numTree2s; i++)
    {
        auto x{rand() % size.width};
        auto y{rand() % size.height};

        auto tile{worldArea->GetTile(x, y)};

        if (tile->ground_ == Hash("GroundGrass") ||
            tile->ground_ == Hash("GroundDirt"))
        {
            tile->tileObjects_->AddObject("ObjectTree2");
        }
    }
}

void WorldGenerator::GenerateSmallObjects()
{
    auto worldArea{_<World>().currentWorldArea_};
    auto size{worldArea->GetSize()};

    auto numStones{500 + rand() % 50};

    for (auto i = 0; i < numStones; i++)
    {
        auto x{rand() % size.width};
        auto y{rand() % size.height};

        auto tile{worldArea->GetTile(x, y)};

        if (tile->ground_ == Hash("GroundWater"))
        {
            continue;
        }

        tile->tileObjects_->AddObject("ObjectStone");
    }

    auto numBranches{500 + rand() % 50};

    for (auto i = 0; i < numBranches; i++)
    {
        auto x{rand() % size.width};
        auto y{rand() % size.height};

        auto tile{worldArea->GetTile(x, y)};

        if (tile->ground_ == Hash("GroundWater") ||
            tile->ground_ == Hash("GroundRock"))
        {
            continue;
        }

        tile->tileObjects_->AddObject("ObjectBranch");
    }

    auto numPinkFlowers{500 + rand() % 50};

    for (auto i = 0; i < numPinkFlowers; i++)
    {
        auto x{rand() % size.width};
        auto y{rand() % size.height};

        auto tile{worldArea->GetTile(x, y)};

        if (tile->ground_ == Hash("GroundWater") ||
            tile->ground_ == Hash("GroundRock") ||
            tile->ground_ == Hash("GroundDirt"))
        {
            continue;
        }

        tile->tileObjects_->AddObject("ObjectPinkFlower");
    }

    auto numLeaves{500 + rand() % 50};

    for (auto i = 0; i < numLeaves; i++)
    {
        auto x{rand() % size.width};
        auto y{rand() % size.height};

        auto tile{worldArea->GetTile(x, y)};

        if (tile->ground_ == Hash("GroundWater") ||
            tile->ground_ == Hash("GroundRock"))
        {
            continue;
        }

        tile->tileObjects_->AddObject("ObjectLeaf");
    }
}

void WorldGenerator::GenerateCreatures()
{
    auto worldArea{_<World>().currentWorldArea_};
    auto size{worldArea->GetSize()};

    // auto numDeers{150 + rand() % 20};
    auto numDeers{40 + rand() % 10};

    for (auto i = 0; i < numDeers; i++)
    {
        auto x{rand() % size.width};
        auto y{rand() % size.height};

        auto tile{worldArea->GetTile(x, y)};

        if (tile->ground_ == Hash("GroundWater") ||
            tile->ground_ == Hash("GroundRock"))
        {
            continue;
        }

        auto newCreature{std::make_shared<Creature>("CreatureDeer")};

        worldArea->creaturesMirror_.insert({newCreature, {x, y}});

        tile->creature_ = newCreature;
    }

    // auto numBoars{150 + rand() % 20};
    auto numBoars{40 + rand() % 10};

    for (auto i = 0; i < numBoars; i++)
    {
        auto x{rand() % size.width};
        auto y{rand() % size.height};

        auto tile{worldArea->GetTile(x, y)};

        if (tile->ground_ == Hash("GroundWater") ||
            tile->ground_ == Hash("GroundRock"))
        {
            continue;
        }

        auto newCreature{std::make_shared<Creature>("CreatureBoar")};

        worldArea->creaturesMirror_.insert({newCreature, {x, y}});
    }
}

void WorldGenerator::GenerateCivilization()
{
    // auto worldArea{_<World>().currentWorldArea_};
    // auto size{worldArea->GetSize()};

    // auto playerPosition{_<Player>().position_};

    // auto prevXTileElevation{0};

    // for (auto x = 0; x < size.width; x++)
    // {
    //     auto tile{worldArea->GetTile(x, playerPosition.y)};

    //     tile->tileObjects_->Clear();

    //     tile->ground_ = Hash("GroundCobblestone");

    //     auto elevDifference{tile->elevation_ - prevXTileElevation};

    //     if (elevDifference)
    //     {
    //         tile->elevation_ =
    //             prevXTileElevation + elevDifference /
    //             std::abs(elevDifference);
    //     }

    //     prevXTileElevation = tile->elevation_;
    // }

    // auto prevYTileElevation{0};

    // for (auto y = 0; y < size.height; y++)
    // {
    //     auto tile{worldArea->GetTile(playerPosition.x, y)};

    //     tile->tileObjects_->Clear();

    //     tile->ground_ = Hash("GroundCobblestone");

    //     auto elevDifference{tile->elevation_ - prevYTileElevation};

    //     if (elevDifference)
    //     {
    //         tile->elevation_ =
    //         prevYTileElevation + elevDifference /
    //         std::abs(elevDifference);
    //     }

    //     prevYTileElevation = tile->elevation_;
    // }

    // for (auto y = playerPosition.y - 1; y <= playerPosition.y + 1; y++)
    // {
    //     for (auto x = playerPosition.x - 1; x <= playerPosition.x + 1;
    //     x++)
    //     {
    //         auto tile{worldArea->GetTile(x, y)};

    //         tile->tileObjects_->Clear();

    //         tile->ground_ = Hash("GroundCobblestone");
    //     }
    // }

    // auto tileNorthWest{
    //     worldArea->GetTile(playerPosition.x - 1, playerPosition.y - 1)};

    // tileNorthWest->npc_ = std::make_shared<NPC>("NPC0");

    // auto tileNorthEast{
    //     worldArea->GetTile(playerPosition.x + 1, playerPosition.y - 1)};

    // tileNorthEast->npc_ = std::make_shared<NPC>("NPC1");
}

void WorldGenerator::GenerateWorldAroundPlayer()
{
    // auto worldArea{_<World>().currentWorldArea_};
    // auto size{worldArea->GetSize()};

    // Point playerPosition{static_cast<int>(_<Player>().position_.x),
    //                      static_cast<int>(_<Player>().position_.y)};

    // for (auto y = playerPosition.y - 4; y <= playerPosition.y + 4; y++)
    // {
    //     for (auto x = playerPosition.x - 4; x <= playerPosition.x + 4; x++)
    //     {
    //         auto tile{worldArea->GetTile(x, y)};

    //         if (!tile)
    //         {
    //             continue;
    //         }

    //         tile->tileObjects_->Clear();

    //         tile->ground_ = Hash("GroundGrass");

    //         tile->elevation_ = 1;
    //     }
    // }
}