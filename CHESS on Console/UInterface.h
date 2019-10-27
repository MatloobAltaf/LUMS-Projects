#pragma once
#include "chess.h"
//Interface is developed with the help of www.codeproject.com/GameDevelopment
#define WHITE_SQUARE 0xDB
#define BLACK_SQUARE 0xFF
#define EMPTY_SQUARE 0x20

void createNextMessage(string msg);
void appendToNextMessage(string msg);
void printMessage(void);
void printLine(int iLine, int iColor1, int iColor2, Game& game);
void printCaptured(Game& game);
void printBoard(Game& game);
void clearScreen(void);
