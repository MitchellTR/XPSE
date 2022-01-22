/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
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
#include <string.h>
#include <stdlib.h>

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
char * word = "WORDS";
int wordSpacing = 100;
int wordSize = 0;
Vector2 * letterPositions;

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------
void DrawWord();
void setLetterPositions();

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    setLetterPositions();
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!

    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        finishScreen = 1;
        //PlaySound(fxCoin);
    }
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    // TODO: Draw GAMEPLAY screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BEIGE);
    //DrawTextEx(font, "GAMEPLAY SCREEN", (Vector2){ 20, 10 }, font.baseSize*3, 4, MAROON);
    //DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);
    DrawWord();
}

void DrawWord(){
  for(int i=0;i<wordSize;i++){
    char curLetter = word[i];
    DrawTextEx(fontLarge,&curLetter,letterPositions[i],fontLarge.baseSize,0,BLACK);
  }
}

void setLetterPositions(){
  wordSize = strlen(word);
  letterPositions = (Vector2 *) malloc(wordSize * sizeof(Vector2));
  int wordSpaceWidth = wordSpacing * (wordSize-1);
  int startingPoint = GetScreenWidth()/2 - wordSpaceWidth/2;

  for(int i=0;i<wordSize;i++){
    char curLetter = word[i];
    Vector2 letterSize = MeasureTextEx(fontLarge,&curLetter,fontLarge.baseSize,0);
    letterPositions[i].y=GetScreenHeight()/2-letterSize.y/2;
    //int startingPoint = GetScreenWidth()/2-(wordSize/2) * wordSpacing;
    letterPositions[i].x = startingPoint + wordSpacing * i - letterSize.x/2;
  }
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
    free(letterPositions);
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}
