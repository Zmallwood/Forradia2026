// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class GUIComponent
{
  public:
    GUIComponent() = default;

    GUIComponent(float x, float y);

    void Update();

    void Render();

    virtual bool OnMouseDown(Uint8 mouseButton);

    virtual bool OnMouseUp(Uint8 mouseButton, int clickSpeed);

    virtual bool OnKeyDown(SDL_Keycode key);

    virtual bool OnKeyUp(SDL_Keycode key);

    std::shared_ptr<GUIComponent>
    AddComponent(std::shared_ptr<GUIComponent> component);

    virtual PointF GetPosition();

    void SetYPosition(float y);

    virtual void SetPosition(PointF value)
    {
        position_ = value;
    }

    bool isVisible_{true};
    bool isEnabled_{true};

  protected:
    virtual void UpdateDerived()
    {
    }

    virtual void RenderDerived()
    {
    }

  private:
    std::vector<std::shared_ptr<GUIComponent>> components_;
    PointF position_{0.0f, 0.0f};
    GUIComponent *parent_{nullptr};
};