/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class SDLDevice
    {
      public:
        SDLDevice();

        void ClearCanvas();

        void PresentCanvas();

        void Clip(float x, float y, float width, float height);

        void ResetClip();

        std::shared_ptr<SDL_Window> window_;
        std::shared_ptr<SDL_Renderer> renderer_;

      private:
        static constexpr std::string_view k_window_name_{"Darktale"};
    };
}