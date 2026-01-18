#include "Point.h"

#include <iostream>
#include <cctype>

#include "Screen.h"
#include "game_manager.h"


class Screen;

void Point::setKeys(const std::string& my_keys) {
	for (size_t i = 0; i < NUM_KEYS && i < my_keys.length(); i++)
		keys[i] = my_keys[i];
}

//=========================draw point=================================
bool Point::colorChose = true;

void Point::draw() const {
	draw(player);
}

void Point::draw(char p) const  {
	gotoxyLegendSafe(x, y);
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
	// iterate through keys to find which one was pressed and set direction
	size_t index = 0;
	for (char k : keys) { // check which key was pressed and set direction accordingly
		if (std::toupper((unsigned char)key) == std::toupper((unsigned char)k)) {
			if (index == DISPOSE_KEY){    // DISPOSE
				char disposed = dispose(screen, roomNum);
				if (disposed == BOMB && gm != nullptr) 
					gm->setBombTimer(x, y, roomNum);
				
				if (gm != nullptr)
					gm->eraseOutput();
			}
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
char Point::itemToDispose(Screen&, int)
{
	char tmp = heldItem;
	heldItem = EMPTY_CELL;
	return tmp;
}

//=========================draw to inventory=================================
bool Point::drawToInventory(Screen&, int, char item)
{
	// allow clearing
	if (item == EMPTY_CELL) {
		heldItem = EMPTY_CELL;
		return true;
	}

	// already holding something
	if (heldItem != EMPTY_CELL)
		return false;

	// keep your existing “must be moving” rule if you had it
	if (diff_x == 0 && diff_y == 0)
		return false;

	heldItem = item;
	return true;
}

//=========================check if in inventory=================================
char Point::checkInventory(const Screen& screen, int) const {
	return heldItem;
}

void Point::resetInventory(Screen&)
{
	heldItem = EMPTY_CELL;
}

//=========================dispose=================================
char Point::dispose(Screen& screen, int roomNum)
{
	char item = itemToDispose(screen, roomNum);
	if (item != EMPTY_CELL) {
		// drop at current position only if empty (or your rule)
		if (screen.charAt(x, y, roomNum) == EMPTY_CELL)
			screen.setChar(x, y, roomNum, item);
		else {
			// if you have different dropping rules, apply them here
		}
	}
	return item;
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

//=========================spring thing=================================

void Point::startSpringEffect(int dx, int dy, int speed)
{
	beingLaunched = true;
	launchDirX = dx;
	launchDirY = dy;
	launchSpeed = speed;
	launchCyclesLeft = speed * speed;
}

void Point::tickSpringEffect()
{
	if (!beingLaunched)
		return;

	launchCyclesLeft--;

	if (launchCyclesLeft <= 0) {
		beingLaunched = false;
		launchDirX = launchDirY = 0;
		launchSpeed = 0;
		launchCyclesLeft = 0;
	}
}