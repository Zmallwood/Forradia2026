/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "WorldGenerator.hpp"
#include "Core/WorldStructure/Creature.hpp"
#include "Core/WorldStructure/Tile.hpp"
#include "Core/WorldStructure/TileObjects.hpp"
#include "Core/WorldStructure/World.hpp"
#include "Core/WorldStructure/WorldArea.hpp"

namespace Forradia
{
    void WorldGenerator::GenerateNewWorld()
    {
        ClearWithGrass();

        GenerateDirt();

        GenerateWater();

        GenerateElevation();

        GenerateRock();

        GenerateLargeObjects();

        GenerateSmallObjects();

        GenerateCreatures();
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

    void WorldGenerator::GenerateDirt()
    {
        auto worldArea{_<World>().currentWorldArea_};
        auto size{worldArea->GetSize()};

        auto numDirtPatches{15 + rand() % 8};

        for (auto i = 0; i < numDirtPatches; i++)
        {
            auto xCenter{rand() % size.width};
            auto yCenter{rand() % size.height};
            auto radius{3 + rand() % 14};

            for (auto y = yCenter - radius; y <= yCenter + radius; y++)
            {
                for (auto x = xCenter - radius; x <= xCenter + radius; x++)
                {
                    if (!worldArea->IsValidCoordinate(x, y))
                    {
                        continue;
                    }

                    auto dx{x - xCenter};
                    auto dy{y - yCenter};

                    if (dx * dx + dy * dy <= radius * radius)
                    {
                        auto tile{worldArea->GetTile(x, y)};

                        tile->ground_ = Hash("GroundDirt");
                    }
                }
            }
        }
    }

    void WorldGenerator::GenerateWater()
    {
        auto worldArea{_<World>().currentWorldArea_};
        auto size{worldArea->GetSize()};

        auto numLakes{40 + rand() % 20};

        for (auto i = 0; i < numLakes; i++)
        {
            auto xCenter{rand() % size.width};
            auto yCenter{rand() % size.height};
            auto radius{3 + rand() % 6};

            for (auto y = yCenter - radius; y <= yCenter + radius; y++)
            {
                for (auto x = xCenter - radius; x <= xCenter + radius; x++)
                {
                    if (!worldArea->IsValidCoordinate(x, y))
                    {
                        continue;
                    }

                    auto dx{x - xCenter};
                    auto dy{y - yCenter};

                    if (dx * dx + dy * dy <= radius * radius)
                    {
                        auto tile{worldArea->GetTile(x, y)};

                        tile->ground_ = Hash("GroundWater");
                    }
                }
            }
        }
    }

    void WorldGenerator::GenerateElevation()
    {
        auto worldArea{_<World>().currentWorldArea_};
        auto size{worldArea->GetSize()};

        for (auto y = 0; y < size.height; y++)
        {
            for (auto x = 0; x < size.width; x++)
            {
                auto tile{worldArea->GetTile(x, y)};

                if (tile->ground_ != Hash("GroundWater"))
                {
                    tile->elevation_ = 1;
                }
            }
        }

        auto numHills{20 + rand() % 10};

        for (auto i = 0; i < numHills; i++)
        {
            auto xCenter{rand() % size.width};
            auto yCenter{rand() % size.height};
            auto radius{3 + rand() % 9};

            for (auto r = radius; r >= 0; r--)
            {
                for (auto y = yCenter - r; y <= yCenter + r; y++)
                {
                    for (auto x = xCenter - r; x <= xCenter + r; x++)
                    {
                        if (!worldArea->IsValidCoordinate(x, y))
                        {
                            continue;
                        }

                        auto dx{x - xCenter};
                        auto dy{y - yCenter};

                        if (dx * dx + dy * dy <= r * r)
                        {
                            auto tile{worldArea->GetTile(x, y)};

                            if (tile->ground_ == Hash("GroundWater"))
                            {
                                continue;
                            }

                            ++tile->elevation_;
                        }
                    }
                }
            }
        }
    }

    void WorldGenerator::GenerateRock()
    {
        auto worldArea{_<World>().currentWorldArea_};
        auto size{worldArea->GetSize()};

        auto numRockPatches{60 + rand() % 5};

        for (auto i = 0; i < numRockPatches; i++)
        {
            auto xCenter{rand() % size.width};
            auto yCenter{rand() % size.height};
            auto radius{3 + rand() % 9};

            for (auto y = yCenter - radius; y <= yCenter + radius; y++)
            {
                for (auto x = xCenter - radius; x <= xCenter + radius; x++)
                {
                    if (!worldArea->IsValidCoordinate(x, y))
                    {
                        continue;
                    }

                    auto dx{x - xCenter};
                    auto dy{y - yCenter};

                    if (dx * dx + dy * dy <= radius * radius)
                    {
                        auto tile{worldArea->GetTile(x, y)};

                        if (tile->elevation_ >= 2)
                        {
                            tile->ground_ = Hash("GroundRock");
                        }
                    }
                }
            }
        }
    }

    void WorldGenerator::GenerateLargeObjects()
    {
        auto worldArea{_<World>().currentWorldArea_};
        auto size{worldArea->GetSize()};

        auto numTree2Groups{100 + rand() % 10};

        for (auto i = 0; i < numTree2Groups; i++)
        {
            auto x{rand() % size.width};
            auto y{rand() % size.height};

            auto numTree2s{60 + rand() % 10};

            for (auto j = 0; j < numTree2s; j++)
            {
                x += rand() % 3 - rand() % 3;
                y += rand() % 3 - rand() % 3;

                if (!worldArea->IsValidCoordinate(x, y))
                {
                    continue;
                }

                auto tile{worldArea->GetTile(x, y)};

                if (tile->ground_ == Hash("GroundWater") ||
                    tile->ground_ == Hash("GroundRock"))
                {
                    continue;
                }

                tile->tileObjects_->Clear();

                tile->tileObjects_->AddObject("ObjectTree2");
            }
        }

        auto numTree1Groups{100 + rand() % 10};

        for (auto i = 0; i < numTree1Groups; i++)
        {
            auto x{rand() % size.width};
            auto y{rand() % size.height};

            auto numTree1s{60 + rand() % 10};

            for (auto j = 0; j < numTree1s; j++)
            {
                x += rand() % 3 - rand() % 3;
                y += rand() % 3 - rand() % 3;

                if (!worldArea->IsValidCoordinate(x, y))
                {
                    continue;
                }

                auto tile{worldArea->GetTile(x, y)};

                if (tile->ground_ == Hash("GroundWater") ||
                    tile->ground_ == Hash("GroundRock"))
                {
                    continue;
                }

                tile->tileObjects_->Clear();

                tile->tileObjects_->AddObject("ObjectTree1");
            }
        }

        auto numBush1s{300 + rand() % 50};

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

        auto numDeers{100 + rand() % 20};

        for (auto i = 0; i < numDeers; i++)
        {
            auto x{rand() % size.width};
            auto y{rand() % size.height};

            auto tile{worldArea->GetTile(x, y)};

            if (tile->ground_ == Hash("GroundWater"))
            {
                continue;
            }

            auto newCreature{std::make_shared<Creature>("CreatureDeer")};

            worldArea->creaturesMirror_.insert({newCreature, {x, y}});

            tile->creature_ = newCreature;
        }
    }
}