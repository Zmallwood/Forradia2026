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

#include "Common/Matter/Coloring/Color.hpp"
#include "Common/Matter/Coloring/Colors.hpp"
#include "Common/Matter/Geometry/Point.hpp"
#include "Common/Matter/Geometry/PointF.hpp"
#include "Common/Matter/Geometry/RectF.hpp"
#include "Common/Matter/Geometry/Size.hpp"
#include "Common/CanvasUtilities.hpp"
#include "Common/Constants.hpp"
#include "Common/FilePathUtilities.hpp"
#include "Common/GetHash.hpp"
#include "Common/MouseUtilities.hpp"
#include "Common/NumberUtilities.hpp"
#include "Common/SDLDeleter.hpp"
#include "Common/Singleton.hpp"
#include "Common/StringUtilities.hpp"
#include "Common/TimeUtilities.hpp"
#include "Common/WorldDirections.hpp"