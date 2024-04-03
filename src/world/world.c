#include "world.h"
#include "raylib.h"
#include "../blocks/block.h"
#include "../blocks/grass_block.h"
#include <stdlib.h>
#include <math.h>
#include "perlin.h"


ChunkBlock*** GenerateChunk(int offsetX, int offsetZ) {
    ChunkBlock*** chunk = malloc(CHUNK_WIDTH * sizeof(ChunkBlock**));
    for (int x = 0; x < CHUNK_WIDTH; x++) {
        chunk[x] = malloc(CHUNK_LENGTH * sizeof(ChunkBlock*));
        for (int z = 0; z < CHUNK_LENGTH; z++) {
            chunk[x][z] = malloc(CHUNK_HEIGHT * sizeof(ChunkBlock));
            for (int y = 0; y < CHUNK_HEIGHT; y++) {
                float perlin_value = perlin2d((float)(x + offsetX * CHUNK_WIDTH), (float)(z + offsetZ * CHUNK_LENGTH), 0.06f, 0.5f);

                // Initialize the ChunkBlock with the BlockType
                if (y > CHUNK_HEIGHT - (CHUNK_HEIGHT * perlin_value)) {
                    chunk[x][z][y].block_type = AIR_BLOCK;
                } else if (y > CHUNK_HEIGHT - (CHUNK_HEIGHT * 0.5f)) {
                    chunk[x][z][y].block_type = GRASS_BLOCK;
                } else {
                    chunk[x][z][y].block_type = STONE_BLOCK;
                }

                // Initialize the neighbor_count to 0
                chunk[x][z][y].neighbor_count = 0;
            }
        }
    }

    // Calculate neighbor counts
    for (int x = 0; x < CHUNK_WIDTH; x++) {
        for (int z = 0; z < CHUNK_LENGTH; z++) {
            for (int y = 0; y < CHUNK_HEIGHT; y++) {
                if (chunk[x][z][y].block_type != AIR_BLOCK) {
                    // Check each face for neighboring blocks
                    if (x > 0 && chunk[x - 1][z][y].block_type != AIR_BLOCK) chunk[x][z][y].neighbor_count++;
                    if (x < CHUNK_WIDTH - 1 && chunk[x + 1][z][y].block_type != AIR_BLOCK) chunk[x][z][y].neighbor_count++;
                    if (z > 0 && chunk[x][z - 1][y].block_type != AIR_BLOCK) chunk[x][z][y].neighbor_count++;
                    if (z < CHUNK_LENGTH - 1 && chunk[x][z + 1][y].block_type != AIR_BLOCK) chunk[x][z][y].neighbor_count++;
                    if (y > 0 && chunk[x][z][y - 1].block_type != AIR_BLOCK) chunk[x][z][y].neighbor_count++;
                    if (y < CHUNK_HEIGHT - 1 && chunk[x][z][y + 1].block_type != AIR_BLOCK) chunk[x][z][y].neighbor_count++;
                }
            }
        }
    }

    return chunk;
}

// if u dont run this u die lil bro
void CleanupChunk( ChunkBlock*** chunk ) {
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) {
            free(chunk[x][y]);
        }
        free(chunk[x]);
    }
    free(chunk);
}