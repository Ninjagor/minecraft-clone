#include <stdbool.h>
#include <stdlib.h>
#include "block.h"
#include "stone_block.h"
#include "raylib.h"

Block stone_block;

Block LoadStoneBlockModel( float x, float y, float z ) {

    stone_block = CreateBlock(x, y, z, "/Users/rohit/rohit-project-work/minecraft-clone/src/images/stone_block.png", STONE_BLOCK);

    return stone_block;
}