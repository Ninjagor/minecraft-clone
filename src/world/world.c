#include "world.h"
#include "raylib.h"
#include "../blocks/block.h"
#include "../blocks/grass_block.h"
#include <stdlib.h>
#include <math.h>
#include "perlin.h"

// why did i even do this
#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 32
#define CHUNK_LENGTH 16



BlockType*** GenerateChunk(void) {
    BlockType*** chunk = malloc(CHUNK_WIDTH * sizeof(BlockType**));
    for (int x = 0; x < CHUNK_WIDTH; x++) {
        chunk[x] = malloc(CHUNK_LENGTH * sizeof(BlockType*));
        for (int z = 0; z < CHUNK_LENGTH; z++) {
            chunk[x][z] = malloc(CHUNK_HEIGHT * sizeof(BlockType));
            for (int y = 0; y < CHUNK_HEIGHT; y++) {
                float perlin_value = perlin2d((float)x, (float)z, 0.06f, 0.5f);

                if (y > CHUNK_HEIGHT - (CHUNK_HEIGHT * perlin_value)) {
                    chunk[x][z][y] = AIR_BLOCK;
                } else if (y > CHUNK_HEIGHT - (CHUNK_HEIGHT * 0.5f)) {
                    chunk[x][z][y] = GRASS_BLOCK;
                } else {
                    chunk[x][z][y] = STONE_BLOCK;
                }
            }
        }
    }
    return chunk;
}

// if u dont run this u die lil bro
void CleanupChunk( BlockType*** chunk ) {
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) {
            free(chunk[x][y]);
        }
        free(chunk[x]);
    }
    free(chunk);
}