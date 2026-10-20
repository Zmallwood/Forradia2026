//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME
{
    class GUI;

    class I8SCENE
    {
      public:
        I8SCENE();

        void INITIALIZE();

        void UPDATE();

        void RENDER();

        void ON8ENTER();

        void ON8KEY8DOWN(SDL_Keycode key);

        void ON8KEY8UP(SDL_Keycode key);

        void ON8MOUSE8DOWN(Uint8 button);

        void ON8MOUSE8UP(Uint8 button, int clickSpeed);

      protected:
        virtual void
        INITIALIZE8DERIVED()
        {
        }

        virtual void
        ON8ENTER8DERIVED()
        {
        }

        virtual void
        UPDATE8DERIVED()
        {
        }

        virtual void
        RENDER8BEFORE8GUI8DERIVED()
        {
        }

        virtual void
        RENDER8AFTER8GUI8DERIVED()
        {
        }

        virtual void
        ON8KEY8DOWN8DERIVED(SDL_Keycode key)
        {
        }

        virtual void
        ON8KEY8UP8DERIVED(SDL_Keycode key)
        {
        }

        virtual void
        ON8MOUSE8DOWN8DERIVED(Uint8 button)
        {
        }

        virtual void
        ON8MOUSE8UP8DERIVED(Uint8 button, int clickSpeed)
        {
        }

        std::shared_ptr<GUI> gui_;
    };
}