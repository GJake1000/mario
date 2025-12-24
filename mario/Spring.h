#pragma once
#include "auxThing.h"
#include "Screen.h"


class Spring {
	int x, y;					//location of a spring character
	int length;
	int roomNum;
	bool isVertical; // isVertical == 1: the spring is vertical. isVertical == 0: the spring is horizontal

public:
	Spring(int x, int y, int len, int roomN, bool isVer) : x(x), y(y), length(len), roomNum(roomN), isVertical(isVer) {}
	
	bool contains(int px, int py, int room) const;

	bool getTowardWallDir(const Screen& screen, int roomN, int& dx, int& dy) const;
};