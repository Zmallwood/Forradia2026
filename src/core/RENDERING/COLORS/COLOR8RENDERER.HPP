//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME
{
    class COLOR8RENDERER
    {
      public:
        void FILL8RECT(float x, float y, float width, float height,
                       COLOR color = COLORS::kBlack);

        void FILL8RECT(RECT8F rect, COLOR color = COLORS::kBlack);

        void DRAW8RECT(float x, float y, float width, float height,
                       COLOR color = COLORS::kBlack);

        void DRAW8LINE(float x1, float y1, float x2, float y2,
                       COLOR color = COLORS::kBlack);

      private:
        SDL_Rect CREATE8SDL8RECT(float x, float y, float width, float height);
    };
}