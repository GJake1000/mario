#include "Obstacle.h"
//===============================draw===============================
void Obstacle::draw(Screen& screen) const {
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			screen.setChar(x + i, y + j, roomNum, OBSTACLE);
		}
	}
}

//===============================erase===============================
void Obstacle::erase(Screen& screen) const {
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			screen.setChar(x + i, y + j, roomNum, EMPTY_CELL);
		}
	}
}

//========================check if it can move========================
bool Obstacle::tryMove(int dx, int dy, Screen& screen) {
	// check if the obstacle can move by (dx, dy) without hitting walls
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			int newX = x + i + dx;
			int newY = y + j + dy;
			if (screen.charAt(newX, newY, roomNum) != EMPTY_CELL && !loc(newX, newY, roomNum)) {
				return false;
			}
		}
	}
	erase(screen);
	x += dx;
	y += dy;
	draw(screen);
	return true;
}

//========================check if location is inside obstacle========================
bool Obstacle::loc(int cx, int cy, int curRoom) const {
	if (curRoom != roomNum)
		return false;
	return (cx >= x && cx < x + width && cy >= y && cy < y + height);
}
