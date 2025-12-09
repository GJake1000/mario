#pragma once
#include "Screen.h"
#include "Point.h"


class game_manager {
	enum { ESC = 27 };
	Point points[2];
	Screen screen;
	int currentRoom = 0;
	int turn = 0;
	int output_time = 0;
	void newGameStarter();
	bool textAppears = false;

public:
	game_manager();
	void run();
	bool loadMenu();
	void printInstructionAndKeys();
	void printCredits() const;
	bool printPauseScreen();
	void handleSpacialItem(Point &p, int x, int y, char item);
	void handleTorch(Point& p, int x, int y);
	void handleSwitch(int x, int y);
	void handleRiddle(Point& p, int x, int y);
	void handleKey(Point& p, int x, int y);
	void handleDoor(Point& currentPlayer, char doorNum);
	bool hasTorch();
	void onOffLight(bool& dark);
	bool printOutput(const char* output);
	void eraseOutput();
	bool handleAnswer(char correct, char ans, Point& p);
	void turnOff(int x, int y, int roomNum);
	char printRiddle0();
	char printRiddle1();
};