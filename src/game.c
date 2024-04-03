#include "raylib.h"
#include "include/constants.h"
#include "include/game.h"
#include "blocks/block.h"
#include "world/world.h"
#include "blocks/grass_block.h"
#include "blocks/stone_block.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Camera3D camera = { 0 };
Camera2D camera2d = { 0 };
Vector3 camera_target = ( Vector3 ){ -5.0f, 2.0f, 0.0f };

Texture2D crosshairTexture;

Block grass_block;
Block stone_block;
Model model;
Vector3 mapPosition;

Block grass_block;
Block stone_block;

ChunkBlock*** chunk_map;
ChunkBlock*** chunk_map2;
ChunkBlock*** chunk_map3;
ChunkBlock*** chunk_map4;

Chunk* chunks;

void Init( void ) {
    camera.position = ( Vector3 ){ 0.0f, 5.0f, 5.0f };
    camera.target = camera_target; 
    camera.up = (  Vector3 ){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;    
    camera.projection = CAMERA_PERSPECTIVE;  


    camera2d.target = (Vector2){ (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 };
    camera2d.offset = (Vector2){ (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 };
    camera2d.rotation = 0.0f;
    camera2d.zoom = 1.0f;

    crosshairTexture = LoadTexture("/Users/rohit/rohit-project-work/minecraft-clone/src/images/crosshair.png");

    grass_block = LoadGrassBlockModel(0.0f, 0.0f, 0.0f);

    stone_block = LoadStoneBlockModel(0.0f, 0.0f, 0.0f);

    chunk_map = GenerateChunk(0, 0);
    chunk_map2 = GenerateChunk(-1, 0);
    chunk_map3 = GenerateChunk(0, -1);
    chunk_map4 = GenerateChunk(-1, -1);

    // chunks = malloc(CHUNK_RENDER_SIZE * sizeof(ChunkBlock***));

    // for (int x = 0; x < (int)sqrt(CHUNK_RENDER_SIZE); x++) {
    //     for (int z = 0; z < (int)sqrt(CHUNK_RENDER_SIZE); z++) {
    //         Chunk rendered_chunk = {
    //             GenerateChunk(x, z),
    //             x,
    //             z
    //         };
    //         chunks[x * (int)sqrt(CHUNK_RENDER_SIZE) + z] = rendered_chunk;
    //     }
    // }

    DisableCursor();  
}

bool render_only_wire = false;

void Update( void ) {
    Vector3 cubePosition = { 2.0f, 0.0f, 0.0f };

    UpdateCamera(&camera, CAMERA_FREE);

    BeginDrawing();

        Color bg_color = { 135, 206, 235 };
        ClearBackground( bg_color );

        BeginMode3D( camera );

        // for (int i = 0; i < CHUNK_RENDER_SIZE; i++) {
        //     Chunk current_chunk = chunks[i];
        //     // for (int x = 0; x < CHUNK_WIDTH; x++) {
        //     //     for (int y = 0; y < CHUNK_HEIGHT; y++) {
        //     //         for (int z = 0; z < CHUNK_LENGTH; z++) {
        //     //             ChunkBlock current_block = current_chunk.chunk_block[x][z][y];
        //     //             if (current_block.block_type == GRASS_BLOCK) {
        //     //                 grass_block.x = (x*2) + (current_chunk.x_offset * CHUNK_WIDTH);
        //     //                 grass_block.y = y*2;
        //     //                 grass_block.z = z*2 + (current_chunk.z_offset * CHUNK_LENGTH);
        //     //                 RenderBlock(grass_block, camera);
        //     //             } else if (current_block.block_type == STONE_BLOCK) {
        //     //                 stone_block.x = (x*2) + (current_chunk.x_offset * CHUNK_WIDTH);
        //     //                 stone_block.y = y*2;
        //     //                 stone_block.z = z*2 + (current_chunk.z_offset * CHUNK_LENGTH);
        //     //                 RenderBlock(stone_block, camera);
        //     //             }
        //     //         }
        //     //     }
        //     // }
        // }


                for (int x = 0; x < CHUNK_WIDTH; x++) {
                    for (int z = 0; z < CHUNK_LENGTH; z++) {
                        for (int y = 0; y < CHUNK_HEIGHT; y++) {
                            ChunkBlock current_block = chunk_map[x][z][y];
                            if ( current_block.neighbor_count < 6 ) {
                                if (current_block.block_type == GRASS_BLOCK) {
                                    grass_block.x = x*2;
                                    grass_block.y = y*2;
                                    grass_block.z = z*2;
                                    RenderBlock(grass_block, camera);
                                } else if (current_block.block_type == STONE_BLOCK) {
                                    stone_block.x = x*2;
                                    stone_block.y = y*2;
                                    stone_block.z = z*2;
                                    RenderBlock(stone_block, camera);
                                }
                            }
                        }
                    }
                }

                for (int x = 0; x < CHUNK_WIDTH; x++) {
                    for (int z = 0; z < CHUNK_LENGTH; z++) {
                        for (int y = 0; y < CHUNK_HEIGHT; y++) {
                            ChunkBlock current_block = chunk_map2[x][z][y];
                            if ( current_block.neighbor_count < 6 ) {
                                if (current_block.block_type == GRASS_BLOCK) {
                                    grass_block.x = x*2 - 32;
                                    grass_block.y = y*2;
                                    grass_block.z = z*2;
                                    RenderBlock(grass_block, camera);
                                } else if (current_block.block_type == STONE_BLOCK) {
                                    stone_block.x = x*2 - 32;
                                    stone_block.y = y*2;
                                    stone_block.z = z*2;
                                    RenderBlock(stone_block, camera);
                                }
                            }
                        }
                    }
                }

                for (int x = 0; x < CHUNK_WIDTH; x++) {
                    for (int z = 0; z < CHUNK_LENGTH; z++) {
                        for (int y = 0; y < CHUNK_HEIGHT; y++) {
                            ChunkBlock current_block = chunk_map3[x][z][y];
                            if ( current_block.neighbor_count < 6 ) {
                                if (current_block.block_type == GRASS_BLOCK) {
                                    grass_block.x = x*2 ;
                                    grass_block.y = y*2;
                                    grass_block.z = z*2- 32;
                                    RenderBlock(grass_block, camera);
                                } else if (current_block.block_type == STONE_BLOCK) {
                                    stone_block.x = x*2;
                                    stone_block.y = y*2;
                                    stone_block.z = z*2 - 32;
                                    RenderBlock(stone_block, camera);
                                }
                            }
                        }
                    }
                }

                for (int x = 0; x < CHUNK_WIDTH; x++) {
                    for (int z = 0; z < CHUNK_LENGTH; z++) {
                        for (int y = 0; y < CHUNK_HEIGHT; y++) {
                            ChunkBlock current_block = chunk_map4[x][z][y];
                            if ( current_block.neighbor_count < 6 ) {
                                if (current_block.block_type == GRASS_BLOCK) {
                                    grass_block.x = x*2 - 32;
                                    grass_block.y = y*2;
                                    grass_block.z = z*2- 32;
                                    RenderBlock(grass_block, camera);
                                } else if (current_block.block_type == STONE_BLOCK) {
                                    stone_block.x = x*2- 32;
                                    stone_block.y = y*2;
                                    stone_block.z = z*2 - 32;
                                    RenderBlock(stone_block, camera);
                                }
                            }
                        }
                    }
                }


            ResetBlockCollision();

        EndMode3D();

        BeginMode2D(camera2d);

            // DrawTextureEx(crosshairTexture, (Vector2){ SCREEN_WIDTH / 2 - crosshairTexture.width/2, SCREEN_HEIGHT / 2 - crosshairTexture.height/2 + 5 }, 0.0f, 0.5f, WHITE);

            DrawRectangle(SCREEN_WIDTH/2 - 10, SCREEN_HEIGHT/2 - 10, 10, 10, RED);

        EndMode2D();

        DrawFPS(10, 10);

    EndDrawing();
}

void EndGame( void ) {
    CleanupChunk( chunk_map );
    CleanupChunk( chunk_map2 );
    // for (int i = 0; i < CHUNK_RENDER_SIZE; i++) {
    //     ChunkBlock*** chunk = chunks[i].chunk_block;
    //     for (int x = 0; x < CHUNK_WIDTH; x++) {
    //             for (int z = 0; z < CHUNK_LENGTH; z++) {
    //                 free(chunk[x][z]);
    //             }
    //             free(chunk[x]);
    //     }
    //     free(chunk);
    // }
    // free(chunks);
    // for (int i = 0; i < CHUNK_RENDER_SIZE; i++) {
    //     CleanupChunk(chunks[i].chunk_block);
    // }
}