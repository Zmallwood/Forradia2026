/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

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

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Common/Matter/Coloring/color.hpp"
#include "Common/Matter/Coloring/colors.hpp"
#include "Common/Matter/Geometry/point.hpp"
#include "Common/Matter/Geometry/point_f.hpp"
#include "Common/Matter/Geometry/rect_f.hpp"
#include "Common/Matter/Geometry/size.hpp"
#include "Common/canvas_utilities.hpp"
#include "Common/constants.hpp"
#include "Common/file_path_utilities.hpp"
#include "Common/get_hash.hpp"
#include "Common/mouse_utilities.hpp"
#include "Common/number_utilities.hpp"
#include "Common/sdl_deleter.hpp"
#include "Common/singleton.hpp"
#include "Common/string_utilities.hpp"
#include "Common/time_utilities.hpp"
#include "Common/world_directions.hpp"