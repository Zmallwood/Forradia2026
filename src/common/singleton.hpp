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
    std::shared_ptr<T> GetSingletonPtr()
    {
        static std::shared_ptr<T> instance = std::make_shared<T>();

        return instance;
    }

    template <class T>
    T &_()
    {
        auto ptr{GetSingletonPtr<T>()};

        return *ptr;
    }
}