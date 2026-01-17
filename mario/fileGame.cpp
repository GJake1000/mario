#include "fileGame.h"

fileGame::fileGame(bool silent) : game_manager(silent) {
	stepsFile.open("adv-world.steps");
	if(!(stepsFile >> stepIndex >> keyInFile))
		stepIndex = -1;
	resFile.open("adv-world.result");

}

fileGame::~fileGame() {
	if (resFile.is_open())
		resFile.close();
	gotoxy(0, errors + 1);
	std::cout << "errors amount: " << errors << std::endl;
}

bool fileGame::input(char& key) {
	if (stepIndex != -1 && stepIndex == turn) {
		key = keyInFile;
		if(!(stepsFile >> stepIndex >> keyInFile))
			stepIndex = -1;
		return true;
	}
	return false;
}

void fileGame::reportEvent(const std::string& event) {
	if (!resFile.is_open())
		return;

	std::string line;
	std::string inRes = std::to_string(turn) + ": " + event;

	if (std::getline(resFile, line)) {
		if (line != inRes) {
			gotoxy(0, errors + 1);
			std::cerr << "error at turn: " << turn << ", got: " << line <<
				", but should get: " << inRes << std::endl;
			++errors;
		}
	}
	else {
		gotoxy(0, errors + 1);
		std::cerr << "error at turn: " << turn 
			<< "resaults file ended earlier than expected." << std::endl;
		++errors;
	}
}

void fileGame::run() {
	Point::setColorChose(false);
	gameLives.setColor(false);
	genericRun();
	//cls();
}

bool fileGame::handleKB() {
	bool isExit = game_manager::handleKB();
	if (isExit)
		return true;
	if (stepIndex == -1)
		return true;
	return false;
}
