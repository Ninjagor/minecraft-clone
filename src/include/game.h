#pragma once

#define CHUNK_RENDER_SIZE 25

#include "../world/world.h"

typedef struct Chunk {
    ChunkBlock*** chunk_block;
    int x_offset;
    int z_offset;
} Chunk;

void Init( void );

void Update( void );

void EndGame( void );