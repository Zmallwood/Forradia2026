// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include <compare>
#include <filesystem>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <functional>
#include <sstream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "COMMON/MATTER/COLORING/COLOR.HPP"
#include "COMMON/MATTER/COLORING/COLORS.HPP"
#include "COMMON/MATTER/GEOMETRY/POINT.HPP"
#include "COMMON/MATTER/GEOMETRY/POINT_F.HPP"
#include "COMMON/MATTER/GEOMETRY/RECT_F.HPP"
#include "COMMON/MATTER/GEOMETRY/SIZE.HPP"
#include "COMMON/MATTER/GEOMETRY/SIZE_F.HPP"
#include "COMMON/CANVAS_UTILITIES.HPP"
#include "COMMON/CONSTANTS.HPP"
#include "COMMON/FILE_PATH_UTILITIES.HPP"
#include "COMMON/HASH.HPP"
#include "COMMON/MOUSE_UTILITIES.HPP"
#include "COMMON/NUMBER_UTILITIES.HPP"
#include "COMMON/SDL_DELETER.HPP"
#include "COMMON/SINGLETON.HPP"
#include "COMMON/STRING_UTILITIES.HPP"
#include "COMMON/TIME_UTILITIES.HPP"