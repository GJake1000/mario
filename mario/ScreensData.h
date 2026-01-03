#pragma once
#include <vector>
#include <utility>
#include <string>

constexpr int MAX_X = 79;
constexpr int MAX_Y = 24;

struct obsData {
	int x;
	int y;
	int width;
	int height;
};

struct DoorInfo {
	int x;
	int y;
	int leadsToRoom;
	char doorChar;
	int xLead;
	int yLead;
	std::vector<std::string> conditions; // e.g., "KEY", "NONE"
};

struct roomData {
	char map[MAX_Y + 1][MAX_X + 2]; 
	char initialMap[MAX_Y + 1][MAX_X + 2];
	bool isDark = false;
	bool isLastRoom = false;
	int startX1 = 1, startY1 = 15; // starting first player position
	int startX2 = 1, startY2 = 17; // starting second player position

	std::vector<DoorInfo> doors;
	std::vector<obsData> obstaclePositions; // positions of obstacles in the room
	std::vector<std::pair<int, int>> springPositions;   // positions of springs in the room
};