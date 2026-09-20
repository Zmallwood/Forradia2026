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
        auto file_name{std::filesystem::path(path).filename().string()};

        return file_name.substr(0, file_name.find_last_of("."));
    }
}