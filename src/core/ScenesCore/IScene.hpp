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

        virtual void OnKeyDown(SDL_Keycode key);

        virtual void OnKeyUp(SDL_Keycode key);

        virtual void OnMouseDown(Uint8 button);

        virtual void OnMouseUp(Uint8 button, int clickSpeed);

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

        std::shared_ptr<GUI> gui_;
    };
}