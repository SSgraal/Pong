#include <iostream>
#include <raylib.h>

//PONG
//Cream o fereastra
//Cream cei doi jucatori(doua linii verticale)
//Facem ca cele doua linii(jucatorii) sa fie controlate din tastele w,s respectiv sageata sus, sageata jos
//Cream un cerc care va fi lansat din mijlocul ferestrei(sa alterneze de la stanga la dreapta)
//Cream un functie care detecteaza coliziunea dintre cerc si jucatori sau cerc si pereti sau jucator si pereti
//Cream un sistem de scor
//Poate un meniu

using namespace std;

int main () {

    float windowWidth = 1220;
    float windowHeight = 800;

    float playerWidth = 20;
    float playerHeight = 100;
    float playerSpeed = 12;

    int score1 = 0;
    int score2 = 0; 

    InitWindow(windowWidth, windowHeight, "My window");

    //player1 and player2 positions
    Vector2 player1Position = {(float)  windowWidth/100.0, (float) windowHeight/2.0};
    Vector2 player2Position = {(float) 97.0 * windowWidth/100.0, (float) windowHeight/2.0};

    //ball coordinates
    Vector2 ballPosition = {windowWidth/2.0, windowHeight/2.0};
    //ball speed
    Vector2 ballSpeed = {8.5, 7.0};

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {

        //player1 movement       
        if(IsKeyDown(KEY_W))
            player1Position.y -= playerSpeed;
        else if(IsKeyDown(KEY_S))
            player1Position.y += playerSpeed;

        //player2 movement
        if(IsKeyDown(KEY_UP))
            player2Position.y -= playerSpeed;
        else if(IsKeyDown(KEY_DOWN))
            player2Position.y += playerSpeed;

        //ball movement
        ballPosition.x -= ballSpeed.x;
        ballPosition.y += ballSpeed.y;

        //ball collision detection
        if(CheckCollisionCircleRec(Vector2{ballPosition.x, ballPosition.y}, 25, Rectangle{player1Position.x, player1Position.y, playerWidth, playerHeight}))
            ballSpeed.x *= -1.0;
        else if(CheckCollisionCircleRec(Vector2{ballPosition.x, ballPosition.y}, 25, Rectangle{player2Position.x, player2Position.y, playerWidth, playerHeight}))
            ballSpeed.x *= -1.0;

        if((ballPosition.y + 20 >= windowHeight) || (ballPosition.y-20 <= 0))
            ballSpeed.y *= -1.0;

        //score system
        if(ballPosition.x + 20 >= windowWidth)
        {
            score2 ++;
            ballPosition.x = windowWidth/2.0;
            ballPosition.y = windowHeight/2.0;
            ballSpeed.x *= -1.0 ;
            ballSpeed.y *= -1.0 ;
        }
        else if(ballPosition.x - 20 <= 0)
        {
            score1 ++;
            ballPosition.x = windowWidth/2.0;
            ballPosition.y = windowHeight/2.0;
            ballSpeed.x *= -1.0;
            ballSpeed.y *= -1.0;
        }

        BeginDrawing();

        //changing the background color
        ClearBackground(BLUE);


        //drawing the players
        DrawRectangle(player1Position.x, player1Position.y, playerWidth, playerHeight, WHITE);//player1
        DrawRectangle(player2Position.x, player2Position.y, playerWidth, playerHeight, WHITE);//player2

        DrawLine(windowWidth/2.0, 0, windowWidth/2.0, windowHeight, WHITE);
        DrawText(TextFormat("%i", score2), windowWidth/4-20, 20, 80, WHITE);
         DrawText(TextFormat("%i", score1), 3 * windowWidth/4-20, 20, 80, WHITE);
        //drawing the ball
        DrawCircle(ballPosition.x, ballPosition.y, 20, WHITE);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}