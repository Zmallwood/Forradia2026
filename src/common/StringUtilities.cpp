/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "StringUtilities.hpp"

namespace Forradia
{
    std::string Replace(std::string_view text, std::string_view oldValue,
                        std::string_view newValue)
    {
        std::string result(text);

        size_t position{0};

        while ((position = result.find(oldValue, position)) !=
               std::string::npos)
        {
            result.replace(position, oldValue.length(), newValue);
            position += newValue.length();
        }

        return result;
    }
}