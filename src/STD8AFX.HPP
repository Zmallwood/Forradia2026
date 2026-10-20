//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

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
#include "COMMON/MATTER/GEOMETRY/POINT8F.HPP"
#include "COMMON/MATTER/GEOMETRY/RECT8F.HPP"
#include "COMMON/MATTER/GEOMETRY/SIZE.HPP"
#include "COMMON/MATTER/GEOMETRY/SIZE8F.HPP"
#include "COMMON/CANVAS8UTILITIES.HPP"
#include "COMMON/CONSTANTS.HPP"
#include "COMMON/FILE8PATH8UTILITIES.HPP"
#include "COMMON/HASH.HPP"
#include "COMMON/MOUSE8UTILITIES.HPP"
#include "COMMON/NUMBER8UTILITIES.HPP"
#include "COMMON/SDL8DELETER.HPP"
#include "COMMON/SINGLETON.HPP"
#include "COMMON/STRING8UTILITIES.HPP"
#include "COMMON/TIME8UTILITIES.HPP"