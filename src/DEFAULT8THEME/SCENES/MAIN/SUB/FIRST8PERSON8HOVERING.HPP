//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME {
    class OBJECT;
    class CREATURE;

    class FIRST8PERSON8HOVERING {
      public:
        void UPDATE();

        void RENDER();

        std::shared_ptr<OBJECT> hoveredObject_;
        std::shared_ptr<CREATURE> hoveredCreature_;
        POINT8F hoveredThingMouseOffset_;

      private:
        static constexpr float kTextYOffset_{-0.03f};
    };
}