//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "CITY8GENERATOR.HPP"
#include "CORE/WORLD8STRUCTURE/CREATURE.HPP"
#include "CORE/WORLD8STRUCTURE/NPC.HPP"
#include "CORE/WORLD8STRUCTURE/TILE.HPP"
#include "CORE/WORLD8STRUCTURE/TILE8OBJECTS.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD8AREA.HPP"

namespace FORRADIA8GAME {
    void
    CITY8GENERATOR::GENERATE8CITY() {
        CLEAR8WITH8GRASS();
        SET8BASE8ELEVATION();
        GENERATE8DIRT();
        GENERATE8HILLS();
        GENERATE8ROADS();
        GENERATE8LARGE8OBJECTS();
        GENERATE8SMALL8OBJECTS();
        GENERATE8CREATURES();
    }

    void
    CITY8GENERATOR::CLEAR8WITH8GRASS() {
        auto worldArea{_<WORLD>().currentWorldArea_};
        auto size{worldArea->GET8SIZE()};

        for (auto y = 0; y < size.height; y++) {
            for (auto x = 0; x < size.width; x++) {
                auto tile{worldArea->GET8TILE(x, y)};

                tile->ground_ = HASH("GroundGrass");
            }
        }
    }

    void
    CITY8GENERATOR::SET8BASE8ELEVATION() {
        auto worldArea{_<WORLD>().currentWorldArea_};
        auto size{worldArea->GET8SIZE()};

        for (auto y = 0; y < size.height; y++) {
            for (auto x = 0; x < size.width; x++) {
                auto tile{worldArea->GET8TILE(x, y)};
                tile->elevation_ = 1;
            }
        }
    }

    void
    CITY8GENERATOR::GENERATE8ROADS() {
        auto worldArea{_<WORLD>().currentWorldArea_};
        auto size{worldArea->GET8SIZE()};

        auto centerX{size.width / 2};
        auto centerY{size.height / 2};

        auto x{centerX};

        for (auto y = 0; y < size.height; y++) {
            auto tile{worldArea->GET8TILE(x, y)};

            tile->roadOrientation_ = ROAD8ORIENTATION::Vertical;

            if (rand() % 8 == 0) {
                x++;

                tile->roadOrientation_ = ROAD8ORIENTATION::CornerNorthEast;

                auto tile{worldArea->GET8TILE(x, y)};

                tile->roadOrientation_ = ROAD8ORIENTATION::CornerSouthWest;
            } else if (rand() % 8 == 0) {
                x--;

                tile->roadOrientation_ = ROAD8ORIENTATION::CornerNorthWest;

                auto tile{worldArea->GET8TILE(x, y)};

                tile->roadOrientation_ = ROAD8ORIENTATION::CornerSouthEast;
            }
        }

        auto y{centerY};

        for (auto x = 0; x < size.width; x++) {
            auto tile{worldArea->GET8TILE(x, y)};

            if (tile->roadOrientation_ != ROAD8ORIENTATION::Horizontal &&
                tile->roadOrientation_ != ROAD8ORIENTATION::None &&
                tile->roadOrientation_ != ROAD8ORIENTATION::Fill) {
                for (auto y2 = y - 1; y2 <= y + 1; y2++) {
                    for (auto x2 = x - 1; x2 <= x + 1; x2++) {
                        auto tile2{worldArea->GET8TILE(x2, y2)};

                        if (!tile2)
                            continue;

                        tile2->roadOrientation_ = ROAD8ORIENTATION::Fill;

                        tile2->elevation_ = tile->elevation_;
                    }
                }

                roadNetworkCenter_ = {x, y};
            } else if (tile->roadOrientation_ != ROAD8ORIENTATION::Fill) {
                tile->roadOrientation_ = ROAD8ORIENTATION::Horizontal;
            }

            if (tile->roadOrientation_ != ROAD8ORIENTATION::CrossIntersection &&
                tile->roadOrientation_ != ROAD8ORIENTATION::Fill) {
                if (rand() % 8 == 0) {
                    y++;

                    tile->roadOrientation_ = ROAD8ORIENTATION::CornerSouthWest;

                    auto tile{worldArea->GET8TILE(x, y)};

                    tile->roadOrientation_ = ROAD8ORIENTATION::CornerNorthEast;
                } else if (rand() % 8 == 0) {
                    y--;

                    tile->roadOrientation_ = ROAD8ORIENTATION::CornerNorthWest;

                    auto tile{worldArea->GET8TILE(x, y)};

                    tile->roadOrientation_ = ROAD8ORIENTATION::CornerSouthEast;
                }
            }
        }
    }

