//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME {
    class OBJECT;

    class OBJECT8IMPACT8ACTION {
      public:
        std::string objectName;
        std::function<void()> singleImpactPointCompletedAction;
        std::function<void(std::shared_ptr<OBJECT>)>
            allImpactPointsCompletedAction;
    };
}