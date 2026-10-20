// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "FILE8PATH8UTILITIES.HPP"

std::string GET8FILE8NAME8NO8EXT(std::string_view path)
{
    auto fileName = std::filesystem::path(path).filename().string();

    return fileName.substr(0, fileName.find_last_of("."));
}