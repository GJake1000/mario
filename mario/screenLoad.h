#pragma once
#include <vector>

#include "ScreensData.h"

class screenLoad {
public:
	static std::vector<roomData> loadScreens();
	int legendRow;
	static constexpr const char* legend = "";
};

