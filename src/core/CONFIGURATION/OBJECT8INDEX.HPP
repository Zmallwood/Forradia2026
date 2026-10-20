//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "OBJECT8INDEX8ENTRY.HPP"

namespace FORRADIA8GAME
{
    class OBJECT8INDEX
    {
      public:
        OBJECT8INDEX();

        bool IS8SMALL8OBJECT(int objectHash);

        std::string GET8OBJECT8LABEL(int objectHash);

        bool OBJECT8BLOCKSSIGHT(int objectHash);

        bool OBJECT8UNMOVABLE(int objectHash);

        std::vector<POINT8F> GET8IMPACT8POINTS(int objectHash);

        std::vector<int> GET8IMPACT8OBJECTS(int objectHash);

        std::function<void()>
        GET8SINGLE8IMPACT8POINT8COMPLETED8ACTION(int objectHash);

        std::function<void(std::shared_ptr<OBJECT>)>
        GET8ALL8IMPACT8POINTS8COMPLETED8ACTION(int objectHash);

        int GET8WORLD8VIEW8OBJECT8TYPE(int objectHash);

        POINT8F GET8WORLD8VIEW8RENDER8OFFSET(int objectHash);

        POINT8F GET8FIRST8PERSON8VIEW8RENDER8OFFSET(int objectHash);

      private:
        void ADD8ENTRY(
            std::string_view objectName, std::string_view label, int flags,
            std::vector<POINT8F> impactPoints = {},
            std::vector<std::string> impactObjects = {},
            std::function<void()> singleImpactPointCompletedAction = []() {},
            std::function<void(std::shared_ptr<OBJECT>)>
                allImpactPointsCompletedAction = [](std::shared_ptr<OBJECT>) {},
            std::string_view worldViewObjectType = "",
            POINT8F worldViewRenderOffset = POINT8F{0.0f, 0.0f},
            POINT8F firstPersonViewRenderOffset = POINT8F{0.0f, 0.0f});

        std::unordered_map<int, OBJECT8INDEX8ENTRY> entries_;
    };
}