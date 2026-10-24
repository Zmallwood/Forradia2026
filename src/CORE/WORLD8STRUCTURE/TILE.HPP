//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "ROAD8ORIENTATION.HPP"

namespace FORRADIA8GAME {
    class TILE8OBJECTS;
    class CREATURE;
    class NPC;

    class TILE {
      public:
        TILE();

        int mGround{0};
        int mElevation{0};
        std::shared_ptr<TILE8OBJECTS> mTileObjects;
        std::shared_ptr<CREATURE> mCreature;
        std::shared_ptr<NPC> mNPC;
        ROAD8ORIENTATION mRoadOrientation{ROAD8ORIENTATION::None};
    };
}