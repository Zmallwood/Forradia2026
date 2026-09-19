/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class first_person_view
    {
      public:
        void render();

      private:
        static constexpr point_f k_margin_{0.03f, 0.01f};
    };
}