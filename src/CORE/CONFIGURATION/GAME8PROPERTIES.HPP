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
        static constexpr std::string_view mkWindowName{"Forradia"};
        static constexpr SIZE mkWorldAreaSize{100, 100};
        static constexpr float mkTileWidth{0.07F};
        static constexpr int mkTileGridSize{15};
        static constexpr int mkTileUnitsWidth{20};
        static constexpr float mkViewWidth{0.5F};
        static constexpr float mkLargeObjectScale{0.35F};
        static constexpr float mkSmallObjectScale{0.08F};
        static constexpr POINT8F mkFirstPersonViewMargin{0.03F, 0.01F};
        static constexpr float mkImpactPointWidth{0.005F};
        static constexpr float mkHoveringLabelYOffset{-0.03F};
        static constexpr float mkWorldViewYOffset{0.07F};
    };
}