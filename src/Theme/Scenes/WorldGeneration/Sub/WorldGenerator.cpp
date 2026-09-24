/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "WorldGenerator.hpp"
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
    }

    void WorldGenerator::ClearWithGrass()
    {
        auto world_area{_<World>().currentWorldArea_};
        auto size{world_area->GetSize()};

        for (auto y = 0; y < size.height; y++)
        {
            for (auto x = 0; x < size.width; x++)
            {
                auto tile{world_area->GetTile(x, y)};

                tile->ground_ = Hash("ground_grass");
            }
        }
    }

    void WorldGenerator::GenerateDirt()
    {
        auto world_area{_<World>().currentWorldArea_};
        auto size{world_area->GetSize()};

        auto num_dirt_patches{15 + rand() % 8};

        for (auto i = 0; i < num_dirt_patches; i++)
        {
            auto x_center{rand() % size.width};
            auto y_center{rand() % size.height};
            auto radius{3 + rand() % 14};

            for (auto y = y_center - radius; y <= y_center + radius; y++)
            {
                for (auto x = x_center - radius; x <= x_center + radius; x++)
                {
                    if (!world_area->IsValidCoordinate(x, y))
                    {
                        continue;
                    }

                    auto dx{x - x_center};
                    auto dy{y - y_center};

                    if (dx * dx + dy * dy <= radius * radius)
                    {
                        auto tile{world_area->GetTile(x, y)};

                        tile->ground_ = Hash("ground_dirt");
                    }
                }
            }
        }
    }

    void WorldGenerator::GenerateWater()
    {
        auto world_area{_<World>().currentWorldArea_};
        auto size{world_area->GetSize()};

        auto num_lakes{40 + rand() % 20};

        for (auto i = 0; i < num_lakes; i++)
        {
            auto x_center{rand() % size.width};
            auto y_center{rand() % size.height};
            auto radius{3 + rand() % 6};

            for (auto y = y_center - radius; y <= y_center + radius; y++)
            {
                for (auto x = x_center - radius; x <= x_center + radius; x++)
                {
                    if (!world_area->IsValidCoordinate(x, y))
                    {
                        continue;
                    }

                    auto dx{x - x_center};
                    auto dy{y - y_center};

                    if (dx * dx + dy * dy <= radius * radius)
                    {
                        auto tile{world_area->GetTile(x, y)};
                        tile->ground_ = Hash("ground_water");
                    }
                }
            }
        }
    }

    void WorldGenerator::GenerateElevation()
    {
        auto world_area{_<World>().currentWorldArea_};
        auto size{world_area->GetSize()};

        for (auto y = 0; y < size.height; y++)
        {
            for (auto x = 0; x < size.width; x++)
            {
                auto tile{world_area->GetTile(x, y)};

                if (tile->ground_ != Hash("ground_water"))
                {
                    tile->elevation_ = 1;
                }
            }
        }

        auto num_hills{20 + rand() % 10};

        for (auto i = 0; i < num_hills; i++)
        {
            auto x_center{rand() % size.width};
            auto y_center{rand() % size.height};
            auto radius{3 + rand() % 9};

            for (auto r = radius; r >= 0; r--)
            {
                for (auto y = y_center - r; y <= y_center + r; y++)
                {
                    for (auto x = x_center - r; x <= x_center + r; x++)
                    {
                        if (!world_area->IsValidCoordinate(x, y))
                        {
                            continue;
                        }

                        auto dx{x - x_center};
                        auto dy{y - y_center};

                        if (dx * dx + dy * dy <= r * r)
                        {
                            auto tile{world_area->GetTile(x, y)};

                            if (tile->ground_ == Hash("ground_water"))
                            {
                                continue;
                            }

                            tile->elevation_++;
                        }
                    }
                }
            }
        }
    }

    void WorldGenerator::GenerateRock()
    {
        auto world_area{_<World>().currentWorldArea_};
        auto size{world_area->GetSize()};

        auto num_rock_patches{60 + rand() % 5};

        for (auto i = 0; i < num_rock_patches; i++)
        {
            auto x_center{rand() % size.width};
            auto y_center{rand() % size.height};
            auto radius{3 + rand() % 9};

            for (auto y = y_center - radius; y <= y_center + radius; y++)
            {
                for (auto x = x_center - radius; x <= x_center + radius; x++)
                {
                    if (!world_area->IsValidCoordinate(x, y))
                    {
                        continue;
                    }

                    auto dx{x - x_center};
                    auto dy{y - y_center};

                    if (dx * dx + dy * dy <= radius * radius)
                    {
                        auto tile{world_area->GetTile(x, y)};

                        if (tile->elevation_ >= 2)
                        {
                            tile->ground_ = Hash("ground_rock");
                        }
                    }
                }
            }
        }
    }

    void WorldGenerator::GenerateLargeObjects()
    {
        auto world_area{_<World>().currentWorldArea_};
        auto size{world_area->GetSize()};

        auto num_tree_2_groups{100 + rand() % 10};

        for (auto i = 0; i < num_tree_2_groups; i++)
        {
            auto x{rand() % size.width};
            auto y{rand() % size.height};

            auto num_tree_2s{60 + rand() % 10};

            for (auto j = 0; j < num_tree_2s; j++)
            {
                x += rand() % 3 - rand() % 3;
                y += rand() % 3 - rand() % 3;

                if (!world_area->IsValidCoordinate(x, y))
                {
                    continue;
                }

                auto tile{world_area->GetTile(x, y)};

                if (tile->ground_ == Hash("ground_water") ||
                    tile->ground_ == Hash("ground_rock"))
                {
                    continue;
                }

                tile->tileObjects_->Clear();

                tile->tileObjects_->AddObject("object_tree_2");
            }
        }

        auto num_tree_1_groups{100 + rand() % 10};

        for (auto i = 0; i < num_tree_1_groups; i++)
        {
            auto x{rand() % size.width};
            auto y{rand() % size.height};

            auto num_tree_1s{60 + rand() % 10};

            for (auto j = 0; j < num_tree_1s; j++)
            {
                x += rand() % 3 - rand() % 3;
                y += rand() % 3 - rand() % 3;

                if (!world_area->IsValidCoordinate(x, y))
                {
                    continue;
                }

                auto tile{world_area->GetTile(x, y)};

                if (tile->ground_ == Hash("ground_water") ||
                    tile->ground_ == Hash("ground_rock"))
                {
                    continue;
                }

                tile->tileObjects_->Clear();

                tile->tileObjects_->AddObject("object_tree_1");
            }
        }

        auto num_bush_1s{300 + rand() % 50};

        for (auto i = 0; i < num_bush_1s; i++)
        {
            auto x{rand() % size.width};
            auto y{rand() % size.height};

            auto tile{world_area->GetTile(x, y)};

            if (tile->ground_ == Hash("ground_water") ||
                tile->ground_ == Hash("ground_dirt") ||
                tile->ground_ == Hash("ground_rock"))
            {
                continue;
            }

            tile->tileObjects_->AddObject("object_bush_1");
        }

        auto num_stone_boulders{100 + rand() % 50};

        for (auto i = 0; i < num_stone_boulders; i++)
        {
            auto x{rand() % size.width};
            auto y{rand() % size.height};

            auto tile{world_area->GetTile(x, y)};

            if (tile->ground_ == Hash("ground_grass") ||
                tile->ground_ == Hash("ground_dirt"))
            {
                continue;
            }

            tile->tileObjects_->AddObject("object_stone_boulder");
        }
    }

    void WorldGenerator::GenerateSmallObjects()
    {
        auto world_area{_<World>().currentWorldArea_};
        auto size{world_area->GetSize()};

        auto num_stones{500 + rand() % 50};

        for (auto i = 0; i < num_stones; i++)
        {
            auto x{rand() % size.width};
            auto y{rand() % size.height};

            auto tile{world_area->GetTile(x, y)};

            if (tile->ground_ == Hash("ground_water"))
            {
                continue;
            }

            tile->tileObjects_->AddObject("object_stone");
        }

        auto num_branches{500 + rand() % 50};

        for (auto i = 0; i < num_branches; i++)
        {
            auto x{rand() % size.width};
            auto y{rand() % size.height};

            auto tile{world_area->GetTile(x, y)};

            if (tile->ground_ == Hash("ground_water") ||
                tile->ground_ == Hash("ground_rock"))
            {
                continue;
            }

            tile->tileObjects_->AddObject("object_branch");
        }

        auto num_pink_flowers{500 + rand() % 50};

        for (auto i = 0; i < num_pink_flowers; i++)
        {
            auto x{rand() % size.width};
            auto y{rand() % size.height};

            auto tile{world_area->GetTile(x, y)};

            if (tile->ground_ == Hash("ground_water") ||
                tile->ground_ == Hash("ground_rock") ||
                tile->ground_ == Hash("ground_dirt"))
            {
                continue;
            }

            tile->tileObjects_->AddObject("object_pink_flower");
        }

        auto num_leaves{500 + rand() % 50};

        for (auto i = 0; i < num_leaves; i++)
        {
            auto x{rand() % size.width};
            auto y{rand() % size.height};

            auto tile{world_area->GetTile(x, y)};

            if (tile->ground_ == Hash("ground_water") ||
                tile->ground_ == Hash("ground_rock"))
            {
                continue;
            }

            tile->tileObjects_->AddObject("object_leaf");
        }
    }
}