#pragma once

#include "raylib.h"
#include "../blocks/block.h"

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 16
#define CHUNK_LENGTH 16

typedef struct ChunkBlock {
    BlockType block_type;
    int neighbor_count;
} ChunkBlock;

ChunkBlock*** GenerateChunk(int offsetX, int offsetZ);

void CleanupChunk( ChunkBlock*** chunk );