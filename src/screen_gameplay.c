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
char word[] = "WORD";
char password[] = "WORD";
char scrambledWord[] = "WORD";
char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int wordSpacing = 125;
int verticalLetterSpacing = 100;
int wordSize = 0;
Vector2 * letterPositions;
int letterButtonYOffset = 85;
int easyDistance = 1;
char * easyWords[] = {
  "BALL","ABLE","CARD","DOOR", "EDGE", "FIRE",
  "GOLD", "HIDE", "IDEA", "JOKE", "KING", "LIFE",
  "MARK", "NAME", "OPEN", "PASS", "QUIP", "ROCK",
  "STAR", "TEST", "USER", "VIEW", "WALL", "EXIT",
  "YEAR", "TIME"
};
int easyWordsTotal = sizeof easyWords / sizeof easyWords[0];
int currentRangeMax = 0;
int easyRangeMax = 2;
int rangeIndexes[] = {-1,-1,-1,-1,-1,-1};
int rangePositions[] = {-1,-1,-1,-1,-1,-1};
int verticalLetterPositions[] = {0,0,0,0,0,0,0,0,0,0,0};

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------
void DrawWord();
void setLetterPositions();
int ClickCollides(int minX, int minY, int maxX, int maxY);
void IncrementLetter(int index);
void DecrementLetter(int index);
int GetLetterIndex(char letter);
int PasswordSolved();
void ScrambleWord();
void SetVerticalLetterPositions();

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;

    //set everything easy for now
    currentRangeMax = easyRangeMax;

    setLetterPositions();
    SetVerticalLetterPositions();
    ScrambleWord();
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!

    // Press enter or tap to change to ENDING screen
    if (IsMouseButtonReleased(0))// removed: IsGestureDetected(GESTURE_TAP) ||
    {
      for(int i=0;i<wordSize;i++){
        if(ClickCollides(
          letterPositions[i].x-fontLarge.baseSize/5,
          letterPositions[i].y-letterButtonYOffset-10-fontLarge.baseSize/5,
          letterPositions[i].x+fontLarge.baseSize/5,
          letterPositions[i].y-letterButtonYOffset-10+fontLarge.baseSize/5
        ) == 1 && rangePositions[i]<currentRangeMax){
          IncrementLetter(i);
          rangePositions[i]++;
          if(PasswordSolved()==1){
            finishScreen=1;
          }
        }else if(ClickCollides(
          letterPositions[i].x-fontLarge.baseSize/5,
          letterPositions[i].y+letterButtonYOffset-5-fontLarge.baseSize/5,
          letterPositions[i].x+fontLarge.baseSize/5,
          letterPositions[i].y+letterButtonYOffset-5+fontLarge.baseSize/5
        ) == 1 && rangePositions[i]>0){
          DecrementLetter(i);
          rangePositions[i]--;
          if(PasswordSolved()==1){
            finishScreen=1;
          }
        }
      }
    }
}

int PasswordSolved(){
  int solved = 1;
  for(int i=0;i<wordSize;i++){
    if(word[i]!=password[i]){
      return 0;
    }
  }
  if(solved==1){
    return 1;
  }
  return -1;
}

void ScrambleWord(){
  strcpy(password,easyWords[GetRandomValue(0,easyWordsTotal-1)]);
  //strcpy(password,"XYZY");
  strcpy(word,password);

  //For each letter, decide random position in range up to
  //range limit. Adjust range for edge cases. Move to random letter
  //in range, repeat until random letter is not the correct letter.
  for(int i=0;i<wordSize;i++){
    rangeIndexes[i]=GetRandomValue(0,currentRangeMax);
    int alphaIndex = GetLetterIndex(word[i]);
    while(alphaIndex<rangeIndexes[i]){
      rangeIndexes[i]--;
    }
    while(alphaIndex+(currentRangeMax-rangeIndexes[i])>25){
      rangeIndexes[i]++;
    }
    while(word[i]==password[i]){
        rangePositions[i] = GetRandomValue(0,currentRangeMax);
        int rangeDifference = rangeIndexes[i] - rangePositions[i];
        word[i]=alphabet[alphaIndex-rangeDifference];
    }
  }
  strcpy(scrambledWord,word);
}

void IncrementLetter(int index){
  if(word[index]=='Z'){
    word[index]='A';
  }else{
    word[index]=alphabet[GetLetterIndex(word[index])+1];
  }
}

