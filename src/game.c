#include "raylib.h"
#include "include/constants.h"
#include "include/game.h"
#include "blocks/block.h"
#include "world/world.h"
#include "blocks/grass_block.h"
#include "blocks/stone_block.h"
#include <stdio.h>

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

BlockType*** chunk_map;

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

    chunk_map = GenerateChunk();

    // for (int x = 0; x < 16; x++) {
    //     for (int z = 0; z < 16; z++) {
    //         for (int y = 0; y < 32; y++) {
    //             printf("%d ", chunk_map[x][z][y]);
    //         }
    //         printf("\n");
    //     }
    //     printf("\n");
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

            // GenerateChunk(camera, grass_block);

                for (int x = 0; x < 16; x++) {
                    for (int z = 0; z < 16; z++) {
                        for (int y = 0; y < 32; y++) {
                            // printf("%d ", chunk_map[x][z][y]);
                            if (chunk_map[x][z][y] == GRASS_BLOCK) {
                                grass_block.x = x*2;
                                grass_block.y = y*2;
                                grass_block.z = z*2;
                                RenderBlock(grass_block, camera);
                            } else if (chunk_map[x][z][y] == STONE_BLOCK) {
                                stone_block.x = x*2;
                                stone_block.y = y*2;
                                stone_block.z = z*2;
                                RenderBlock(stone_block, camera);
                            }
                        }
                        // printf("\n");
                    }
                    // printf("\n");
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