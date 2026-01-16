#include "kbGame.h"
#include "menuManager.h"
#include <cctype>

char kbGame::translateToEnglish(int k) {
	if (k >= 'a' && k <= 'z') // already english
		return k;				 
	if (k >= 'A' && k <= 'Z') // already english
		return k;
	switch (k) { // handle hebrew letters
		// player 1
	case HEB_GERESH     : return 'W';
	case HEB_GIMEL      : return 'D';
	case HEB_SAMECH     : return 'X';
	case HEB_SHIN       : return 'A';
	case HEB_DALET      : return 'S';
	case HEB_QOF        : return 'E';
		// player 2
	case HEB_NUN_SOFIT  : return 'I';
	case HEB_KHAF_SOFIT : return 'L';
	case HEB_TSADI      : return 'M';
	case HEB_HET        : return 'J';
	case HEB_LAMED      : return 'K';
	case HEB_MEM_SOFIT  : return 'O';
		// other
	case HEB_YOD        : return 'H'; 
	default:
		return (char)k;
	}
}

kbGame::kbGame(bool silent, bool load) : game_manager(silent), isLoading(load) {
	if (isLoading) {
		stepsFile.open("adv-world.steps");
		resFile.open("adv-world.result");
	}
}

bool kbGame::input(char& key) {
	if (_kbhit()) {
		int k = _getwch();
		char engKey = translateToEnglish(k);
		key = (char)std::toupper((unsigned char)engKey);
		if (isLoading && stepsFile.is_open()) {
			// format: [turn No.]   [key pressed]   
			stepsFile << turn << ' ' << key << std::endl;
		}
		return true;
	}
	return false;
}

void kbGame::reportEvent(const std::string& event) {
	if (resFile.is_open())
		resFile << turn << ": " << event << std::endl;
}

void kbGame::run() {
	bool displayMenu = true;
	while (displayMenu) {
		char choice = menuManager::printMenu();
		if (choice == '9')
			displayMenu = false;
		else {
			bool colors = (choice == '2');
			Point::setColorChose(colors);
			gameLives.setColor(colors);
			genericRun();
		}
	}
	cls();
	menuManager::printCredits(turn);
}
