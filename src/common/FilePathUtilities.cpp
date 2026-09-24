/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "FilePathUtilities.hpp"

namespace Forradia
{
    std::string GetFileNameNoExt(std::string_view path)
    {
        auto fileName{std::filesystem::path(path).filename().string()};

        return fileName.substr(0, fileName.find_last_of("."));
    }
}