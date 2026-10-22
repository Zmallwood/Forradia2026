//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME {
    class ESSENCE8INDEX {
      public:
        ESSENCE8INDEX();

        std::vector<std::string> GET8ESSENCE8DESCRIPTIONS(int nameHash);

      private:
        void ADD8ENTRY(std::string_view name,
                       std::vector<std::string> descriptions);

        std::unordered_map<int, std::vector<std::string>> entries_;
    };
}