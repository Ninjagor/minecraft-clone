#include <stdbool.h>
#include <stdlib.h>
#include "block.h"
#include "raylib.h"
#include "grass_block.h"

Block grass_block;

Block LoadGrassBlockModel( float x, float y, float z ) {

    grass_block = CreateBlock(x, y, z, "/Users/rohit/rohit-project-work/minecraft-clone/src/images/grass_block.png", GRASS_BLOCK);

    return grass_block;
}