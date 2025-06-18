#pragma once

// Size of the SNES screen
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 224

#define SCREEN_WIDTH_HALF 128
#define SCREEN_HEIGHT_HALF 112

// Size of the world tilemap
#define WORLD_SIZE 512
#define TILE_SIZE 16
#define WORLD_TILE_LENGTH 32 // WORLD_SIZE / TILE_SIZE
#define WORLD_TILE_SIZE 1024 // WORLD_TILE_LENGTH * WORLD_TILE_LENGTH

// Math for optimization
#define CANVAS_MAX_X 256 // WORLD_SIZE - SCREEN_WIDTH
#define CANVAS_MAX_Y 288 // WORLD_SIZE - SCREEN_HEIGHT

#define PLAYER_MID_X 112 // SCREEN_WIDTH_HALF - player size (16)
#define PLAYER_MID_Y 96 // SCREEN_HEIGHT_HALF - player size (16)

#define U8_MAX 255