#include "screenLoad.h"
#include "auxThing.h"
#include "ScreensData.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <filesystem>

void resetRoom(roomData& room) {
	for (int i = 0; i <= MAX_Y; ++i) {
		std::fill(&room.map[i][0], &room.map[i][0] + MAX_X + 1, ' '); 
		room.map[i][MAX_X + 1] = '\0';
		std::fill(&room.initialMap[i][0], &room.initialMap[i][0] + MAX_X + 1, ' ');
		room.initialMap[i][MAX_X + 1] = '\0';
	}
}

bool isLastRoom(const std::string line, roomData& room) {
	if (line.find("LAST") != std::string::npos) {
		room.isLastRoom = true;
		return true;
	}
	return false;
}

bool isDark(const std::string& line, roomData& room) {
	if (line.find("DARK") != std::string::npos) {
		room.isDark = true;
		return true;
	}
	return false;
}

bool isDoor(const std::string& line, roomData& room) {
	if (line.substr(0, 4) == "DOOR") {              // find door
		std::stringstream ss(line);
		std::string tmp;
		int dx, dy, target, xl, yl;
		char doorChar;
		ss >> tmp >> dx >> dy >> target >> doorChar >> xl >> yl;

		DoorInfo door;
		door.x = dx;
		door.y = dy;
		door.leadsToRoom = target - 1; // convert to right index
		door.doorChar = doorChar;
		door.xLead = xl;
		door.yLead = yl;

		std::string condition;
		while (ss >> condition) 
			door.conditions.push_back(condition);
		
		if (door.conditions.empty())
			door.conditions.push_back("NONE");

		room.doors.push_back(door); // convert to right index
		return true;
	}
	return false;
}

void mapRow(roomData& room, const std::string& line, int rowIndex) {
	for (size_t col = 0; col <= MAX_X; ++col) {
		char c = ' ';
		if (col < line.length())
			c = line[col];
		room.map[rowIndex][col] = c;
		room.initialMap[rowIndex][col] = c;
		if (c == OBSTACLE)
			room.obstaclePositions.push_back({(int)col, rowIndex, 1, 1});
		else if (c == SPRING)
			room.springPositions.push_back({(int)col, rowIndex});
	}
}

bool isObs(const std::string& line, roomData& room) {
	if (line.substr(0, 3) == "OBS") {
		std::stringstream ss(line);
		std::string tmp;
		obsData obs;
		ss >> tmp >> obs.x >> obs.y >> obs.width >> obs.height;
		room.obstaclePositions.push_back(obs);
		return true;
	}
	return false;
}

std::vector<std::string> sortFiles() {
	std::vector<std::string> files;
	std::string path = ".";
	for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path())) {
		std::string filename = entry.path().filename().string();
		if (entry.path().extension() == ".screen" && filename.rfind("adv-world", 0) == 0) {
			files.push_back(filename);
		}
	}
	std::sort(files.begin(), files.end());
	return files;

}

bool isStart(const std::string& line, roomData& room) {
	if (line.substr(0, 5) == "START") {
		std::stringstream ss(line);
		std::string tmp;
		int x1, y1, x2, y2;
		ss >> tmp >> x1 >> y1 >> x2 >> y2;
		room.startX1 = x1;
		room.startY1 = y1;
		room.startX2 = x2;
		room.startY2 = y2;
		return true;
	}
	return false;
}

bool loadRoom(const std::string& fileName, roomData& room) {
	std::cout << "DEBUG: Trying to open file: " << fileName << "... ";
	std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cerr << "Error: Could not open file " << fileName << std::endl;
		return false;
	}
	std::cout << "SUCCESS!" << std::endl;
	resetRoom(room);
	std::string line;
	int rowIndex = 0;
	while (std::getline(file, line)) {
		if (!line.empty() && line.back() == '\r') // handle possible carriage return
			line.pop_back();
		if (isDark(line, room))
			continue;
		if (isDoor(line, room))
			continue;
		if (isLastRoom(line, room))
			continue;
		if (isStart(line, room))
			continue;
		if (isObs(line, room))
			continue;
		if (rowIndex <= MAX_Y) {
			mapRow(room, line, rowIndex);
			++rowIndex;
		}
	}
	file.close();
	return true;
}

std::vector<roomData> screenLoad::loadScreens() {
	std::vector<roomData> rooms;
	std::vector<std::string> files = sortFiles();
	if (files.empty()) {
		std::cerr << "Error: No .screen files found in the current directory." << std::endl;
		return rooms;
	}
	for (const auto& fileName : files) {
		roomData room;
		if (loadRoom(fileName, room)) {
			rooms.push_back(room);
		}
	}
	return rooms;
}
