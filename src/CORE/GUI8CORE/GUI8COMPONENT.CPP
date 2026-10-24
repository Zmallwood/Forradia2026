//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "GUI8COMPONENT.HPP"

namespace FORRADIA8GAME {
    GUI8COMPONENT::GUI8COMPONENT(float x, float y) : mPosition(x, y) {
    }

    void
    GUI8COMPONENT::UPDATE() {
        if (!mIsEnabled)
            return;

        if (mParent && !mParent->mIsEnabled)
            return;

        UPDATE8DERIVED();

        for (const auto &component : mComponents)
            component->UPDATE();
    }

    void
    GUI8COMPONENT::RENDER() {
        if (!mIsVisible || !mIsEnabled)
            return;

        if (mParent && (!mParent->mIsVisible && !mParent->mIsEnabled))
            return;

        RENDER8DERIVED();

        for (const auto &component : mComponents)
            component->RENDER();
    }

    bool
    GUI8COMPONENT::ON8MOUSE8DOWN(Uint8 mouseButton) {
        if (!mIsVisible || !mIsEnabled)
            return false;

        if (mParent && (!mParent->mIsVisible && !mParent->mIsEnabled))
            return false;

        if (std::any_of(mComponents.rbegin(), mComponents.rend(),
                        [=](const std::shared_ptr<GUI8COMPONENT> &component) {
                            return component->ON8MOUSE8DOWN(mouseButton);
                        }))
            return true;

        return false;
    }

    bool
    GUI8COMPONENT::ON8MOUSE8UP(Uint8 mouseButton, int clickSpeed) {
        if (!mIsVisible || !mIsEnabled)
            return false;

        if (mParent && (!mParent->mIsVisible && !mParent->mIsEnabled))
            return false;

        if (std::any_of(mComponents.rbegin(), mComponents.rend(),
                        [=](const std::shared_ptr<GUI8COMPONENT> &component) {
                            return component->ON8MOUSE8UP(mouseButton,
                                                          clickSpeed);
                        }))
            return true;

        return false;
    }

    bool
    GUI8COMPONENT::ON8KEY8DOWN(SDL_Keycode key) {
        if (!mIsVisible || !mIsEnabled)
            return false;

        if (mParent && (!mParent->mIsVisible && !mParent->mIsEnabled))
            return false;

        if (std::any_of(mComponents.rbegin(), mComponents.rend(),
                        [=](const std::shared_ptr<GUI8COMPONENT> &component) {
                            return component->ON8KEY8DOWN(key);
                        }))
            return true;

        return false;
    }

    bool
    GUI8COMPONENT::ON8KEY8UP(SDL_Keycode key) {
        if (!mIsVisible || !mIsEnabled)
            return false;

        if (mParent && (!mParent->mIsVisible && !mParent->mIsEnabled))
            return false;

        if (std::any_of(mComponents.rbegin(), mComponents.rend(),
                        [=](const std::shared_ptr<GUI8COMPONENT> &component) {
                            return component->ON8KEY8UP(key);
                        }))
            return true;

        return false;
    }

    std::shared_ptr<GUI8COMPONENT>
    GUI8COMPONENT::ADD8COMPONENT(std::shared_ptr<GUI8COMPONENT> component) {
        component->mParent = this;

        mComponents.push_back(component);

        return component;
    }

    POINT8F
    GUI8COMPONENT::GET8POSITION() {
        POINT8F finalPosition{0.0F, 0.0F};

        if (mParent)
            finalPosition += mParent->GET8POSITION();

        finalPosition += mPosition;

        return finalPosition;
    }

    void
    GUI8COMPONENT::SET8Y8POSITION(float y) {
        mPosition.y = y;
    }
}