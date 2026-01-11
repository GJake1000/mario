#include "fileGame.h"

fileGame::fileGame(bool silent) : silent(silent) {
	stepsFile.open("adv-world.steps");
	if(!(stepsFile >> stepIndex >> keyInFile))
		stepIndex = -1;

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
