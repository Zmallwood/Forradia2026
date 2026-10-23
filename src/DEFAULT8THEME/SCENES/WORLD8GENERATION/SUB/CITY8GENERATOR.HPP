//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME {
    class CITY8GENERATOR {
      public:
        void GENERATE8CITY();

        POINT roadNetworkCenter_{-1, -1};

      private:
        void GENERATE8ROADS();

        void CLEAR8WITH8GRASS();

        void SET8BASE8ELEVATION();

        void GENERATE8DIRT();

        void GENERATE8HILLS();

        void GENERATE8LARGE8OBJECTS();

        void GENERATE8SMALL8OBJECTS();

        void GENERATE8CREATURES();

        void TRAVERSE81(std::function<void(int, int)> callback);

        void TRAVERSE82(std::function<void(int, int)> callback);

        void TRAVERSE83(std::function<void(int, int)> callback);

        void TRAVERSE84(std::function<void(int, int)> callback);
    };
}