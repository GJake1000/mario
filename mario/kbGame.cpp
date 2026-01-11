#include "kbGame.h"
#include <cctype>

char kbGame::translateToEnglish(int k) {
	if (k >= 'a' && k <= 'z') // already english
		return k;				 
	if (k >= 'A' && k <= 'Z') // already english
		return k;
	switch (k) { // handle hebrew letters
		// player 1
	case HEB_VAV   : return 'W'; // ?
	case HEB_ZAYIN : return 'X'; // ?
	case HEB_HET   : return 'D'; // ?
	case HEB_TET   : return 'A'; // ?'
	case HEB_GERESH: return 'S'; // ?
	case HEB_CAF   : return 'E'; // ?
		// player 2
	case HEB_LAMED : return 'I'; // ?
	case HEB_MEM   : return 'M'; // ?
	case HEB_NUN   : return 'L'; // ?
	case HEB_SAMECH: return 'J'; // ?
	case HEB_AYIN  : return 'K'; // ?
	case HEB_PE    : return 'O'; // ?
		// other
	case HEB_YOD   : return 'H'; // ?
	default:
		return (char)k;
	}
}
kbGame::kbGame(bool load) : isLoading(load) {
	if (isLoading) {
		stepsFile.open("adv-world.steps");
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