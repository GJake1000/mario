#pragma once
#include "game_manager.h"
#include <fstream>
#include <windows.h>

class fileGame : public game_manager {
	bool silent;
	std::ifstream stepsFile;
	int stepIndex = -1;
	char keyInFile = '\0';
public: 
	fileGame(bool silent);
	~fileGame() { if (stepsFile.is_open()) stepsFile.close(); }
	virtual bool input(char& key) override;
	virtual void updateSleep() override { if (!silent) Sleep(10); }
};

