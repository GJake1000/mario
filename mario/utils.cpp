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

//=========================Error handling=================================

void ErrorEncountered(int errNum)
{
    cls();

    const char* errorMessages[5];

    errorMessages[0] = "Unknown error occurred.";
    errorMessages[1] = "maps are unclear!";
    errorMessages[2] = "Riddle file empty!.";

    std::cout << "Error: " << errorMessages[errNum] << '\n';

    if (errNum <= 1) //critical errors
    {
        std::cout << "This error is critical, The program will now exit." << '\n';
        std::cout << "Exiting program..." << '\n';
        exit(1);
    }
    //else load menu (is after function call)
}

static int g_currentLegendY = -1;

void setCurrentLegendY(int legendY)
{
    g_currentLegendY = legendY;
}

void gotoxyLegendSafe(int x, int y)
{
    if (g_currentLegendY >= 0) {
        if (y >= g_currentLegendY)   // shift everything at/under legend
            y += 2;
    }
    gotoxy(x, y);
}
