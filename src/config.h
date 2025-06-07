#pragma once

// Size of the SNES screen
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 224

#define SCREEN_WIDTH_HALF 128
#define SCREEN_HEIGHT_HALF 112

// Size of the world tilemap
#define WORLD_SIZE 512

// Math for optimization
#define CANVAS_MAX_X 256 // WORLD_SIZE - SCREEN_WIDTH
#define CANVAS_MAX_Y 288 // WORLD_SIZE - SCREEN_HEIGHT

#define PLAYER_MID_X 112 // SCREEN_WIDTH_HALF - player size (16)
#define PLAYER_MID_Y 96 // SCREEN_HEIGHT_HALF - player size (16)