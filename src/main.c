#include "raylib.h"

#include "include/constants.h"
#include "include/game.h"

int main( void ) {
    InitWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Minecraft Clone - Rohit" );

    SetTargetFPS( 120 );
    
    Init();

    while ( !WindowShouldClose() ) {
        Update();
    }

    CloseWindow();

    return 0;
}