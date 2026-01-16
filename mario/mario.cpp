#include "game_manager.h"
#include "kbGame.h"
#include "fileGame.h"
#include <string>

static game_manager* initGame(int argc, char* argv[]) {
	bool isLoading = false;
	bool isSave = false;
	bool silent = false;
	for (int i = 1; i < argc; i++) {
		std::string arg = argv[i];
		if (arg == "-load") 
			isLoading = true;
		if (arg == "-save") 
			isSave = true;
		if (arg == "-silent") 
			silent = true;
	}
	if (!isLoading) 
		silent = false;
	if (isLoading) 
		return new fileGame(silent);
	else 
		return new kbGame(false, isSave);
}

int main(int argc, char* argv[]) {
	game_manager* game;
	game = initGame(argc, argv);
	game->run();
	delete game;
}