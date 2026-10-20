//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "GUI8COMPONENT.HPP"

namespace FORRADIA8GAME
{
    GUI8COMPONENT::GUI8COMPONENT(float x, float y) : position_(x, y)
    {
    }

    void
    GUI8COMPONENT::UPDATE()
    {
        if (!isEnabled_)
        {
            return;
        }

        if (parent_ && !parent_->isEnabled_)
        {
            return;
        }

        UPDATE8DERIVED();

        for (const auto &component : components_)
        {
            component->UPDATE();
        }
    }

    void
    GUI8COMPONENT::RENDER()
    {
        if (!isVisible_ || !isEnabled_)
        {
            return;
        }

        if (parent_ && (!parent_->isVisible_ && !parent_->isEnabled_))
        {
            return;
        }

        RENDER8DERIVED();

        for (const auto &component : components_)
        {
            component->RENDER();
        }
    }

    bool
    GUI8COMPONENT::ON8MOUSE8DOWN(Uint8 mouseButton)
    {
        if (!isVisible_ || !isEnabled_)
        {
            return false;
        }

        if (parent_ && (!parent_->isVisible_ && !parent_->isEnabled_))
        {
            return false;
        }

        if (std::any_of(components_.rbegin(), components_.rend(),
                        [=](const std::shared_ptr<GUI8COMPONENT> &comp)
                        { return comp->ON8MOUSE8DOWN(mouseButton); }))
        {
            return true;
        }

        return false;
    }

    bool
    GUI8COMPONENT::ON8MOUSE8UP(Uint8 mouseButton, int clickSpeed)
    {
        if (!isVisible_ || !isEnabled_)
        {
            return false;
        }

        if (parent_ && (!parent_->isVisible_ && !parent_->isEnabled_))
        {
            return false;
        }

        if (std::any_of(components_.rbegin(), components_.rend(),
                        [=](const std::shared_ptr<GUI8COMPONENT> &comp)
                        { return comp->ON8MOUSE8UP(mouseButton, clickSpeed); }))
        {
            return true;
        }

        return false;
    }

    bool
    GUI8COMPONENT::ON8KEY8DOWN(SDL_Keycode key)
    {
        if (!isVisible_ || !isEnabled_)
        {
            return false;
        }

        if (parent_ && (!parent_->isVisible_ && !parent_->isEnabled_))
        {
            return false;
        }

        if (std::any_of(components_.rbegin(), components_.rend(),
                        [=](const std::shared_ptr<GUI8COMPONENT> &comp)
                        { return comp->ON8KEY8DOWN(key); }))
        {
            return true;
        }

        return false;
    }

    bool
    GUI8COMPONENT::ON8KEY8UP(SDL_Keycode key)
    {
        if (!isVisible_ || !isEnabled_)
        {
            return false;
        }

        if (parent_ && (!parent_->isVisible_ && !parent_->isEnabled_))
        {
            return false;
        }

        if (std::any_of(components_.rbegin(), components_.rend(),
                        [=](const std::shared_ptr<GUI8COMPONENT> &comp)
                        { return comp->ON8KEY8UP(key); }))
        {
            return true;
        }

        return false;
    }

    std::shared_ptr<GUI8COMPONENT>
    GUI8COMPONENT::ADD8COMPONENT(std::shared_ptr<GUI8COMPONENT> component)
    {
        component->parent_ = this;

        components_.push_back(component);

        return component;
    }

    POINT8F
    GUI8COMPONENT::GET8POSITION()
    {
        POINT8F finalPosition = {0.0f, 0.0f};

        if (parent_)
        {
            finalPosition += parent_->GET8POSITION();
        }

        finalPosition += position_;

        return finalPosition;
    }

    void
    GUI8COMPONENT::SET8Y8POSITION(float y)
    {
        position_.y = y;
    }
}