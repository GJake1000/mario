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

bool validGame(game_manager* game) {
	if (!game) return false;
	std::string error = game->catchError();
	if (!error.empty()) {
		if (error.find("Error:") != std::string::npos) {
			std::cerr << error << std::endl;
			return false;
		}
		else {
			std::cerr << error << std::endl;
			std::cout << "press any key to continue despite the warning";
			std::cin.get();
			return true;
		}
	}
	return true;
}

int main(int argc, char* argv[]) {
	game_manager* game = nullptr;
	try {
		game = initGame(argc, argv);
		if (!validGame(game)) {
			delete game;
			return 1;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Fatal Error: " << e.what() << std::endl;
		delete game;
		return 1;
	}
	catch (...) {
		std::cerr << "Unknown Error occurred." << std::endl;
		delete game;
		return 1;
	}
	game->run();
	delete game;
}