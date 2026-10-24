//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "ESSENCE8SYSTEM.HPP"
#include "CORE/CORE8GAME8OBJECTS/PLAYER.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD8AREA.HPP"
#include "CORE/WORLD8STRUCTURE/TILE.HPP"
#include "CORE/WORLD8STRUCTURE/TILE8OBJECTS.HPP"
#include "CORE/WORLD8STRUCTURE/OBJECT.HPP"
#include "CORE/CONFIGURATION/ESSENCE8INDEX.HPP"

namespace FORRADIA8GAME {
    ESSENCE8SYSTEM::ESSENCE8SYSTEM() {
        descriptions_.resize(kMaxDescriptions_);
    }

    void
    ESSENCE8SYSTEM::UPDATE() {
        auto now{NOW()};

        if (now < ticksLastUpdate_ + ticksPerUpdate_ &&
            descriptions_.at(currentDescriptionIndex_) != "")
            return;

        auto worldArea{_<WORLD>().currentWorldArea_};

        POINT playerPosition{static_cast<int>(_<PLAYER>().mPosition.x),
                             static_cast<int>(_<PLAYER>().mPosition.y)};

        auto r{kNoticingRadius_};

        std::vector<std::string> potentialGroundDescriptions;
        std::vector<std::string> potentialObjectDescriptions;

        for (auto y = playerPosition.y - r; y <= playerPosition.y + r; y++) {
            for (auto x = playerPosition.x - r; x <= playerPosition.x + r;
                 x++) {
                auto tile{worldArea->GET8TILE(x, y)};

                if (!tile)
                    continue;

                auto dx{x - playerPosition.x};
                auto dy{y - playerPosition.y};

                auto distance{static_cast<int>(std::sqrt(dx * dx + dy * dy))};

                auto angle{std::atan2(dy, dx)};

                std::string direction{"???"};

                if (angle >= -5.0 * M_PI / 8.0 && angle < -3.0 * M_PI / 8.0)
                    direction = "north";
                else if (angle >= -3.0 * M_PI / 8.0 && angle < -M_PI / 8.0)
                    direction = "north-east";
                else if (angle >= -M_PI / 8.0 && angle < M_PI / 8.0)
                    direction = "east";
                else if (angle >= M_PI / 8.0 && angle < 3.0 * M_PI / 8.0)
                    direction = "south-east";
                else if (angle >= 3.0 * M_PI / 8.0 && angle < 5.0 * M_PI / 8.0)
                    direction = "south";
                else if (angle >= 5.0 * M_PI / 8.0 && angle < 7.0 * M_PI / 8.0)
                    direction = "south-west";
                else if (angle >= 7.0 * M_PI / 8.0 || angle < -7.0 * M_PI / 8.0)
                    direction = "west";
                else if (angle >= -7.0 * M_PI / 8.0 &&
                         angle < -5.0 * M_PI / 8.0)
                    direction = "north-west";

                auto noticeGround{static_cast<bool>(rand() % 2)};
                auto noticeObject{!noticeGround};

                auto groundType{tile->ground_};
                auto descriptions{
                    _<ESSENCE8INDEX>().GET8ESSENCE8DESCRIPTIONS(groundType)};

                if (!descriptions.empty()) {
                    auto randomEssence{
                        descriptions.at(rand() % descriptions.size())};

                    auto description{randomEssence + " " +
                                     std::to_string(distance) + "m to the " +
                                     direction};

                    potentialGroundDescriptions.push_back(description);
                }
                auto tileObjects{tile->tileObjects_};

                auto objects{tileObjects->objects_};

                if (!objects.empty()) {
                    auto randomObjectEntry =
                        std::next(objects.begin(), rand() % objects.size());

                    auto object = randomObjectEntry->second;

                    auto objectType{object->type_};

                    auto descriptions{
                        _<ESSENCE8INDEX>().GET8ESSENCE8DESCRIPTIONS(
                            objectType)};

                    if (!descriptions.empty()) {
                        auto randomEssence{
                            descriptions.at(rand() % descriptions.size())};

                        auto description{randomEssence + " " +
                                         std::to_string(distance) +
                                         "m to the " + direction};

                        potentialObjectDescriptions.push_back(description);
                    }
                }
            }
        }

        auto noticeGround{static_cast<bool>(rand() % 2)};
        auto noticeObject{!noticeGround};

        if (noticeGround && !potentialGroundDescriptions.empty()) {
            std::string newDescription;

            auto numTries{10};
            auto i{0};

            do {
                newDescription = potentialGroundDescriptions.at(
                    rand() % potentialGroundDescriptions.size());
                i++;
            } while (newDescription ==
                         descriptions_[currentDescriptionIndex_] &&
                     i < numTries);

            descriptions_[currentDescriptionIndex_] = newDescription;
        } else if (noticeObject && !potentialObjectDescriptions.empty()) {
            std::string newDescription;

            auto numTries{10};
            auto i{0};

            do {
                newDescription = potentialObjectDescriptions.at(
                    rand() % potentialObjectDescriptions.size());
                i++;
            } while (newDescription ==
                         descriptions_[currentDescriptionIndex_] &&
                     i < numTries);

            descriptions_[currentDescriptionIndex_] = newDescription;
        }

        currentDescriptionIndex_++;

        if (currentDescriptionIndex_ >= descriptions_.size())
            currentDescriptionIndex_ = 0;

        ticksLastUpdate_ = now + rand() % kMaxRandomDelay_;
    }

    std::string
    ESSENCE8SYSTEM::GET8ESSENCE8DESCRIPTION(int index) {
        return descriptions_.at(index);
    }
}