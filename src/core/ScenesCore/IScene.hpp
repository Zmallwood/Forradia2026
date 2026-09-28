/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class GUI;

    class IScene
    {
      public:
        IScene();

        void Initialize();

        void Update();

        void Render();

        virtual void OnEnter()
        {
        }

        void OnKeyDown(SDL_Keycode key);

        void OnKeyUp(SDL_Keycode key);

        void OnMouseDown(Uint8 button);

        void OnMouseUp(Uint8 button, int clickSpeed);

      protected:
        virtual void InitializeDerived()
        {
        }

        virtual void UpdateDerived()
        {
        }

        virtual void RenderDerived()
        {
        }

        virtual void OnKeyDownDerived(SDL_Keycode key)
        {
        }

        virtual void OnKeyUpDerived(SDL_Keycode key)
        {
        }

        virtual void OnMouseDownDerived(Uint8 button)
        {
        }

        virtual void OnMouseUpDerived(Uint8 button, int clickSpeed)
        {
        }

        std::shared_ptr<GUI> gui_;
    };
}