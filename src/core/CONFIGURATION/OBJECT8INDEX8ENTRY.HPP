//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME {
    class OBJECT;

    class OBJECT8INDEX8ENTRY {
      public:
        std::string label;
        int flags = 0;
        std::vector<POINT8F> impactPoints;
        std::vector<int> impactObjects;
        std::function<void()> singleImpactPointCompletedAction;
        std::function<void(std::shared_ptr<OBJECT>)>
            allImpactPointsCompletedAction;
        int worldViewObjectType = 0;
        POINT8F worldViewRenderOffset = {0.0f, 0.0f};
        POINT8F firstPersonViewRenderOffset = {0.0f, 0.0f};
    };
}