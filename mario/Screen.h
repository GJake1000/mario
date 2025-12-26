#pragma once
#include "auxThing.h"
#include "utils.h"


class Point;

class Screen {
public:
	static constexpr int MAX_X = 79;
	static constexpr int MAX_Y = 24;
	static constexpr int NUM_OF_ROOMS = 4; //2 rooms + final end room
	static const char EMPTY_ROW[];
private:
	char initialRooms[NUM_OF_ROOMS][MAX_Y + 1][MAX_X + 2]; // +1 for null terminator
	void loadScreens(const char* fileName);
	char rooms[NUM_OF_ROOMS][MAX_Y + 1][MAX_X + 2];
	
public:
	void colorItem(char item) const;
	Screen();
	void resetRoom();
	void resetRoom(int roomNum);
	char charAt(const Point& p, int roomNum) const;
	char charAt(int x, int y, int roomNum) const;
	void draw(int roomNum) const;
	bool isWall(int x, int y, int roomNum) const;
	void setChar(int x, int y, int roomNum, char ch);
	void setChar(int x, int y, int roomNum, char ch, Color chClr);
	void setDark() const;
	void helpLockPlayers() const;
	char getInitialChar(int x, int y, int roomNum) const;
	bool searchItem(int roomNum, char item) const;
};