/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class Object;

    class ObjectMoving
    {
      public:
        void OnMouseDown(Uint8 button);

        void OnMouseUp(Uint8 button, int clickSpeed);

        void Render();

        void ClearObject();

        auto GetObjectInAir()
        {
            return objectInAir_;
        }

        void SetObjectInAir(std::shared_ptr<Object> value)
        {
            objectInAir_ = value;
        }

        PointF draggingMouseOffset_;

      private:
        std::shared_ptr<Object> objectInAir_;
        Point pickedPosition_;
    };
}