    void
    CITY8GENERATOR::GENERATE8LARGE8OBJECTS() {
        auto worldArea{_<WORLD>().currentWorldArea_};
        auto size{worldArea->GET8SIZE()};

        auto numBush1s{100 + rand() % 30};

        for (auto i = 0; i < numBush1s; i++) {
            auto x{rand() % size.width};
            auto y{rand() % size.height};

            auto tile{worldArea->GET8TILE(x, y)};

            if (tile->ground_ == HASH("GroundWater") ||
                tile->ground_ == HASH("GroundDirt") ||
                tile->ground_ == HASH("GroundRock"))
                continue;

            if (tile->roadOrientation_ != ROAD8ORIENTATION::None)
                continue;

            tile->tileObjects_->ADD8OBJECT("ObjectBush1");
        }

        auto numBush2s{100 + rand() % 30};

        for (auto i = 0; i < numBush2s; i++) {
            auto x{rand() % size.width};
            auto y{rand() % size.height};

            auto tile{worldArea->GET8TILE(x, y)};

            if (tile->ground_ == HASH("GroundWater") ||
                tile->ground_ == HASH("GroundDirt") ||
                tile->ground_ == HASH("GroundRock"))
                continue;

            if (tile->roadOrientation_ != ROAD8ORIENTATION::None)
                continue;

            tile->tileObjects_->ADD8OBJECT("ObjectBush2");
        }

        auto numStoneBoulders{100 + rand() % 50};

        for (auto i = 0; i < numStoneBoulders; i++) {
            auto x{rand() % size.width};
            auto y{rand() % size.height};

            auto tile{worldArea->GET8TILE(x, y)};

            if (tile->ground_ == HASH("GroundGrass") ||
                tile->ground_ == HASH("GroundDirt"))
                continue;

            if (tile->roadOrientation_ != ROAD8ORIENTATION::None)
                continue;

            tile->tileObjects_->ADD8OBJECT("ObjectStoneBoulder");
        }

        auto numTree1s{100 + rand() % 50};

        for (auto i = 0; i < numTree1s; i++) {
            auto x{rand() % size.width};
            auto y{rand() % size.height};

            auto tile{worldArea->GET8TILE(x, y)};

            if (tile->roadOrientation_ != ROAD8ORIENTATION::None)
                continue;

            if (tile->ground_ == HASH("GroundGrass") ||
                tile->ground_ == HASH("GroundDirt"))
                tile->tileObjects_->ADD8OBJECT("ObjectTree1");
        }

        auto numTree2s{100 + rand() % 50};

        for (auto i = 0; i < numTree2s; i++) {
            auto x{rand() % size.width};
            auto y{rand() % size.height};

            auto tile{worldArea->GET8TILE(x, y)};

            if (tile->roadOrientation_ != ROAD8ORIENTATION::None)
                continue;

            if (tile->ground_ == HASH("GroundGrass") ||
                tile->ground_ == HASH("GroundDirt"))
                tile->tileObjects_->ADD8OBJECT("ObjectTree2");
        }
    }
    void
    CITY8GENERATOR::GENERATE8SMALL8OBJECTS() {
        auto worldArea{_<WORLD>().currentWorldArea_};
        auto size{worldArea->GET8SIZE()};

        auto numStones{500 + rand() % 50};

        for (auto i = 0; i < numStones; i++) {
            auto x{rand() % size.width};
            auto y{rand() % size.height};

            auto tile{worldArea->GET8TILE(x, y)};

            if (tile->ground_ == HASH("GroundWater"))
                continue;

            tile->tileObjects_->ADD8OBJECT("ObjectStone");
        }

        auto numBranches{500 + rand() % 50};

        for (auto i = 0; i < numBranches; i++) {
            auto x{rand() % size.width};
            auto y{rand() % size.height};

            auto tile{worldArea->GET8TILE(x, y)};

            if (tile->ground_ == HASH("GroundWater") ||
                tile->ground_ == HASH("GroundRock"))
                continue;

            tile->tileObjects_->ADD8OBJECT("ObjectBranch");
        }

        auto numPinkFlowers{500 + rand() % 50};

        for (auto i = 0; i < numPinkFlowers; i++) {
            auto x{rand() % size.width};
            auto y{rand() % size.height};

            auto tile{worldArea->GET8TILE(x, y)};

            if (tile->ground_ == HASH("GroundWater") ||
                tile->ground_ == HASH("GroundRock") ||
                tile->ground_ == HASH("GroundDirt"))
                continue;

            tile->tileObjects_->ADD8OBJECT("ObjectPinkFlower");
        }

        auto numLeaves{500 + rand() % 50};

        for (auto i = 0; i < numLeaves; i++) {
            auto x{rand() % size.width};
            auto y{rand() % size.height};

            auto tile{worldArea->GET8TILE(x, y)};

            if (tile->ground_ == HASH("GroundWater") ||
                tile->ground_ == HASH("GroundRock"))
                continue;

            tile->tileObjects_->ADD8OBJECT("ObjectLeaf");
        }
    }
    void
    CITY8GENERATOR::GENERATE8DIRT() {
        auto worldArea{_<WORLD>().currentWorldArea_};
        auto size{worldArea->GET8SIZE()};

        for (auto y = 1; y < size.height - 1; y++) {
            for (auto x = 1; x < size.width - 1; x++) {
                auto tile{worldArea->GET8TILE(x, y)};

                auto tileNW{worldArea->GET8TILE(x - 1, y - 1)};
                auto tileN{worldArea->GET8TILE(x, y - 1)};
                auto tileNE{worldArea->GET8TILE(x + 1, y - 1)};
                auto tileW{worldArea->GET8TILE(x - 1, y)};

                auto groundNW{tileNW->ground_};
                auto groundN{tileN->ground_};
                auto groundNE{tileNE->ground_};
                auto groundW{tileW->ground_};

                if (groundNW == HASH("GroundGrass") &&
                    groundN == HASH("GroundGrass") &&
                    groundNE == HASH("GroundGrass") &&
                    groundW == HASH("GroundGrass")) {
                    auto makeDirt{rand() % 1000 < 3};

                    if (makeDirt) {
                        tile->ground_ = HASH("GroundDirt");

                        tileW->ground_ = HASH("GroundDirt");

                        tile->elevation_ = 1;
                        tileW->elevation_ = 1;
                    }
                }
            }
        }

        auto fnMakeDirt = std::function<void(int, int)>([&](int x, int y) {
            auto tile{worldArea->GET8TILE(x, y)};

            auto tileNW{worldArea->GET8TILE(x - 1, y - 1)};
            auto tileN{worldArea->GET8TILE(x, y - 1)};
            auto tileNE{worldArea->GET8TILE(x + 1, y - 1)};
            auto tileW{worldArea->GET8TILE(x - 1, y)};
            auto tileE{worldArea->GET8TILE(x + 1, y)};
            auto tileSW{worldArea->GET8TILE(x - 1, y + 1)};
            auto tileS{worldArea->GET8TILE(x, y + 1)};
            auto tileSE{worldArea->GET8TILE(x + 1, y + 1)};

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
                numDirtTiles++;
            if (groundN == HASH("GroundDirt"))
                numDirtTiles++;
            if (groundNE == HASH("GroundDirt"))
                numDirtTiles++;
            if (groundW == HASH("GroundDirt"))
                numDirtTiles++;
            if (groundE == HASH("GroundDirt"))
                numDirtTiles++;
            if (groundSW == HASH("GroundDirt"))
                numDirtTiles++;
            if (groundS == HASH("GroundDirt"))
                numDirtTiles++;
            if (groundSE == HASH("GroundDirt"))
                numDirtTiles++;

            if (numDirtTiles == 2) {
                auto makeDirt{rand() % 1000 < 500};

                if (makeDirt) {
                    tile->ground_ = HASH("GroundDirt");

                    tile->elevation_ = 1;
                }
            } else if (numDirtTiles > 2) {
                auto makeDirt{rand() % 1000 < 600};

                if (makeDirt) {
                    tile->ground_ = HASH("GroundDirt");

                    tile->elevation_ = 1;
                }
            }
        });

        TRAVERSE81(fnMakeDirt);
        TRAVERSE82(fnMakeDirt);
        TRAVERSE83(fnMakeDirt);
        TRAVERSE84(fnMakeDirt);
    }

