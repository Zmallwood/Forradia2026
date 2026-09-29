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

        std::shared_ptr<Object> objectInAir_;

      private:
        static constexpr float k_imageWidth_{0.05f};
        PointF draggingMouseOffset_;
        Point pickedPosition_;
    };
}