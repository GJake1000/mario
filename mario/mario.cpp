#include "game_manager.h"
#include "kbGame.h"
#include "fileGame.h"
#include <string>

game_manager* initGame(int argc, char* argv[]) {
	bool isLoading = false;
	bool silent = false;
	for (int i = 1; i < argc; i++) {
		std::string arg = argv[i];
		if (arg == "-load") 
			isLoading = true;
		if (arg == "-silent") 
			silent = true;
	}
	if (isLoading) 
		return new fileGame(silent);
	else 
		return new kbGame(true);
}

int main(int argc, char* argv[]) {
	game_manager* game;
	game = initGame(argc, argv);
	game->run();
	delete game;
}