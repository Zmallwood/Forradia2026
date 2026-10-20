//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME
{
    class OBJECT;

    class OBJECT8MOVING
    {
      public:
        void ON8MOUSE8DOWN(Uint8 button);

        void ON8MOUSE8UP(Uint8 button, int clickSpeed);

        void RENDER();

        void CLEAR8OBJECT();

        auto
        GET8OBJECT8IN8AIR()
        {
            return objectInAir_;
        }

        void
        SET8OBJECT8IN8AIR(std::shared_ptr<OBJECT> value)
        {
            objectInAir_ = value;
        }

        POINT8F draggingMouseOffset_;

      private:
        std::shared_ptr<OBJECT> objectInAir_;
        POINT pickedPosition_;
    };
}