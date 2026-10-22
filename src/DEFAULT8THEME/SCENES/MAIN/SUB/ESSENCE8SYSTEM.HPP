//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME {
    class ESSENCE8SYSTEM {
      public:
        ESSENCE8SYSTEM();

        void UPDATE();

        std::string GET8ESSENCE8DESCRIPTION(int index);

        static constexpr int kMaxDescriptions_{6};

      private:
        static constexpr int kNoticingRadius_{8};
        std::vector<std::string> descriptions_;
        int currentDescriptionIndex_{0};
        int ticksLastUpdate_{0};
        int ticksPerUpdate_{500};
    };
}