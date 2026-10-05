/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    template <class T>
    std::shared_ptr<T> &SingletonStorage()
    {
        static std::shared_ptr<T> instance = std::make_shared<T>();

        return instance;
    }

    template <class T>
    std::shared_ptr<T> GetSingletonPtr()
    {
        auto &instance{SingletonStorage<T>()};

        if (!instance)
        {
            instance = std::make_shared<T>();
        }

        return instance;
    }

    template <class T>
    void DestroySingleton()
    {
        SingletonStorage<T>().reset();
    }

    template <class T>
    T &_()
    {
        return *GetSingletonPtr<T>();
    }
}