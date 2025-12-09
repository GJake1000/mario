#include "Point.h"
#include "Screen.h"
#include <iostream>
#include <cctype>
class Screen;


//=========================draw point=================================
bool Point::colorChose = true;

void Point::draw() {
	draw(player);
}

void Point::draw(char p) {
	gotoxy(x, y);
	if (colorChose)
		setTextColor(color);
	else
		setTextColor(Color::white);
	std::cout << p << std::flush;
	setTextColor(Color::white);
}

//=========================move point=================================
void Point::move(bool canMove)
{
	if (canMove) { // move only if no wall
		x = (x + diff_x + MAX_X) % MAX_X;
		y = (y + diff_y + MAX_Y) % MAX_Y;
	}
}

void Point::setPosition(int newX, int newY) {
	x = newX;
	y = newY;
	diff_x = 0;
	diff_y = 0;
}

//=========================handle key pressed=================================
void Point::handleKeyPressed(int key, Screen& screen, int roomNum) {
	unsigned char hebrew = (unsigned char)key;
	char letter = key;
	gotoxy(0, 0);
	std::cout << (int)hebrew;
	switch (hebrew) { // handle hebrew letters
		// player 1
	case HEB_VAV   : letter = 'W'; break; // ו
	case HEB_ZAYIN : letter = 'X'; break; // ז
	case HEB_HET   : letter = 'D'; break; // ח
	case HEB_TET   : letter = 'A'; break; // ט'
	case HEB_GERESH: letter = 'S'; break; // י
	case HEB_CAF   : letter = 'E'; break; // כ
		// player 2
	case HEB_LAMED : letter = 'I'; break; // ל
	case HEB_MEM   : letter = 'M'; break; // מ
	case HEB_NUN   : letter = 'L'; break; // נ
	case HEB_SAMECH: letter = 'J'; break; // ס
	case HEB_AYIN  : letter = 'K'; break; // ע
	case HEB_PE    : letter = 'O'; break; // פ

		// other
	case HEB_YOD   : letter = 'H'; break; // י

	}

	// iterate through keys to find which one was pressed and set direction
	size_t index = 0;
	for (char k : keys) { // check which key was pressed and set direction accordingly
		if (std::toupper((unsigned char)letter) == std::toupper((unsigned char)k)) {
			if (index == DISPOSE_KEY)    // DISPOSE
				dispose(screen, roomNum);

			else setDirection((Direction)index);
			return;
		}
		index++;
	}
}

//=========================set direction=================================
void Point::setDirection(Direction dir) {

	switch (dir) {
	case Direction::UP:
		diff_x = 0;
		diff_y = -1;
		break;
	case Direction::RIGHT:
		diff_x = 1;
		diff_y = 0;
		break;
	case Direction::DOWN:
		diff_x = 0;
		diff_y = 1;
		break;
	case Direction::LEFT:
		diff_x = -1;
		diff_y = 0;
		break;
	case Direction::STAY:
		diff_x = 0;
		diff_y = 0;
		break;
	}
}

//=========================item to dispose=================================
char Point::itemToDispose(Screen& screen, int roomNum) {
	char invItem = screen.charAt(inventoryX, inventoryY, roomNum);
	for (int i = 0; i < Screen::NUM_OF_ROOMS; i++)            // remove item from all rooms' inventories
		screen.setChar(inventoryX, inventoryY, i, EMPTY_CELL);

	return invItem;
}

//=========================draw to inventory=================================
bool Point::drawToInventory(Screen& screen, int roomNum, char item) {
	if (checkInventory(screen, roomNum) == EMPTY_CELL || item == EMPTY_CELL) {
		for (int i = 0; i < Screen::NUM_OF_ROOMS; i++) {           // draw item in all rooms' inventories       
			screen.setChar(inventoryX, inventoryY, i, item);
		}
		return true;
	}
	return false;
}

//=========================check if in inventory=================================
char Point::checkInventory(Screen& screen, int roomNum) const {
	return screen.charAt(inventoryX, inventoryY, roomNum);
}

//=========================dispose=================================
void Point::dispose(Screen& screen, int roomNum) {
	char invItem = itemToDispose(screen, roomNum);
	if (invItem != EMPTY_CELL)
		if (screen.charAt(x, y, roomNum) == EMPTY_CELL)
			screen.setChar(x, y, roomNum, invItem); // place item from inventory to current position
	drawToInventory(screen, roomNum, ' ');

}

//=========================get something=================================
char Point::getPlayerChar() const {
	return player;
}
int Point::getX() const {
	return x;
}
int Point::getY() const {
	return y;
}
int Point::getNextX() const {
	return (x + diff_x + MAX_X) % MAX_X;
}
int Point::getNextY() const {
	return (y + diff_y + MAX_Y) % MAX_Y;
}