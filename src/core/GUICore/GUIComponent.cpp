// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "GUIComponent.hpp"

GUIComponent::GUIComponent(float x, float y) : position_(x, y)
{
}

void GUIComponent::Update()
{
    if (!isEnabled_)
    {
        return;
    }

    if (parent_ && !parent_->isEnabled_)
    {
        return;
    }

    UpdateDerived();

    for (const auto &component : components_)
    {
        component->Update();
    }
}

void GUIComponent::Render()
{
    if (!isVisible_ || !isEnabled_)
    {
        return;
    }

    if (parent_ && (!parent_->isVisible_ && !parent_->isEnabled_))
    {
        return;
    }

    RenderDerived();

    for (const auto &component : components_)
    {
        component->Render();
    }
}

bool GUIComponent::OnMouseDown(Uint8 mouseButton)
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
                    [=](const std::shared_ptr<GUIComponent> &comp)
                    { return comp->OnMouseDown(mouseButton); }))
    {
        return true;
    }

    return false;
}

bool GUIComponent::OnMouseUp(Uint8 mouseButton, int clickSpeed)
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
                    [=](const std::shared_ptr<GUIComponent> &comp)
                    { return comp->OnMouseUp(mouseButton, clickSpeed); }))
    {
        return true;
    }

    return false;
}

bool GUIComponent::OnKeyDown(SDL_Keycode key)
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
                    [=](const std::shared_ptr<GUIComponent> &comp)
                    { return comp->OnKeyDown(key); }))
    {
        return true;
    }

    return false;
}

bool GUIComponent::OnKeyUp(SDL_Keycode key)
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
                    [=](const std::shared_ptr<GUIComponent> &comp)
                    { return comp->OnKeyUp(key); }))
    {
        return true;
    }

    return false;
}

std::shared_ptr<GUIComponent>
GUIComponent::AddComponent(std::shared_ptr<GUIComponent> component)
{
    component->parent_ = this;

    components_.push_back(component);

    return component;
}

PointF GUIComponent::GetPosition()
{
    PointF finalPosition{0.0F, 0.0F};

    if (parent_)
    {
        finalPosition += parent_->GetPosition();
    }

    finalPosition += position_;

    return finalPosition;
}

void GUIComponent::SetYPosition(float y)
{
    position_.y = y;
}