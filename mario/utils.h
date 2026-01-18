#pragma once

//int g_currentLegendY;

void gotoxy(int x, int y);
void hideCursor();
void cls();
//void printOutput(const char* output);
//void eraseOutput();


enum class Color {
    black = 0,
    blue = 1,
    green = 2,
    cyan = 3,
    red = 4,
    purple = 5,
    brown = 6,
    gray = 8,
    yellow = 12,
    white = 15
};

void setTextColor(Color color);
void ErrorEncountered(int errNum);


extern int g_currentLegendY;

void setCurrentLegendY(int legendY);
void gotoxyLegendSafe(int x, int y);
int getLegendY();


/*
class Legend {
    int g_currentLegendY = -1;
    
public:
    void setCurrentLegendY(int legendY);
    void gotoxyLegendSafe(int x, int y);
    int getLegendY();
};
*/
