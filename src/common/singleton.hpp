#pragma once

namespace darktale
{
    template <class T>
    T &_()
    {
        static T instance;

        return instance;
    }
}