//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME {
    class WORLD8AREA;

    class CITY8GENERATOR {
      public:
        std::shared_ptr<WORLD8AREA> GENERATE8CITY();

        POINT roadNetworkCenter_{-1, -1};

      private:
        void GENERATE8ROADS(std::shared_ptr<WORLD8AREA> worldArea);

        void CLEAR8WITH8GRASS(std::shared_ptr<WORLD8AREA> worldArea);

        void SET8BASE8ELEVATION(std::shared_ptr<WORLD8AREA> worldArea);

        void GENERATE8DIRT(std::shared_ptr<WORLD8AREA> worldArea);

        void GENERATE8HILLS(std::shared_ptr<WORLD8AREA> worldArea);

        void GENERATE8LARGE8OBJECTS(std::shared_ptr<WORLD8AREA> worldArea);

        void GENERATE8SMALL8OBJECTS(std::shared_ptr<WORLD8AREA> worldArea);

        void GENERATE8CREATURES(std::shared_ptr<WORLD8AREA> worldArea);

        void GENERATE8WATER(std::shared_ptr<WORLD8AREA> worldArea);

        void GENERATE8MOUNTAINS(std::shared_ptr<WORLD8AREA> worldArea);

        void GENERATE8FORESTS(std::shared_ptr<WORLD8AREA> worldArea);

        void TRAVERSE81(std::shared_ptr<WORLD8AREA> worldArea,
                        std::function<void(int, int)> callback);

        void TRAVERSE82(std::shared_ptr<WORLD8AREA> worldArea,
                        std::function<void(int, int)> callback);

        void TRAVERSE83(std::shared_ptr<WORLD8AREA> worldArea,
                        std::function<void(int, int)> callback);

        void TRAVERSE84(std::shared_ptr<WORLD8AREA> worldArea,
                        std::function<void(int, int)> callback);
    };
}