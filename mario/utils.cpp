#include "utils.h"
#include <iostream>
#include <windows.h>
#include <cstdlib>


//=========================move cursor to (x,y) position=================================
void gotoxy(int x, int y) {
    std::cout.flush(); // Flush the output buffer to ensure all previous output is displayed
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//=========================hide cursor=================================
void hideCursor()
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = FALSE; // Set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

//=========================clear screen=================================
void cls()
{
    system("cls");
}

//=========================set text color=================================
void setTextColor(Color color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)color);
}