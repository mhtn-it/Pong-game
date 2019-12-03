#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
using namespace std;

void resizeConsole(int width, int height);
void gotoxy(int x, int y);
int wherex();
int wherey();
void clrscr();
void textcolor(int color);
void colorString(int x, int y, char *a, int color);
void Nocursortype();
void drawRectangle(int x, int y, int height, int width, int color);
void drawRectangle1(int x, int y, int length, int width, int color);
