#include "raylib.h"

#include "include/constants.h"
#include "include/game.h"

int main( void ) {
    InitWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Minecraft Clone - Rohit" );

    SetTargetFPS( 520 );
    
    Init();

    while ( !WindowShouldClose() ) {
        Update();
    }

    EndGame();

    CloseWindow();

    return 0;
}