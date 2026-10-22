//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME {
    class GAME8PROPERTIES {
      public:
        static constexpr std::string_view kWindowName_{"Forradia"};
        static constexpr SIZE kWorldAreaSize_{100, 100};
        static constexpr float kTileWidth_{0.07F};
        static constexpr int kTileGridSize_{15};
        static constexpr int kTileUnitsWidth_{20};
        static constexpr float kViewWidth_{0.5F};
        static constexpr float kLargeObjectScale_{0.35F};
        static constexpr float kSmallObjectScale_{0.08F};
        static constexpr POINT8F kFirstPersonViewMargin_{0.03F, 0.01F};
        static constexpr float kImpactPointWidth_{0.005F};
        static constexpr float kHoveringLabelYOffset_{-0.03F};
        static constexpr float kWorldViewYOffset_{0.07F};
    };
}