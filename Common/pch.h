#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
#include <iostream>
#include <windows.h>
#include <string>
#include <unordered_map>
#include <set>
#include <vector>
#include <functional>
#include <queue>
#include <algorithm>
#include <limits>

#include "Util.h"
#include "VectorMath.h"
#include "GameConfig.h"

using std::string;
using std::wstring;
using std::vector;
using std::set;
using std::unordered_map;
using std::queue;
using std::priority_queue;
using std::pair;
using std::function;
using std::unique_ptr;
using std::make_unique;
using std::move;