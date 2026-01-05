#include "Screen.h"
#include "Point.h" 
#include "utils.h"
#include "screenLoad.h"
#include <iostream>
#include <windows.h> 
#include <cstring>
#include <fstream>
#include <string>

// ========================= Get Obstacle Positions =========================
const std::vector<obsData>& Screen::getObstaclePositions(int roomNum) const {
	if (roomNum >= 0 && roomNum < loadedRooms.size())
		return loadedRooms[roomNum].obstaclePositions;
	static std::vector<obsData> empty; 
	return empty;
}

// ========================= Get Spring Positions =========================
const std::vector<std::pair<int, int>>& Screen::getSpringPositions(int roomNum) const {
	if (roomNum >= 0 && roomNum < loadedRooms.size())
		return loadedRooms[roomNum].springPositions;
	static std::vector<std::pair<int, int>> empty; return empty;
}

// ============================== Color Item ==============================
void Screen::colorItem(char item) const {
	if (!Point::isColorChose()) return;

	switch (item) {
	case TORCH: 
		setTextColor(Color::yellow); 
		break;
	case SWITCH:
	case OFF_SWITCH:		
	setTextColor(Color::green);
		break;
	case DOOR: 
	case '1': 
	case '2': 
	case '3': 
		setTextColor(Color::brown); 
		break;
	case RIDDLE: 
		setTextColor(Color::cyan); 
		break;
	case '&': 
		setTextColor(Color::green); 
		break;
	case '$': 
		setTextColor(Color::blue); 
		break;
	case BOMB: 
		setTextColor(Color::purple); 
		break;
	default: 
		setTextColor(Color::white); 
		break;
	}
}

// ========================= Constructor =================================
Screen::Screen() {
	screenLoad loader;
	loadedRooms = loader.loadScreens();
}

// ========================= Reset Rooms =================================
void Screen::resetRoom() {
	for (size_t i = 0; i < loadedRooms.size(); ++i) {
		resetRoom((int)i);
	}
}

void Screen::resetRoom(int roomNum) {
	if (roomNum < 0 || roomNum >= loadedRooms.size()) return;
	for (int j = 0; j <= MAX_Y; ++j) { 
		for (int k = 0; k <= MAX_X + 1; ++k) {
			loadedRooms[roomNum].map[j][k] = loadedRooms[roomNum].initialMap[j][k];
		}
	}
}

// ========================= Char At =================================
char Screen::charAt(const Point& p, int roomNum) const {
	return charAt(p.getX(), p.getY(), roomNum);
}

char Screen::charAt(int x, int y, int roomNum) const {
	if (roomNum >= 0 && roomNum < loadedRooms.size()) {
		if (x >= 0 && x <= MAX_X && y >= 0 && y <= MAX_Y) {
			return loadedRooms[roomNum].map[y][x];
		}
	}
	return ' ';
}

// ========================= Draw =================================
void Screen::draw(int roomNum) const {
	if (roomNum < 0 || roomNum >= loadedRooms.size()) return;


	const int legendY = loadedRooms[roomNum].legendY;
	setCurrentLegendY(legendY);

	// 1) Print legend in its real place (raw gotoxy, not LegendSafe)
	if (legendY >= 0 && legendY < MAX_Y) {   // need two lines: legendY and legendY+1
		gotoxy(0, legendY);
		std::cout << screenLoad::legend;
	}


	for (int i = 0; i <= MAX_Y; ++i) {
		gotoxyLegendSafe(0, i);

		const char* row = loadedRooms[roomNum].map[i];
		for (int j = 0; row[j] != '\0'; ++j) {
			char ch = row[j];
			colorItem(ch);
			std::cout << ch;
		}
	}
	std::cout << std::flush;
}

// ========================= Is Wall =================================
bool Screen::isWall(int x, int y, int roomNum) const {
	if (roomNum < 0 || roomNum >= loadedRooms.size()) return true;
	if (x < 0 || x > MAX_X || y < 0 || y > MAX_Y) return true;

	char ch = loadedRooms[roomNum].map[y][x];
	return (ch == WALL || ch == DOOR_D || ch == OBSTACLE);
}

