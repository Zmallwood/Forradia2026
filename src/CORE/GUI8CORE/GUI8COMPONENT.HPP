//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME {
    class GUI8COMPONENT {
      public:
        GUI8COMPONENT() = default;

        GUI8COMPONENT(float x, float y);

        void UPDATE();

        void RENDER();

        virtual bool ON8MOUSE8DOWN(Uint8 mouseButton);

        virtual bool ON8MOUSE8UP(Uint8 mouseButton, int clickSpeed);

        virtual bool ON8KEY8DOWN(SDL_Keycode key);

        virtual bool ON8KEY8UP(SDL_Keycode key);

        std::shared_ptr<GUI8COMPONENT>
        ADD8COMPONENT(std::shared_ptr<GUI8COMPONENT> component);

        virtual POINT8F GET8POSITION();

        void SET8Y8POSITION(float y);

        virtual void
        SET8POSITION(POINT8F value) {
            mPosition = value;
        }

        bool mIsVisible{true};
        bool mIsEnabled{true};

      protected:
        virtual void
        UPDATE8DERIVED() {
        }

        virtual void
        RENDER8DERIVED() {
        }

      private:
        std::vector<std::shared_ptr<GUI8COMPONENT>> mComponents;
        POINT8F mPosition{0.0F, 0.0F};
        GUI8COMPONENT *mParent{nullptr};
    };
}