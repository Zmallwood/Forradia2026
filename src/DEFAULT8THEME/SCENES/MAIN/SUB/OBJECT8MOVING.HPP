//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME {
    class OBJECT;

    class OBJECT8MOVING {
      public:
        void ON8MOUSE8DOWN(Uint8 button);

        void ON8MOUSE8UP(Uint8 button, int clickSpeed);

        void RENDER();

        void CLEAR8OBJECT();

        void MOVE8OBJECT8TO8PICKUP8LOCATION(std::shared_ptr<OBJECT> object);

        void SET8PICKED8INVENTORY8POSITION(int position);

        void SET8PICKED8EQUIPMENT8SLOT(int slot);

        auto
        GET8OBJECT8IN8AIR() {
            return objectInAir_;
        }

        void
        SET8OBJECT8IN8AIR(std::shared_ptr<OBJECT> value) {
            objectInAir_ = value;
        }

        POINT8F draggingMouseOffset_;

      private:
        void SET8PICKED8POSITION(POINT position);

        std::shared_ptr<OBJECT> objectInAir_;
        POINT pickedPosition_{-1, -1};
        int pickedInventoryPosition_{-1};
        int pickedEquipmentSlot_{-1};
    };
}