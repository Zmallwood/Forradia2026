//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME
{
    class SDL8DEVICE
    {
      public:
        SDL8DEVICE();

        void CLEAR8CANVAS();

        void PRESENT8CANVAS();

        void CLIP(float x, float y, float width, float height);

        void RESET8CLIP();

        std::shared_ptr<SDL_Window> window_;
        std::shared_ptr<SDL_Renderer> renderer_;

      private:
        static constexpr std::string_view kWindowName_ = "Forradia";
    };
}