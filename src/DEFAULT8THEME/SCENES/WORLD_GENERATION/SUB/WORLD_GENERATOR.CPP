// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"
#include "CORE/WORLD8STRUCTURE/CREATURE.HPP"
#include "CORE/WORLD8STRUCTURE/NPC.HPP"
#include "CORE/WORLD8STRUCTURE/TILE.HPP"
#include "CORE/WORLD8STRUCTURE/TILE8OBJECTS.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD_AREA.HPP"
#include "WORLD_GENERATOR.HPP"

void
WorldGenerator::GenerateNewWorld()
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

            if (groundNW == HASH("GroundGrass") &&
                groundN == HASH("GroundGrass") &&
                groundNE == HASH("GroundGrass") &&
                groundW == HASH("GroundGrass"))
            {
                auto makeWater{rand() % 1000 < 3};

                if (makeWater)
                {
                    tile->ground_ = HASH("GroundWater");

                    tileW->ground_ = HASH("GroundWater");

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

            if (groundNW == HASH("GroundWater"))
            {
                numWaterTiles++;
            }
            if (groundN == HASH("GroundWater"))
            {
                numWaterTiles++;
            }
            if (groundNE == HASH("GroundWater"))
            {
                numWaterTiles++;
            }
            if (groundW == HASH("GroundWater"))
            {
                numWaterTiles++;
            }
            if (groundE == HASH("GroundWater"))
            {
                numWaterTiles++;
            }
            if (groundSW == HASH("GroundWater"))
            {
                numWaterTiles++;
            }
            if (groundS == HASH("GroundWater"))
            {
                numWaterTiles++;
            }
            if (groundSE == HASH("GroundWater"))
            {
                numWaterTiles++;
            }

            if (numWaterTiles == 2)
            {
                auto makeWater{rand() % 1000 < 500};

                if (makeWater)
                {
                    tile->ground_ = HASH("GroundWater");

                    tile->elevation_ = 0;
                }
            }
            else if (numWaterTiles > 2)
            {
                auto makeWater{rand() % 1000 < 600};

                if (makeWater)
                {
                    tile->ground_ = HASH("GroundWater");

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

            if (groundNW == HASH("GroundGrass") &&
                groundN == HASH("GroundGrass") &&
                groundNE == HASH("GroundGrass") &&
                groundW == HASH("GroundGrass"))
            {
                auto makeDirt{rand() % 1000 < 3};

                if (makeDirt)
                {
                    tile->ground_ = HASH("GroundDirt");

                    tileW->ground_ = HASH("GroundDirt");

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

            if (groundNW == HASH("GroundDirt"))
            {
                numDirtTiles++;
            }
            if (groundN == HASH("GroundDirt"))
            {
                numDirtTiles++;
            }
            if (groundNE == HASH("GroundDirt"))
            {
                numDirtTiles++;
            }
            if (groundW == HASH("GroundDirt"))
            {
                numDirtTiles++;
            }
            if (groundE == HASH("GroundDirt"))
            {
                numDirtTiles++;
            }
            if (groundSW == HASH("GroundDirt"))
            {
                numDirtTiles++;
            }
            if (groundS == HASH("GroundDirt"))
            {
                numDirtTiles++;
            }
            if (groundSE == HASH("GroundDirt"))
            {
                numDirtTiles++;
            }

            if (numDirtTiles == 2)
            {
                auto makeDirt{rand() % 1000 < 500};

                if (makeDirt)
                {
                    tile->ground_ = HASH("GroundDirt");

                    tile->elevation_ = 1;
                }
            }
            else if (numDirtTiles > 2)
            {
                auto makeDirt{rand() % 1000 < 600};

                if (makeDirt)
                {
                    tile->ground_ = HASH("GroundDirt");

                    tile->elevation_ = 1;
                }
            }
        });

    Traverse1(fnMakeDirt);
    Traverse2(fnMakeDirt);
    Traverse3(fnMakeDirt);
    Traverse4(fnMakeDirt);

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

                        if (tile->ground_ == HASH("GroundWater") &&
                            tile->ground_ != HASH("GroundRock"))
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

    auto numMountains = 40 + rand() % 10;

    for (auto i = 0; i < numMountains; i++)
    {
        auto xCenter{rand() % size.width};
        auto yCenter{rand() % size.height};
        auto radius{3 + rand() % 8};

        for (auto r = radius; r >= 0; r -= 2 + rand() % 6)
        {
            auto elevationChange = 3 + rand() % 3;

            for (auto y = yCenter - r; y <= yCenter + r; y++)
            {
                for (auto x = xCenter - r; x <= xCenter + r; x++)
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

                        if (tile->ground_ == HASH("GroundWater"))
                        {
                            continue;
                        }

                        tile->elevation_ += elevationChange;

                        tile->ground_ = HASH("GroundRock");

                        if (rand() % 5 == 0)
                        {
                            tile->tileObjects_->CLEAR();

                            tile->tileObjects_->ADD8OBJECT(
                                "ObjectStoneBoulder");
                        }
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

            if (groundNW != HASH("GroundWater") &&
                groundN != HASH("GroundWater") &&
                groundNE != HASH("GroundWater") &&
                groundW != HASH("GroundWater") &&
                groundNW != HASH("GroundRock") &&
                groundN != HASH("GroundRock") &&
                groundNE != HASH("GroundRock") && groundW != HASH("GroundRock"))
            {
                auto makeTree{rand() % 1000 < 5};

                if (makeTree)
                {
                    if (rand() % 2)
                    {
                        tile->tileObjects_->CLEAR();

                        tile->tileObjects_->ADD8OBJECT("ObjectTree1");

                        tileW->tileObjects_->CLEAR();

                        tileW->tileObjects_->ADD8OBJECT("ObjectTree1");
                    }
                    else
                    {
                        tile->tileObjects_->CLEAR();

                        tile->tileObjects_->ADD8OBJECT("ObjectTree2");

                        tileW->tileObjects_->CLEAR();

                        tileW->tileObjects_->ADD8OBJECT("ObjectTree2");
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
                tileNW->tileObjects_->HAS8OBJECT8OF8TYPE("ObjectTree1") ||
                tileNW->tileObjects_->HAS8OBJECT8OF8TYPE("ObjectTree2")};
            auto hasTreeN{
                tileN->tileObjects_->HAS8OBJECT8OF8TYPE("ObjectTree1") ||
                tileN->tileObjects_->HAS8OBJECT8OF8TYPE("ObjectTree2")};
            auto hasTreeNE{
                tileNE->tileObjects_->HAS8OBJECT8OF8TYPE("ObjectTree1") ||
                tileNE->tileObjects_->HAS8OBJECT8OF8TYPE("ObjectTree2")};
            auto hasTreeW{
                tileW->tileObjects_->HAS8OBJECT8OF8TYPE("ObjectTree1") ||
                tileW->tileObjects_->HAS8OBJECT8OF8TYPE("ObjectTree2")};
            auto hasTreeE{
                tileE->tileObjects_->HAS8OBJECT8OF8TYPE("ObjectTree1") ||
                tileE->tileObjects_->HAS8OBJECT8OF8TYPE("ObjectTree2")};
            auto hasTreeSW{
                tileSW->tileObjects_->HAS8OBJECT8OF8TYPE("ObjectTree1") ||
                tileSW->tileObjects_->HAS8OBJECT8OF8TYPE("ObjectTree2")};
            auto hasTreeS{
                tileS->tileObjects_->HAS8OBJECT8OF8TYPE("ObjectTree1") ||
                tileS->tileObjects_->HAS8OBJECT8OF8TYPE("ObjectTree2")};
            auto hasTreeSE{
                tileSE->tileObjects_->HAS8OBJECT8OF8TYPE("ObjectTree1") ||
                tileSE->tileObjects_->HAS8OBJECT8OF8TYPE("ObjectTree2")};

            auto numTreeTiles{0};

            if (tile->ground_ != HASH("GroundWater") &&
                tile->ground_ != HASH("GroundRock"))
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
                        tile->tileObjects_->CLEAR();

                        tile->tileObjects_->ADD8OBJECT("ObjectTree1");
                    }
                    else if (rand() % 2)
                    {
                        tile->tileObjects_->CLEAR();

                        tile->tileObjects_->ADD8OBJECT("ObjectTree2");
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
                        tile->tileObjects_->CLEAR();
                        tile->tileObjects_->ADD8OBJECT("ObjectTree1");
                    }
                    else if (rand() % 2)
                    {
                        tile->tileObjects_->CLEAR();
                        tile->tileObjects_->ADD8OBJECT("ObjectTree2");
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

void
WorldGenerator::Traverse1(std::function<void(int, int)> callback)
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

void
WorldGenerator::Traverse2(std::function<void(int, int)> callback)
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

void
WorldGenerator::Traverse3(std::function<void(int, int)> callback)
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

void
WorldGenerator::Traverse4(std::function<void(int, int)> callback)
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

void
WorldGenerator::ClearWithGrass()
{
    auto worldArea{_<World>().currentWorldArea_};
    auto size{worldArea->GetSize()};

    for (auto y = 0; y < size.height; y++)
    {
        for (auto x = 0; x < size.width; x++)
        {
            auto tile{worldArea->GetTile(x, y)};

            tile->ground_ = HASH("GroundGrass");
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

//                     tile->ground_ = HASH("GroundDirt");
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

//                     tile->ground_ = HASH("GroundWater");
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

//             if (tile->ground_ != HASH("GroundWater"))
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

//                         if (tile->ground_ == HASH("GroundWater"))
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
//                         tile->ground_ = HASH("GroundRock");
//                     }
//                 }
//             }
//         }
//     }
// }

void
WorldGenerator::GenerateLargeObjects()
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

    //         if (tile->ground_ == HASH("GroundWater") ||
    //             tile->ground_ == HASH("GroundRock"))
    //         {
    //             continue;
    //         }

    //         tile->tileObjects_->CLEAR();

    //         tile->tileObjects_->ADD8OBJECT("ObjectTree2");
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

    //         if (tile->ground_ == HASH("GroundWater") ||
    //             tile->ground_ == HASH("GroundRock"))
    //         {
    //             continue;
    //         }

    //         tile->tileObjects_->CLEAR();

    //         tile->tileObjects_->ADD8OBJECT("ObjectTree1");
    //     }
    // }

    auto numBush1s{100 + rand() % 30};

    for (auto i = 0; i < numBush1s; i++)
    {
        auto x{rand() % size.width};
        auto y{rand() % size.height};

        auto tile{worldArea->GetTile(x, y)};

        if (tile->ground_ == HASH("GroundWater") ||
            tile->ground_ == HASH("GroundDirt") ||
            tile->ground_ == HASH("GroundRock"))
        {
            continue;
        }

        tile->tileObjects_->ADD8OBJECT("ObjectBush1");
    }

    auto numBush2s{100 + rand() % 30};

    for (auto i = 0; i < numBush2s; i++)
    {
        auto x{rand() % size.width};
        auto y{rand() % size.height};

        auto tile{worldArea->GetTile(x, y)};

        if (tile->ground_ == HASH("GroundWater") ||
            tile->ground_ == HASH("GroundDirt") ||
            tile->ground_ == HASH("GroundRock"))
        {
            continue;
        }

        tile->tileObjects_->ADD8OBJECT("ObjectBush2");
    }

    auto numStoneBoulders{100 + rand() % 50};

    for (auto i = 0; i < numStoneBoulders; i++)
    {
        auto x{rand() % size.width};
        auto y{rand() % size.height};

        auto tile{worldArea->GetTile(x, y)};

        if (tile->ground_ == HASH("GroundGrass") ||
            tile->ground_ == HASH("GroundDirt"))
        {
            continue;
        }

        tile->tileObjects_->ADD8OBJECT("ObjectStoneBoulder");
    }

    auto numTree1s{100 + rand() % 50};

    for (auto i = 0; i < numTree1s; i++)
    {
        auto x{rand() % size.width};
        auto y{rand() % size.height};

        auto tile{worldArea->GetTile(x, y)};

        if (tile->ground_ == HASH("GroundGrass") ||
            tile->ground_ == HASH("GroundDirt"))
        {
            tile->tileObjects_->ADD8OBJECT("ObjectTree1");
        }
    }

    auto numTree2s{100 + rand() % 50};

    for (auto i = 0; i < numTree2s; i++)
    {
        auto x{rand() % size.width};
        auto y{rand() % size.height};

        auto tile{worldArea->GetTile(x, y)};

        if (tile->ground_ == HASH("GroundGrass") ||
            tile->ground_ == HASH("GroundDirt"))
        {
            tile->tileObjects_->ADD8OBJECT("ObjectTree2");
        }
    }
}

void
WorldGenerator::GenerateSmallObjects()
{
    auto worldArea{_<World>().currentWorldArea_};
    auto size{worldArea->GetSize()};

    auto numStones{500 + rand() % 50};

    for (auto i = 0; i < numStones; i++)
    {
        auto x{rand() % size.width};
        auto y{rand() % size.height};

        auto tile{worldArea->GetTile(x, y)};

        if (tile->ground_ == HASH("GroundWater"))
        {
            continue;
        }

        tile->tileObjects_->ADD8OBJECT("ObjectStone");
    }

    auto numBranches{500 + rand() % 50};

    for (auto i = 0; i < numBranches; i++)
    {
        auto x{rand() % size.width};
        auto y{rand() % size.height};

        auto tile{worldArea->GetTile(x, y)};

        if (tile->ground_ == HASH("GroundWater") ||
            tile->ground_ == HASH("GroundRock"))
        {
            continue;
        }

        tile->tileObjects_->ADD8OBJECT("ObjectBranch");
    }

    auto numPinkFlowers{500 + rand() % 50};

    for (auto i = 0; i < numPinkFlowers; i++)
    {
        auto x{rand() % size.width};
        auto y{rand() % size.height};

        auto tile{worldArea->GetTile(x, y)};

        if (tile->ground_ == HASH("GroundWater") ||
            tile->ground_ == HASH("GroundRock") ||
            tile->ground_ == HASH("GroundDirt"))
        {
            continue;
        }

        tile->tileObjects_->ADD8OBJECT("ObjectPinkFlower");
    }

    auto numLeaves{500 + rand() % 50};

    for (auto i = 0; i < numLeaves; i++)
    {
        auto x{rand() % size.width};
        auto y{rand() % size.height};

        auto tile{worldArea->GetTile(x, y)};

        if (tile->ground_ == HASH("GroundWater") ||
            tile->ground_ == HASH("GroundRock"))
        {
            continue;
        }

        tile->tileObjects_->ADD8OBJECT("ObjectLeaf");
    }
}

void
WorldGenerator::GenerateCreatures()
{
    auto worldArea{_<World>().currentWorldArea_};
    auto size{worldArea->GetSize()};

    // auto numDeers{150 + rand() % 20};
    auto numDeers{80 + rand() % 10};

    for (auto i = 0; i < numDeers; i++)
    {
        auto x{rand() % size.width};
        auto y{rand() % size.height};

        auto tile{worldArea->GetTile(x, y)};

        if (tile->ground_ == HASH("GroundWater") ||
            tile->ground_ == HASH("GroundRock"))
        {
            continue;
        }

        auto newCreature{std::make_shared<CREATURE>("CreatureDeer")};

        worldArea->creaturesMirror_.insert({newCreature, {x, y}});

        tile->creature_ = newCreature;
    }

    // auto numBoars{150 + rand() % 20};
    auto numBoars{80 + rand() % 10};

    for (auto i = 0; i < numBoars; i++)
    {
        auto x{rand() % size.width};
        auto y{rand() % size.height};

        auto tile{worldArea->GetTile(x, y)};

        if (tile->ground_ == HASH("GroundWater") ||
            tile->ground_ == HASH("GroundRock"))
        {
            continue;
        }

        auto newCreature{std::make_shared<CREATURE>("CreatureBoar")};

        worldArea->creaturesMirror_.insert({newCreature, {x, y}});
    }
    
    auto numButterflies{80 + rand() % 10};

    for (auto i = 0; i < numButterflies; i++)
    {
        auto x{rand() % size.width};
        auto y{rand() % size.height};

        auto tile{worldArea->GetTile(x, y)};

        if (tile->ground_ == HASH("GroundWater") ||
            tile->ground_ == HASH("GroundRock"))
        {
            continue;
        }

        auto newCreature{std::make_shared<CREATURE>("CreatureButterfly")};

        worldArea->creaturesMirror_.insert({newCreature, {x, y}});
    }
    
    auto numRedBirds{80 + rand() % 10};

    for (auto i = 0; i < numRedBirds; i++)
    {
        auto x{rand() % size.width};
        auto y{rand() % size.height};

        auto tile{worldArea->GetTile(x, y)};

        if (tile->ground_ == HASH("GroundWater") ||
            tile->ground_ == HASH("GroundRock"))
        {
            continue;
        }

        auto newCreature{std::make_shared<CREATURE>("CreatureRedBird")};

        worldArea->creaturesMirror_.insert({newCreature, {x, y}});
    }
    
    auto numWhiteRabbits{80 + rand() % 10};

    for (auto i = 0; i < numWhiteRabbits; i++)
    {
        auto x{rand() % size.width};
        auto y{rand() % size.height};

        auto tile{worldArea->GetTile(x, y)};

        if (tile->ground_ == HASH("GroundWater") ||
            tile->ground_ == HASH("GroundRock"))
        {
            continue;
        }

        auto newCreature{std::make_shared<CREATURE>("CreatureWhiteRabbit")};

        worldArea->creaturesMirror_.insert({newCreature, {x, y}});
    }
}

void
WorldGenerator::GenerateCivilization()
{
    // auto worldArea{_<World>().currentWorldArea_};
    // auto size{worldArea->GetSize()};

    // auto playerPosition{_<PLAYER>().position_};

    // auto prevXTileElevation{0};

    // for (auto x = 0; x < size.width; x++)
    // {
    //     auto tile{worldArea->GetTile(x, playerPosition.y)};

    //     tile->tileObjects_->CLEAR();

    //     tile->ground_ = HASH("GroundCobblestone");

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

    //     tile->tileObjects_->CLEAR();

    //     tile->ground_ = HASH("GroundCobblestone");

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

    //         tile->tileObjects_->CLEAR();

    //         tile->ground_ = HASH("GroundCobblestone");
    //     }
    // }

    // auto tileNorthWest{
    //     worldArea->GetTile(playerPosition.x - 1, playerPosition.y - 1)};

    // tileNorthWest->npc_ = std::make_shared<NPC>("NPC0");

    // auto tileNorthEast{
    //     worldArea->GetTile(playerPosition.x + 1, playerPosition.y - 1)};

    // tileNorthEast->npc_ = std::make_shared<NPC>("NPC1");
}

void
WorldGenerator::GenerateWorldAroundPlayer()
{
    // auto worldArea{_<World>().currentWorldArea_};
    // auto size{worldArea->GetSize()};

    // POINT playerPosition{static_cast<int>(_<PLAYER>().position_.x),
    //                      static_cast<int>(_<PLAYER>().position_.y)};

    // for (auto y = playerPosition.y - 4; y <= playerPosition.y + 4; y++)
    // {
    //     for (auto x = playerPosition.x - 4; x <= playerPosition.x + 4; x++)
    //     {
    //         auto tile{worldArea->GetTile(x, y)};

    //         if (!tile)
    //         {
    //             continue;
    //         }

    //         tile->tileObjects_->CLEAR();

    //         tile->ground_ = HASH("GroundGrass");

    //         tile->elevation_ = 1;
    //     }
    // }
}