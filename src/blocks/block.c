#include <stdbool.h>
#include <stdlib.h>
#include "block.h"
#include "raylib.h"
#include <float.h>

Block CreateBlock( float x, float y, float z, char * texture_path, BlockType block_type ) {

    Vector3 cube_pos = { x, y, z };
    Color OPAQUE_BLACK = { 0, 0, 0, 100 };
    DrawCubeWires( cube_pos, 2.0f, 2.0f, 2.0f, OPAQUE_BLACK );


    static Texture2D texture = { 0 };
    static Material material = { 0 };

    Mesh cubeMesh = GenMeshCube(2.0f, 2.0f, 2.0f);
    Vector2 *texcoords = ( Vector2 * ) malloc( sizeof(Vector2) * cubeMesh.vertexCount );
    for (int i = 0; i < cubeMesh.vertexCount; i += 4)
    {
        texcoords[i] = (Vector2){0.0f, 0.0f};
        texcoords[i + 1] = (Vector2){1.0f, 0.0f};
        texcoords[i + 2] = (Vector2){1.0f, 1.0f};
        texcoords[i + 3] = (Vector2){0.0f, 1.0f};
    }

    cubeMesh.texcoords = texcoords;

    Model model = LoadModelFromMesh(cubeMesh);

    texture = LoadTexture(texture_path);
    material = LoadMaterialDefault();
    material.maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    free(texcoords);

    Block created_block = {
        x,
        y,
        z,
        model,
        block_type,
        false,
    };

    return created_block;
}


bool already_collided = false;

void ResetBlockCollision(void) {
    already_collided = false;
}

bool CheckCollisionRayBox(Ray ray, BoundingBox box) {
    float tmin = (box.min.x - ray.position.x) / ray.direction.x;
    float tmax = (box.max.x - ray.position.x) / ray.direction.x;

    if (tmin > tmax) {
        float temp = tmin;
        tmin = tmax;
        tmax = temp;
    }

    float tymin = (box.min.y - ray.position.y) / ray.direction.y;
    float tymax = (box.max.y - ray.position.y) / ray.direction.y;

    if (tymin > tymax) {
        float temp = tymin;
        tymin = tymax;
        tymax = temp;
    }

    if ((tmin > tymax) || (tymin > tmax)) {
        return false;
    }

    if (tymin > tmin) {
        tmin = tymin;
    }

    if (tymax < tmax) {
        tmax = tymax;
    }

    float tzmin = (box.min.z - ray.position.z) / ray.direction.z;
    float tzmax = (box.max.z - ray.position.z) / ray.direction.z;

    if (tzmin > tzmax) {
        float temp = tzmin;
        tzmin = tzmax;
        tzmax = temp;
    }

    if ((tmin > tzmax) || (tzmin > tmax)) {
        return false;
    }

    return true;
}

void RenderBlock(Block block, Camera camera) {
    Vector3 block_position = { block.x, block.y, block.z };
    // DrawCubeWires(block_position, 2.0f, 2.0f, 2.0f, BLACK);

    Vector2 screenCenter = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
    Ray ray = GetMouseRay(screenCenter, camera);

    bool hit = false;
    if (!already_collided && CheckCollisionRayBox(ray, (BoundingBox){(Vector3){block.x - 1, block.y - 1, block.z - 1}, (Vector3){block.x + 1, block.y + 1, block.z + 1}})) {
        hit = true;
        already_collided = true;
    }

    if (hit) {
        DrawCube(block_position, 2.0f, 2.0f, 2.0f, Fade(WHITE, 0.5f));
    } else {
        DrawModel(block.model, block_position, 1.0f, WHITE);
    }
}