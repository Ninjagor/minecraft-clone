#pragma once

#include "raylib.h"
#include <stdbool.h>

typedef enum BlockType {
    AIR_BLOCK = 0,
    GRASS_BLOCK = 1,
    STONE_BLOCK = 2,
} BlockType;

typedef struct Block {
    float x;
    float y;
    float z;
    Model model;
    BlockType block_type;
    bool is_selected;
} Block;

Block CreateBlock( float x, float y, float z, char * texture_path, BlockType block_type );

void RenderBlock ( Block block, Camera camera );

void ResetBlockCollision(void);