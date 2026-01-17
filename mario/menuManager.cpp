#include <Windows.h>
#include "menuManager.h"
#include <synchapi.h>
#include "auxThing.h"

void menuManager::cls() {
	system("cls");
}

char menuManager::printMenu() {
	// initialize a new game menu
	char choice = 0;

	while (true) {
		cls();
		std::cout << "(1) Start a new game no colors" << "\n";
		std::cout << "(2) Start a new game colors" << "\n";
		std::cout << "(8) Present instructions and keys" << "\n";
		std::cout << "(9) EXIT" << "\n";
		char choice = _getch();

		if (choice == '1' || choice == '9' || choice == '2') {
			return choice;
		}
		else if (choice == '8') {
			printInstructions();
		}
		else {
			std::cout << "Invalid Input..\n";
			Sleep(200);
		}
	}
}

void menuManager::printInstructions() {
	cls();
	std::string instructions = "instructions of the game: ";// will be long (probably we will take this from some file)
	std::string keys[2] = { STARDARD_PLAYER_1_KEYS , STARDARD_PLAYER_2_KEYS };

	std::cout << instructions << std::endl;

	for (int i = 0; i < 2; i++)
	{
		std::cout << "\n Player " << (i + 1) << " keys:\n";
		std::cout << "Up              : " << keys[i][0] << "\n";
		std::cout << "Right           : " << keys[i][1] << "\n";
		std::cout << "Down            : " << keys[i][2] << "\n";
		std::cout << "Left            : " << keys[i][3] << "\n";
		std::cout << "Stay            : " << keys[i][4] << "\n";
		std::cout << "Dispose element : " << keys[i][5] << "\n";
	}
	std::cout << "\nPress any key to return to menu...";
	(void)_getch();
}

void menuManager::printCredits(int turns) {
	std::cout << "\nFinished in " << turns << " turns\n";
	std::cout << "\nBy Saar and Shahar\n...\n";
}

bool menuManager::printPauseScreen() {
	cls();
	std::cout << "\n\n\nGame Paused.\n";
	std::cout << "Press ESC to continue playing.\n";
	std::cout << "Press 'H' to go back to main menu.\n";

	while (true) {
		char key = _getch();
		if (key == 27) return false; // ESC
		if (key == 'H'|| key == 'h' || key == HEB_YOD) return true;
	}
}
