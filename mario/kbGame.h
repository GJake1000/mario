#pragma once
#include "game_manager.h"
#include <conio.h>
#include <fstream>

class kbGame : public game_manager {
	bool isLoading;
	std::ofstream stepsFile;

public:
	char translateToEnglish(int k);
	kbGame(bool load);
	~kbGame() { if (stepsFile.is_open()) stepsFile.close(); }
	virtual bool input(char& key) override;

};

