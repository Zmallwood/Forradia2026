/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "string_utilities.hpp"

namespace Forradia
{
    std::string replace(std::string_view text, std::string_view old_value,
                        std::string_view new_value)
    {
        std::string result(text);

        size_t pos = 0;

        while ((pos = result.find(old_value, pos)) != std::string::npos)
        {
            result.replace(pos, old_value.length(), new_value);
            pos += new_value.length();
        }

        return result;
    }
}