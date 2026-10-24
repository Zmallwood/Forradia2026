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
    std::shared_ptr<WORLD8AREA>
    CITY8GENERATOR::GENERATE8CITY() {
        auto worldArea{std::make_shared<WORLD8AREA>()};

        CLEAR8WITH8GRASS(worldArea);
        SET8BASE8ELEVATION(worldArea);
        GENERATE8WATER(worldArea);
        GENERATE8DIRT(worldArea);
        GENERATE8HILLS(worldArea);
        GENERATE8MOUNTAINS(worldArea);
        GENERATE8FORESTS(worldArea);
        GENERATE8LARGE8OBJECTS(worldArea);
        GENERATE8ROADS(worldArea);
        GENERATE8SMALL8OBJECTS(worldArea);
        GENERATE8CREATURES(worldArea);

        return worldArea;
    }

    void
    CITY8GENERATOR::CLEAR8WITH8GRASS(std::shared_ptr<WORLD8AREA> worldArea) {
        auto size{worldArea->GET8SIZE()};

        for (auto y = 0; y < size.height; y++) {
            for (auto x = 0; x < size.width; x++) {
                auto tile{worldArea->GET8TILE(x, y)};

                tile->ground_ = HASH("GroundGrass");
            }
        }
    }

    void
    CITY8GENERATOR::SET8BASE8ELEVATION(std::shared_ptr<WORLD8AREA> worldArea) {
        auto size{worldArea->GET8SIZE()};

        for (auto y = 0; y < size.height; y++) {
            for (auto x = 0; x < size.width; x++) {
                auto tile{worldArea->GET8TILE(x, y)};
                tile->elevation_ = 1;
            }
        }
    }

    void
    CITY8GENERATOR::GENERATE8ROADS(std::shared_ptr<WORLD8AREA> worldArea) {
        auto size{worldArea->GET8SIZE()};

        auto centerX{size.width / 2};
        auto centerY{size.height / 2};

        auto x{centerX};

        for (auto y = 0; y < size.height; y++) {
            auto tile{worldArea->GET8TILE(x, y)};

            tile->roadOrientation_ = ROAD8ORIENTATION::Vertical;

            tile->tileObjects_->CLEAR();

            if (rand() % 8 == 0) {
                x++;

                tile->roadOrientation_ = ROAD8ORIENTATION::CornerNorthEast;

                auto tile{worldArea->GET8TILE(x, y)};

                tile->roadOrientation_ = ROAD8ORIENTATION::CornerSouthWest;

                tile->tileObjects_->CLEAR();
            } else if (rand() % 8 == 0) {
                x--;

                tile->roadOrientation_ = ROAD8ORIENTATION::CornerNorthWest;

                auto tile{worldArea->GET8TILE(x, y)};

                tile->roadOrientation_ = ROAD8ORIENTATION::CornerSouthEast;

                tile->tileObjects_->CLEAR();
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

                        tile2->tileObjects_->CLEAR();

                        tile2->elevation_ = tile->elevation_;
                    }
                }

                roadNetworkCenter_ = {x, y};
            } else if (tile->roadOrientation_ != ROAD8ORIENTATION::Fill) {
                tile->roadOrientation_ = ROAD8ORIENTATION::Horizontal;

                tile->tileObjects_->CLEAR();
            }

            if (tile->roadOrientation_ != ROAD8ORIENTATION::CrossIntersection &&
                tile->roadOrientation_ != ROAD8ORIENTATION::Fill) {
                if (rand() % 8 == 0) {
                    y++;

                    tile->roadOrientation_ = ROAD8ORIENTATION::CornerSouthWest;

                    tile->tileObjects_->CLEAR();

                    auto tile{worldArea->GET8TILE(x, y)};

                    tile->roadOrientation_ = ROAD8ORIENTATION::CornerNorthEast;

                    tile->tileObjects_->CLEAR();
                } else if (rand() % 8 == 0) {
                    y--;

                    tile->roadOrientation_ = ROAD8ORIENTATION::CornerNorthWest;

                    tile->tileObjects_->CLEAR();

                    auto tile{worldArea->GET8TILE(x, y)};

                    tile->roadOrientation_ = ROAD8ORIENTATION::CornerSouthEast;

                    tile->tileObjects_->CLEAR();
                }
            }
        }
    }

    void
    CITY8GENERATOR::GENERATE8LARGE8OBJECTS(
        std::shared_ptr<WORLD8AREA> worldArea) {
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
    CITY8GENERATOR::GENERATE8SMALL8OBJECTS(
        std::shared_ptr<WORLD8AREA> worldArea) {
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
    CITY8GENERATOR::GENERATE8DIRT(std::shared_ptr<WORLD8AREA> worldArea) {
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

        TRAVERSE81(worldArea, fnMakeDirt);
        TRAVERSE82(worldArea, fnMakeDirt);
        TRAVERSE83(worldArea, fnMakeDirt);
        TRAVERSE84(worldArea, fnMakeDirt);
    }

    void
    CITY8GENERATOR::TRAVERSE81(std::shared_ptr<WORLD8AREA> worldArea,
                               std::function<void(int, int)> callback) {
        auto size{worldArea->GET8SIZE()};

        for (auto y = 1; y < size.height - 1; y++)
            for (auto x = 1; x < size.width - 1; x++)
                callback(x, y);
    }

    void
    CITY8GENERATOR::TRAVERSE82(std::shared_ptr<WORLD8AREA> worldArea,
                               std::function<void(int, int)> callback) {
        auto size{worldArea->GET8SIZE()};

        for (auto x = 1; x < size.width - 1; x++)
            for (auto y = 1; y < size.height - 1; y++)
                callback(x, y);
    }

    void
    CITY8GENERATOR::TRAVERSE83(std::shared_ptr<WORLD8AREA> worldArea,
                               std::function<void(int, int)> callback) {
        auto size{worldArea->GET8SIZE()};

        for (auto y = size.height - 2; y > 0; y--)
            for (auto x = 1; x < size.width - 1; x++)
                callback(x, y);
    }

    void
    CITY8GENERATOR::TRAVERSE84(std::shared_ptr<WORLD8AREA> worldArea,
                               std::function<void(int, int)> callback) {
        auto size{worldArea->GET8SIZE()};

        for (auto x = size.width - 2; x > 0; x--)
            for (auto y = 1; y < size.height - 1; y++)
                callback(x, y);
    }

    void
    CITY8GENERATOR::GENERATE8HILLS(std::shared_ptr<WORLD8AREA> worldArea) {
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
    CITY8GENERATOR::GENERATE8CREATURES(std::shared_ptr<WORLD8AREA> worldArea) {
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

    void
    CITY8GENERATOR::GENERATE8WATER(std::shared_ptr<WORLD8AREA> worldArea) {
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
                    auto makeWater{rand() % 1000 < 3};

                    if (makeWater) {
                        tile->ground_ = HASH("GroundWater");

                        tileW->ground_ = HASH("GroundWater");

                        tile->elevation_ = 0;
                        tileW->elevation_ = 0;
                    }
                }
            }
        }

        auto fnMakeWater = std::function<void(int, int)>([&](int x, int y) {
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

            auto numWaterTiles{0};

            if (groundNW == HASH("GroundWater"))
                numWaterTiles++;
            if (groundN == HASH("GroundWater"))
                numWaterTiles++;
            if (groundNE == HASH("GroundWater"))
                numWaterTiles++;
            if (groundW == HASH("GroundWater"))
                numWaterTiles++;
            if (groundE == HASH("GroundWater"))
                numWaterTiles++;
            if (groundSW == HASH("GroundWater"))
                numWaterTiles++;
            if (groundS == HASH("GroundWater"))
                numWaterTiles++;
            if (groundSE == HASH("GroundWater"))
                numWaterTiles++;

            if (numWaterTiles == 2) {
                auto makeWater{rand() % 1000 < 500};

                if (makeWater) {
                    tile->ground_ = HASH("GroundWater");

                    tile->elevation_ = 0;
                }
            } else if (numWaterTiles > 2) {
                auto makeWater{rand() % 1000 < 600};

                if (makeWater) {
                    tile->ground_ = HASH("GroundWater");

                    tile->elevation_ = 0;
                }
            }
        });

        TRAVERSE81(worldArea, fnMakeWater);
        TRAVERSE82(worldArea, fnMakeWater);
        TRAVERSE83(worldArea, fnMakeWater);
        TRAVERSE84(worldArea, fnMakeWater);
    }

    void
    CITY8GENERATOR::GENERATE8MOUNTAINS(std::shared_ptr<WORLD8AREA> worldArea) {
        auto size{worldArea->GET8SIZE()};

        auto numMountains = 40 + rand() % 10;

        for (auto i = 0; i < numMountains; i++) {
            auto xCenter{rand() % size.width};
            auto yCenter{rand() % size.height};
            auto radius{3 + rand() % 8};

            for (auto r = radius; r >= 0; r -= 2 + rand() % 6) {
                auto elevationChange = 3 + rand() % 3;

                for (auto y = yCenter - r; y <= yCenter + r; y++) {
                    for (auto x = xCenter - r; x <= xCenter + r; x++) {
                        if (!worldArea->IS8VALID8COORDINATE(x, y))
                            continue;

                        auto dx = x - xCenter;
                        auto dy = y - yCenter;

                        if (dx * dx + dy * dy <= r * r) {
                            auto tile{worldArea->GET8TILE(x, y)};

                            if (tile->ground_ == HASH("GroundWater"))
                                continue;

                            tile->elevation_ += elevationChange;

                            tile->ground_ = HASH("GroundRock");

                            if (rand() % 5 == 0) {
                                tile->tileObjects_->CLEAR();

                                tile->tileObjects_->ADD8OBJECT(
                                    "ObjectStoneBoulder");
                            }
                        }
                    }
                }
            }
        }
    }

    void
    CITY8GENERATOR::GENERATE8FORESTS(std::shared_ptr<WORLD8AREA> worldArea) {
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

                if (groundNW != HASH("GroundWater") &&
                    groundN != HASH("GroundWater") &&
                    groundNE != HASH("GroundWater") &&
                    groundW != HASH("GroundWater") &&
                    groundNW != HASH("GroundRock") &&
                    groundN != HASH("GroundRock") &&
                    groundNE != HASH("GroundRock") &&
                    groundW != HASH("GroundRock")) {
                    auto makeTree{rand() % 1000 < 5};

                    if (makeTree) {
                        if (rand() % 2) {
                            tile->tileObjects_->CLEAR();

                            tile->tileObjects_->ADD8OBJECT("ObjectTree1");

                            tileW->tileObjects_->CLEAR();

                            tileW->tileObjects_->ADD8OBJECT("ObjectTree1");
                        } else {
                            tile->tileObjects_->CLEAR();

                            tile->tileObjects_->ADD8OBJECT("ObjectTree2");

                            tileW->tileObjects_->CLEAR();

                            tileW->tileObjects_->ADD8OBJECT("ObjectTree2");
                        }
                    }
                }
            }
        }

        auto fnMakeTrees = std::function<void(int, int)>([&](int x, int y) {
            auto tile{worldArea->GET8TILE(x, y)};

            auto tileNW{worldArea->GET8TILE(x - 1, y - 1)};
            auto tileN{worldArea->GET8TILE(x, y - 1)};
            auto tileNE{worldArea->GET8TILE(x + 1, y - 1)};
            auto tileW{worldArea->GET8TILE(x - 1, y)};
            auto tileE{worldArea->GET8TILE(x + 1, y)};
            auto tileSW{worldArea->GET8TILE(x - 1, y + 1)};
            auto tileS{worldArea->GET8TILE(x, y + 1)};
            auto tileSE{worldArea->GET8TILE(x + 1, y + 1)};

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
                tile->ground_ != HASH("GroundRock")) {
                if (hasTreeNW)
                    numTreeTiles++;
                if (hasTreeN)
                    numTreeTiles++;
                if (hasTreeNE)
                    numTreeTiles++;
                if (hasTreeW)
                    numTreeTiles++;
                if (hasTreeE)
                    numTreeTiles++;
                if (hasTreeSW)
                    numTreeTiles++;
                if (hasTreeS)
                    numTreeTiles++;
                if (hasTreeSE)
                    numTreeTiles++;
            }

            if (numTreeTiles == 2) {
                auto makeTree{rand() % 1000 < 700};

                if (makeTree) {
                    if (rand() % 2 % 2) {
                        tile->tileObjects_->CLEAR();

                        tile->tileObjects_->ADD8OBJECT("ObjectTree1");
                    } else if (rand() % 2) {
                        tile->tileObjects_->CLEAR();

                        tile->tileObjects_->ADD8OBJECT("ObjectTree2");
                    }
                }
            } else if (numTreeTiles > 2) {
                auto makeTree{rand() % 1000 < 900};

                if (makeTree) {
                    if (rand() % 2) {
                        tile->tileObjects_->CLEAR();
                        tile->tileObjects_->ADD8OBJECT("ObjectTree1");
                    } else if (rand() % 2) {
                        tile->tileObjects_->CLEAR();
                        tile->tileObjects_->ADD8OBJECT("ObjectTree2");
                    }
                }
            }
        });

        TRAVERSE81(worldArea, fnMakeTrees);
        TRAVERSE82(worldArea, fnMakeTrees);
        TRAVERSE83(worldArea, fnMakeTrees);
        TRAVERSE84(worldArea, fnMakeTrees);
    }
}