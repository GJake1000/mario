#pragma once
#include "Screen.h"
#include "utils.h"


class Obstacle {
	int x, y; // position of the right up corner of obstacle
	int width, height; // dimensions of the obstacle
	int roomNum;
	Color color;
public:
	Obstacle(int x1, int y1, int w, int h, int rN, Color c) : x(x1), y(y1), width(w), height(h), roomNum(rN), color(c) {}
	void draw(Screen& screen) const;
	void erase(Screen& screen) const;
	bool tryMove(int dx, int dy, Screen& screen);	
	bool loc(int cx, int cy, int curRoom) const;
	int getRoom() const {return roomNum; };
};

