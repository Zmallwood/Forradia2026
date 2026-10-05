// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class GUI;

class IScene
{
  public:
    IScene();

    void Initialize();

    void Update();

    void Render();

    void OnEnter();

    void OnKeyDown(SDL_Keycode key);

    void OnKeyUp(SDL_Keycode key);

    void OnMouseDown(Uint8 button);

    void OnMouseUp(Uint8 button, int clickSpeed);

  protected:
    virtual void InitializeDerived()
    {
    }

    virtual void OnEnterDerived()
    {
    }

    virtual void UpdateDerived()
    {
    }

    virtual void RenderBeforeGUIDerived()
    {
    }

    virtual void RenderAfterGUIDerived()
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