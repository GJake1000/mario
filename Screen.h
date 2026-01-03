#pragma once
#include "ScreensData.h"
#include "auxThing.h"
#include "utils.h"
#include "screenLoad.h"
#include <vector>


class Point;

class Screen {
	std::vector<roomData> loadedRooms;
public:
	Screen();
	
	static constexpr int MAX_X = ::MAX_X;
	static constexpr int MAX_Y = ::MAX_Y;
	static constexpr int NUM_OF_ROOMS = 4; //2 rooms + final end room
	

	const std::vector<obsData>& getObstaclePositions(int roomNum) const;
	const std::vector<std::pair<int, int>>& getSpringPositions(int roomNum) const;

	void colorItem(char item) const;
	void resetRoom();
	void resetRoom(int roomNum);
	//getting
	char charAt(const Point& p, int roomNum) const;
	char charAt(int x, int y, int roomNum) const;
	bool isWall(int x, int y, int roomNum) const;
	char getInitialChar(int x, int y, int roomNum) const;
	bool searchItem(int roomNum, char item) const;

	//files
	bool isDark(int roomNum) const;
	int getTargetRoom(int roomNum, int x, int y) const;
	const DoorInfo* getDoor(int roomNum, int x, int y);
	bool isLastRoom(int roomNum);
	std::pair<int, int> getPlayerStartPos(int playerIdx) const;
	const std::vector<obsData>& getObstacleData(int roomNum) const;

	//drawing
	void draw(int roomNum) const;
	void setChar(int x, int y, int roomNum, char ch);
	void setChar(int x, int y, int roomNum, char ch, Color chClr);
	void setDark() const;

	static const char EMPTY_ROW[];
};