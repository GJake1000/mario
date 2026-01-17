#include "Obstacle.h"
#include "Point.h"

//===============================draw===============================
void Obstacle::draw(Screen& screen) const {
	if (Point::isColorChose()) 
		setTextColor(color);
	
	for (const auto& c : cords) {
		screen.setChar(c.x, c.y, roomNum, OBSTACLE, color);
	}
	setTextColor(Color::white);
}

//===============================does the room contain the obstacle===============================
bool Obstacle::contains(const Coord& crd) const {
	
	for (const auto& c : cords)
		if (c == crd) return true;

	return false;
}

//===============================erase===============================
void Obstacle::erase(Screen& screen) const {
	for (const auto& c : cords) {
		screen.setChar(c.x, c.y, roomNum, EMPTY_CELL);
	}
}

//========================check if it can move========================
bool Obstacle::tryMove(int dx, int dy, Screen& screen) {
	// check if the obstacle can move by (dx, dy) without hitting walls

	for (const auto& c : cords) {
		int newX = c.x + dx;
		int newY = c.y + dy;
		
		char dest = screen.charAt(newX, newY, roomNum);	
		if (dest != EMPTY_CELL) {
			if (!contains(Coord(newX, newY))) {//if the new position is not part of the obstacle itself
				return false;
			}	
		}	
		
		
	}	
	erase(screen);

	for (auto& c : cords) {
		c.x += dx;
		c.y += dy;	
	}
	draw(screen);
	return true;
}
/*
//========================check if location is inside obstacle========================
bool Obstacle::loc(int cx, int cy, int curRoom) const {
	if (curRoom != roomNum)
		return false;
	return (cx >= x && cx < x + width && cy >= y && cy < y + height);
}

*/