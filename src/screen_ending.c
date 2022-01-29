/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Ending Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
const int threeStarMoves = 8;
const int twoStarMoves = 12;
const int circleSpacing = 20;

//----------------------------------------------------------------------------------
// Ending Screen Functions Definition
//----------------------------------------------------------------------------------

// Ending Screen Initialization logic
void InitEndingScreen(void)
{
    // TODO: Initialize ENDING screen variables here!
    framesCounter = 0;
    finishScreen = 0;
}

// Ending Screen Update logic
void UpdateEndingScreen(void)
{
    // TODO: Update ENDING screen variables here!

    // Press enter or tap to return to TITLE screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        finishScreen = 1;
        //PlaySound(fxCoin);
    }
}

// Ending Screen Draw logic
void DrawEndingScreen(void)
{
    // TODO: Draw ENDING screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLUE);
    DrawTextEx(font, "Puzzle Solved", (Vector2){ 20, 20 }, font.baseSize, 4, BLACK);
    const char * movesText = TextFormat("Moves: %i",score);
    DrawTextEx(fontSmall,movesText,(Vector2){25,100}, fontSmall.baseSize,2, BLACK);
    DrawTextEx(fontSmall,"Rating: ",(Vector2){25,150}, fontSmall.baseSize,2, BLACK);
    int circlesX = MeasureTextEx(fontSmall,"Rating: ",fontSmall.baseSize,2).x+35;
    int circlesY = 158;
    DrawCircle(circlesX, circlesY, fontSmall.baseSize/2, BLACK);
    if(score<=twoStarMoves){
        DrawCircle(circlesX+circleSpacing, circlesY, fontSmall.baseSize/2, BLACK);
    }else{
        DrawCircleLines(circlesX+circleSpacing, circlesY, fontSmall.baseSize/2, BLACK);
    }
    if(score<=threeStarMoves){
        DrawCircle(circlesX+circleSpacing*2,circlesY,fontSmall.baseSize/2,BLACK);
    }else{
        DrawCircleLines(circlesX+circleSpacing*2,circlesY,fontSmall.baseSize/2,BLACK);
    }
    char * instruction = "TAP to RETURN to TITLE SCREEN";
    Vector2 instructionSize = MeasureTextEx(fontSmall,instruction,fontSmall.baseSize,1);
    DrawTextEx(fontSmall, instruction, (Vector2){GetScreenWidth()/2-instructionSize.x/2,GetScreenHeight()/2-instructionSize.y/2}, fontSmall.baseSize,1, DARKBLUE);
}

// Ending Screen Unload logic
void UnloadEndingScreen(void)
{
    // TODO: Unload ENDING screen variables here!
}

// Ending Screen should finish?
int FinishEndingScreen(void)
{
    return finishScreen;
}
