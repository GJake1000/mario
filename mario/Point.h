#pragma once
#include "Direction.h"
#include "utils.h"
#include "auxThing.h"
class Screen;

class Point {
	enum { MAX_X = 79, MAX_Y = 24 };
	static constexpr int NUM_KEYS = 6;

	int x, y;
	int diff_x = 0, diff_y = 0; // defualt for begin (STAY)
	char player;
	char keys[NUM_KEYS];
	Color color;
	int inventoryX, inventoryY;
	static bool colorChose;

public:
	Point(int x1, int y1, char p, const char(&my_keys)[NUM_KEYS + 1],
		Color clr, int myInventoryX, int myInventoryY = MAX_Y) {
		player = p;
		for (int i = 0; i < NUM_KEYS; i++) 
			keys[i] = my_keys[i];
		color = clr;
		inventoryX = myInventoryX;
		inventoryY = myInventoryY;
		x = x1;
		y = y1;

	}
	void draw();
	void draw(char p);
	void move(bool canMove);
	void handleKeyPressed(int key, Screen& screen, int roomNum);
	void setDirection(Direction dir);
	char itemToDispose(Screen& screen, int roomNum);
	bool drawToInventory(Screen& screen, int roomNum, char item);
	char checkInventory(Screen& screen, int roomNum) const;
	void dispose(Screen& screen, int roomNum);
	void setPosition(int newX, int newY);
	char getPlayerChar() const;
	int getX() const;
	int getY() const;
	int getNextX() const;
	int getNextY() const;
	static bool isColorChose() {
		return colorChose;
	}
	static void setColorChose(bool chose) {
		colorChose = chose;
	}
};