// ========================= Set Char =================================
void Screen::setChar(int x, int y, int roomNum, char ch) {
	if (roomNum < 0 || roomNum >= loadedRooms.size()) return;

	if (x >= 0 && x <= MAX_X && y >= 0 && y <= MAX_Y) {
		loadedRooms[roomNum].map[y][x] = ch;
		gotoxyLegendSafe(x, y);
		colorItem(ch);
		std::cout << ch << std::flush;
	}
}

void Screen::setChar(int x, int y, int roomNum, char ch, Color chClr) {
	if (roomNum < 0 || roomNum >= loadedRooms.size()) return;

	if (x >= 0 && x <= MAX_X && y >= 0 && y <= MAX_Y) {
		loadedRooms[roomNum].map[y][x] = ch;
		gotoxyLegendSafe(x, y);
		if (Point::isColorChose()) setTextColor(chClr);
		std::cout << ch << std::flush;
		setTextColor(Color::white);
	}
}

// ========================= Set Dark =================================
const char Screen::EMPTY_ROW[] = "                                                                                ";

void Screen::setDark() const {
	for (int col = 0; col <= MAX_Y - 2; col++) {
		gotoxyLegendSafe(0, col);
		std::cout << EMPTY_ROW << std::flush;
	}
	gotoxyLegendSafe(20, 23);
}

// ========================= Get Initial Char =================================
char Screen::getInitialChar(int x, int y, int roomNum) const {
	if (roomNum >= 0 && roomNum < loadedRooms.size()) {
		if (x >= 0 && x <= MAX_X && y >= 0 && y <= MAX_Y) {
			return loadedRooms[roomNum].initialMap[y][x];
		}
	}
	return ' ';
}

// ========================= Search Item =================================
bool Screen::searchItem(int roomNum, char item) const {
	if (roomNum < 0 || roomNum >= loadedRooms.size()) return false;

	for (int row = 0; row <= MAX_Y; ++row) {
		const char* mapRow = loadedRooms[roomNum].map[row];
		for (int col = 0; col <= MAX_X; ++col) {
			if (mapRow[col] == item)
				return true;
		}
	}
	return false;
}

bool Screen::isDark(int roomNum) const {
	if (roomNum >= 0 && roomNum < loadedRooms.size())
		return loadedRooms[roomNum].isDark;
	return false;
}

// ========================= Get Target Room =================================
int Screen::getTargetRoom(int roomNum, int x, int y) const {
	if (roomNum < 0 || roomNum >= loadedRooms.size()) return -1;
	for (const auto& door : loadedRooms[roomNum].doors) {
		if (door.x == x && door.y == y) {
			return door.leadsToRoom;
		}
	}
	return -1;
}

const DoorInfo* Screen::getDoor(int roomNum, int x, int y) {
	if (roomNum < 0 || roomNum >= loadedRooms.size()) return nullptr;
	for (const auto& door : loadedRooms[roomNum].doors) {
		if (door.x == x && door.y == y) {
			return &door;
		}
	}
	return nullptr;
}

bool Screen::isLastRoom(int roomNum) {
	if (roomNum >= 0 && roomNum < loadedRooms.size())
		return loadedRooms[roomNum].isLastRoom;
	return false;
}

std::pair<int, int> Screen::getPlayerStartPos(int playerIdx) const
{
	if(loadedRooms.empty()) 
		return { 1,1 };
	if (playerIdx == 1)
		return { loadedRooms[0].startX1, loadedRooms[0].startY1 };
	else if (playerIdx == 2)
		return { loadedRooms[0].startX2, loadedRooms[0].startY2 };
	return std::pair<int, int>();
}

const std::vector<obsData>& Screen::getObstacleData(int roomNum) const {
	if (roomNum >= 0 && roomNum < loadedRooms.size())
		return loadedRooms[roomNum].obstaclePositions;
	static std::vector<obsData> empty;
	return empty;
}
