// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class ColorRenderer
{
  public:
    void FillRect(float x, float y, float width, float height,
                  COLOR color = COLORS::k_black);

    void FillRect(RECT8F rect, COLOR color = COLORS::k_black);

    void DrawRect(float x, float y, float width, float height,
                  COLOR color = COLORS::k_black);

    void DrawLine(float x1, float y1, float x2, float y2,
                  COLOR color = COLORS::k_black);

  private:
    SDL_Rect CreateSDLRect(float x, float y, float width, float height);
};