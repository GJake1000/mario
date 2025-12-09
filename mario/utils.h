#pragma once

void gotoxy(int x, int y);
void hideCursor();
void cls();
//void printOutput(const char* output);
//void eraseOutput();


enum class Color {
    blue = 1,
    green = 2,
    cyan = 3,
    red = 4,
    brown = 6,
    gray = 8,
    yellow = 12,
    white = 15
};

void setTextColor(Color color);