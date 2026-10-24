//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME {
    class OBJECT;

    class PLAYER8INVENTORY {
      public:
        void ADD8OBJECT(std::string_view objectName);

        void ADD8OBJECT(std::shared_ptr<OBJECT> object, int slotIndex);

        std::shared_ptr<OBJECT> GET8OBJECT(int index);

        std::shared_ptr<OBJECT> PICK8OBJECT(int index);

        bool HAS8OBJECT(int index);

      private:
        static constexpr int kMaxObjects{1000};
        std::unordered_map<int, std::shared_ptr<OBJECT>> mObjects;
    };
}