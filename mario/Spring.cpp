#include "Spring.h"


bool Spring::contains(int px, int py, int room) const
{
	if (room != roomNum)
		return false;

	if (!isVertical) //horizontal
		return (py == y && px >= x && px < x + length);	//checks if this is at least part of the spring

	else //vertical
		return (px == x && py >= y && py < y + length); //checks if this is at least part of the spring
}

bool Spring::getTowardWallDir(const Screen& screen, int roomN, int& dx, int& dy) const {
	dx = 0; dy = 0;

	if (!isVertical) { // horizontal
		if (x - 1 >= 0 && screen.getInitialChar(x - 1, y, roomN) == 'W') {
			dx = -1; 
			return true; 
		}
		if (x + length <= Screen::MAX_X && screen.getInitialChar(x + length, y, roomN) == 'W') { 
			dx = 1; 
			return true; 
		}
	}
	else { // vertical
		if (y - 1 >= 0 && screen.getInitialChar(x, y - 1, roomN) == 'W') { 
			dy = -1; 
			return true; 
		}
		if (y + length <= Screen::MAX_Y && screen.getInitialChar(x, y + length, roomN) == 'W') { 
			dy = 1; 
			return true; 
		}
	}
	return false; //no wall found adjacent to spring 
}