    void
    CITY8GENERATOR::TRAVERSE81(std::function<void(int, int)> callback) {
        auto worldArea{_<WORLD>().currentWorldArea_};
        auto size{worldArea->GET8SIZE()};

        for (auto y = 1; y < size.height - 1; y++)
            for (auto x = 1; x < size.width - 1; x++)
                callback(x, y);
    }

    void
    CITY8GENERATOR::TRAVERSE82(std::function<void(int, int)> callback) {
        auto worldArea{_<WORLD>().currentWorldArea_};
        auto size{worldArea->GET8SIZE()};

        for (auto x = 1; x < size.width - 1; x++)
            for (auto y = 1; y < size.height - 1; y++)
                callback(x, y);
    }

    void
    CITY8GENERATOR::TRAVERSE83(std::function<void(int, int)> callback) {
        auto worldArea{_<WORLD>().currentWorldArea_};
        auto size{worldArea->GET8SIZE()};

        for (auto y = size.height - 2; y > 0; y--)
            for (auto x = 1; x < size.width - 1; x++)
                callback(x, y);
    }

    void
    CITY8GENERATOR::TRAVERSE84(std::function<void(int, int)> callback) {
        auto worldArea{_<WORLD>().currentWorldArea_};
        auto size{worldArea->GET8SIZE()};

        for (auto x = size.width - 2; x > 0; x--)
            for (auto y = 1; y < size.height - 1; y++)
                callback(x, y);
    }

