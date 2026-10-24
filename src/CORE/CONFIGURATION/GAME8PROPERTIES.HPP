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
        static constexpr std::string_view kWindowName{"Forradia"};
        static constexpr SIZE kWorldAreaSize{100, 100};
        static constexpr float kTileWidth{0.07F};
        static constexpr int kTileGridSize{15};
        static constexpr int kTileUnitsWidth{20};
        static constexpr float kViewWidth{0.5F};
        static constexpr float kLargeObjectScale{0.35F};
        static constexpr float kSmallObjectScale{0.08F};
        static constexpr POINT8F kFirstPersonViewMargin{0.03F, 0.01F};
        static constexpr float kImpactPointWidth{0.005F};
        static constexpr float kHoveringLabelYOffset{-0.03F};
        static constexpr float kWorldViewYOffset{0.07F};
    };
}