void DecrementLetter(int index){
  if(word[index]=='A'){
    word[index]='Z';
  }else{
    word[index]=alphabet[GetLetterIndex(word[index])-1];
  }
}

int GetLetterIndex(char letter){
  for(int i = 0;i<26;i++){
    if(alphabet[i]==letter){
      return i;
    }
  }
  return -1;
}

int ClickCollides(int minX, int minY, int maxX, int maxY){
  Vector2 clickPosition = GetMousePosition();
  if(clickPosition.x>minX){
    if(clickPosition.x<maxX){
      if(clickPosition.y>minY){
        if(clickPosition.y<maxY){
          return 1;
        }
      }
    }
  }
  return 0;
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    // TODO: Draw GAMEPLAY screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), DARKGRAY);
    DrawWord();
    DrawTextEx(fontSmall, password, (Vector2){5, 5}, 16, 2, WHITE);
}

void DrawWord(){
  for(int i=0;i<wordSize;i++){
    char curLetter = word[i];
    Vector2 letterSize = MeasureTextEx(fontLarge,&curLetter,fontLarge.baseSize,0);
    DrawCircle(letterPositions[i].x, letterPositions[i].y-5, fontLarge.baseSize/2, BLACK);
    DrawTextEx(fontLarge,&curLetter,(Vector2){letterPositions[i].x-letterSize.x/2, letterPositions[i].y-letterSize.y/2},fontLarge.baseSize,0,WHITE);
    if(rangePositions[i]<currentRangeMax){
      DrawTriangle(
        (Vector2){letterPositions[i].x,letterPositions[i].y-letterButtonYOffset-10-fontLarge.baseSize/5},
        (Vector2){letterPositions[i].x-fontLarge.baseSize/5,letterPositions[i].y-letterButtonYOffset-10+fontLarge.baseSize/5},
        (Vector2){letterPositions[i].x+fontLarge.baseSize/5,letterPositions[i].y-letterButtonYOffset-10+fontLarge.baseSize/5}, WHITE);
    }
    if(rangePositions[i]>0){
      DrawTriangle(
        (Vector2){letterPositions[i].x,letterPositions[i].y+letterButtonYOffset-5+fontLarge.baseSize/5},
        (Vector2){letterPositions[i].x+fontLarge.baseSize/5,letterPositions[i].y+letterButtonYOffset-5-fontLarge.baseSize/5},
        (Vector2){letterPositions[i].x-fontLarge.baseSize/5,letterPositions[i].y+letterButtonYOffset-5-fontLarge.baseSize/5},
        WHITE);
    }
    //for(int j=rangePositions[i]-1;j>=0;j--){
      //char jLetter = alphabet[0];
      //int jYPosition = verticalLetterPositions[4];
      //Vector2 jLetterSize = MeasureTextEx(font,&jLetter,font.baseSize,0);
      //DrawTextEx(font,&jLetter,(Vector2){letterPositions[i].x-jLetterSize.x/2,jYPosition-jLetterSize.y/2},font.baseSize,0,WHITE);
    //}
    char jLetter[2] = "z";
    jLetter[0] = alphabet[GetLetterIndex(word[i])-1];
    int jYPosition = verticalLetterPositions[4];
    Vector2 jLetterSize = MeasureTextEx(font,&jLetter[0],font.baseSize,0);
    DrawTextEx(font,&jLetter[0],(Vector2){letterPositions[i].x-jLetterSize.x/2,jYPosition-jLetterSize.y/2},font.baseSize,0,WHITE);
  }
}

void setLetterPositions(){
  wordSize = strlen(word);
  letterPositions = (Vector2 *) malloc(wordSize * sizeof(Vector2));
  int wordSpaceWidth = wordSpacing * (wordSize-1);
  int startingPoint = GetScreenWidth()/2 - wordSpaceWidth/2;
  for(int i=0;i<wordSize;i++){
    letterPositions[i].y=GetScreenHeight()/2;
    letterPositions[i].x = startingPoint + wordSpacing * i;
  }
}

void SetVerticalLetterPositions(){
  verticalLetterPositions[5]=letterPositions[0].y;
  for(int i=6;i<11;i++){
    verticalLetterPositions[i]=verticalLetterPositions[5]+((i-5)*verticalLetterSpacing);
  }
  for(int i=4;i>=0;i--){
    verticalLetterPositions[i]=verticalLetterPositions[5]-((5-i)*verticalLetterSpacing);
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
