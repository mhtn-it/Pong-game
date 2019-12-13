#include "Header.h"

void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
int wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.X;
}
int wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.Y;
}
void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0,0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}
void textcolor(int color)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, color);
}
void colorString(int x, int y, char* a, int color)
{
	gotoxy(x, y);
	textcolor(color);
	puts(a);
	textcolor(7);
}
void Nocursortype()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
void drawRectangle(int x, int y, int height, int width, int color)
{
	textcolor(color);
	for (int i = 0; i <= height; i++) 
	{
		gotoxy(x, y + i);
		for (int j = 0; j <= width; j++) 
		{
			if ((wherey() == y || wherey() == y + height)) 
			{
				cout << "\xB2";
			}
			else if ((wherex() == x || wherex() == x + width)) 
			{
				cout << "\xB2";
			}
			else 
			{
				cout << " ";
			}
		}
	}
}
void drawRectangle1(int x, int y, int height, int width, int color)
{
	textcolor(color);
	for (int i = 0; i <= height; i++) 
	{
		gotoxy(x, y + i);
		for (int j = 0; j <= width; j++) 
		{
			if ((wherey() == y || wherey() == y + height)) 
			{
				if (wherey() == y) {
					if (wherex() == x) cout << "\xC9";
					else if (wherex() == x + width) cout << "\xBB";
					else cout << "\xCD";
				}
				else if (wherey() == y + height) 
				{
					if (wherex() == x) cout << "\xC8";
					else if (wherex() == x + width) cout << "\xBC";
					else cout << "\xCD";
				}
			}
			else if ((wherex() == x || wherex() == x + width)) 
			{
				cout << "\xBA";
			}
			else 
			{
				cout << " ";
			}
		}
	}
}