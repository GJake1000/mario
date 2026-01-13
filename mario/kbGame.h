#pragma once
#include "game_manager.h"
#include <conio.h>
#include <fstream>

class kbGame : public game_manager {
	bool isLoading;
	std::ofstream stepsFile;
	std::ofstream resFile;

public:
	char translateToEnglish(int k);
	kbGame(bool silent, bool load);
	~kbGame() { if (stepsFile.is_open()) stepsFile.close(); }
	virtual bool input(char& key) override;
	virtual void reportEvent(const std::string& event) override;
	virtual void run() override;

};

