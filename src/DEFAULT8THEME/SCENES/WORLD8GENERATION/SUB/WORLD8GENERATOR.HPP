//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME {
    class WORLD8GENERATOR {
      public:
        void GENERATE8NEW8WORLD();

      private:
        void CLEAR8WITH8GRASS();

        void TRAVERSE81(std::function<void(int, int)> callback);

        void TRAVERSE82(std::function<void(int, int)> callback);

        void TRAVERSE83(std::function<void(int, int)> callback);

        void TRAVERSE84(std::function<void(int, int)> callback);

        void GENERATE8LARGE8OBJECTS();

        void GENERATE8SMALL8OBJECTS();

        void GENERATE8CREATURES();
    };
}