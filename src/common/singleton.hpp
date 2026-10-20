// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

template <class T>
std::shared_ptr<T> &
SINGLETON8STORAGE()
{
    static std::shared_ptr<T> instance = std::make_shared<T>();

    return instance;
}

template <class T>
std::shared_ptr<T>
GET8SINGLETON8PTR()
{
    auto &instance = SINGLETON8STORAGE<T>();

    if (!instance)
    {
        instance = std::make_shared<T>();
    }

    return instance;
}

template <class T>
void
DESTROY8SINGLETON()
{
    SINGLETON8STORAGE<T>().reset();
}

template <class T>
T &
_()
{
    return *GET8SINGLETON8PTR<T>();
}