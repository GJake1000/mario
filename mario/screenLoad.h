#pragma once
#include <vector>
#include "ScreensData.h"

class screenLoad {
public:
	static std::vector<roomData> loadScreens();

	int legendRow;
	static constexpr const char* legend = "                                     LIVE | SCORE                             \nPlayer & :                             INVENTORY                   Player $ :     \n";



//private:
	//std::string fileNaming(int index);
	//void resetRoom(roomData& room);
	//bool isDark(const std::string& line, roomData& room);
	//bool isDoor(const std::string& line, roomData& room);
	//void mapRow(roomData& room, const std::string& line, int rowIndex); 
};

