//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA
{
    class OBJECT;

    class ObjectMoving
    {
      public:
        void OnMouseDown(Uint8 button);

        void OnMouseUp(Uint8 button, int clickSpeed);

        void Render();

        void ClearObject();

        auto
        GetObjectInAir()
        {
            return objectInAir_;
        }

        void
        SetObjectInAir(std::shared_ptr<OBJECT> value)
        {
            objectInAir_ = value;
        }

        POINT8F draggingMouseOffset_;

      private:
        std::shared_ptr<OBJECT> objectInAir_;
        POINT pickedPosition_;
    };
}