#pragma once

#include "VectorMath.h"

constexpr int32 GWinSizeX = 1760;
constexpr int32 GWinSizeY = 1040;
constexpr int32 GameAreaWidth = 1440;
constexpr int32 GameAreaHeight = 1040;
constexpr int32 BLOCK_SIZE = 80;
constexpr int32 GRID_COUNT_X = GameAreaWidth / BLOCK_SIZE;
constexpr int32 GRID_COUNT_Y = GameAreaHeight / BLOCK_SIZE;
static_assert(GRID_COUNT_X* BLOCK_SIZE == GameAreaWidth, "BLOCK_SIZE가 GameAreaWidth를 나누어떨어뜨리지 않습니다");
static_assert(GRID_COUNT_Y* BLOCK_SIZE == GameAreaHeight, "BLOCK_SIZE가 GameAreaHeight를 나누어떨어뜨리지 않습니다");
constexpr int32 GameAreaCenterX = GameAreaWidth / 2;
constexpr int32 GameAreaCenterY = GameAreaHeight / 2;
