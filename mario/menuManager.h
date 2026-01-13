#pragma once
#include <iostream>
#include <string>
#include <conio.h>

class menuManager {
	static void cls();
public:
	static char printMenu();
	static void printInstructions();
	static void printCredits(int turns);
	static bool printPauseScreen();

};

