#pragma once

#include <conio.h>
#include <fstream>

#include "game_manager.h"


class kbGame : public game_manager {
	bool isSave;
	std::ofstream stepsFile;
	std::ofstream resFile;

public:
	char translateToEnglish(int k);
	kbGame(bool silent, bool save);
	~kbGame() {
		if (stepsFile.is_open()) stepsFile.close();
		if (resFile.is_open()) resFile.close();
	}
	virtual bool input(char& key) override;
	virtual void reportEvent(const std::string& event) override;
	virtual void run() override;
	virtual void updateSleep() const override { Sleep(50); }

};