    void
    CITY8GENERATOR::GENERATE8HILLS() {
        auto worldArea{_<WORLD>().currentWorldArea_};
        auto size{worldArea->GET8SIZE()};

        auto numHills = 60 + rand() % 10;

        for (auto i = 0; i < numHills; i++) {
            auto xCenter{rand() % size.width};
            auto yCenter{rand() % size.height};
            auto radius{3 + rand() % 14};

            for (auto r = radius; r >= 0; r -= (1 + rand() % 2)) {
                for (auto y = yCenter - radius; y <= yCenter + radius; y++) {
                    for (auto x = xCenter - radius; x <= xCenter + radius;
                         x++) {
                        if (!worldArea->IS8VALID8COORDINATE(x, y))
                            continue;

                        auto dx = x - xCenter;
                        auto dy = y - yCenter;

                        if (dx * dx + dy * dy <= r * r) {
                            auto tile{worldArea->GET8TILE(x, y)};

                            if (tile->ground_ == HASH("GroundWater") &&
                                tile->ground_ != HASH("GroundRock"))
                                continue;

                            if (tile->elevation_ >= 5)
                                continue;

                            tile->elevation_++;
                        }
                    }
                }
            }
        }
    }
    void
    CITY8GENERATOR::GENERATE8CREATURES() {
        auto worldArea{_<WORLD>().currentWorldArea_};
        auto size{worldArea->GET8SIZE()};

        auto numDeers{80 + rand() % 10};

        for (auto i = 0; i < numDeers; i++) {
            auto x{rand() % size.width};
            auto y{rand() % size.height};

            auto tile{worldArea->GET8TILE(x, y)};

            if (tile->ground_ == HASH("GroundWater") ||
                tile->ground_ == HASH("GroundRock"))
                continue;

            auto newCreature{std::make_shared<CREATURE>("CreatureDeer")};

            worldArea->creaturesMirror_.insert({newCreature, {x, y}});

            tile->creature_ = newCreature;
        }

        auto numBoars{80 + rand() % 10};

        for (auto i = 0; i < numBoars; i++) {
            auto x{rand() % size.width};
            auto y{rand() % size.height};

            auto tile{worldArea->GET8TILE(x, y)};

            if (tile->ground_ == HASH("GroundWater") ||
                tile->ground_ == HASH("GroundRock"))
                continue;

            auto newCreature{std::make_shared<CREATURE>("CreatureBoar")};

            worldArea->creaturesMirror_.insert({newCreature, {x, y}});
        }

        auto numButterflies{80 + rand() % 10};

        for (auto i = 0; i < numButterflies; i++) {
            auto x{rand() % size.width};
            auto y{rand() % size.height};

            auto tile{worldArea->GET8TILE(x, y)};

            if (tile->ground_ == HASH("GroundWater") ||
                tile->ground_ == HASH("GroundRock"))
                continue;

            auto newCreature{std::make_shared<CREATURE>("CreatureButterfly")};

            worldArea->creaturesMirror_.insert({newCreature, {x, y}});
        }

        auto numRedBirds{80 + rand() % 10};

        for (auto i = 0; i < numRedBirds; i++) {
            auto x{rand() % size.width};
            auto y{rand() % size.height};

            auto tile{worldArea->GET8TILE(x, y)};

            if (tile->ground_ == HASH("GroundWater") ||
                tile->ground_ == HASH("GroundRock"))
                continue;

            auto newCreature{std::make_shared<CREATURE>("CreatureRedBird")};

            worldArea->creaturesMirror_.insert({newCreature, {x, y}});
        }

        auto numWhiteRabbits{80 + rand() % 10};

        for (auto i = 0; i < numWhiteRabbits; i++) {
            auto x{rand() % size.width};
            auto y{rand() % size.height};

            auto tile{worldArea->GET8TILE(x, y)};

            if (tile->ground_ == HASH("GroundWater") ||
                tile->ground_ == HASH("GroundRock"))
                continue;

            auto newCreature{std::make_shared<CREATURE>("CreatureWhiteRabbit")};

            worldArea->creaturesMirror_.insert({newCreature, {x, y}});
        }
    }
}