#pragma once
#include "Screen.h"
#include "Point.h"
#include "Obstacle.h"
#include <vector>


class game_manager {
	enum { ESC = 27 };
	Point points[2];
	Screen screen;
	int currentRoom = 0;
	int turn = 0;
	int output_time = 0;
	void newGameStarter();
	bool textAppears = false;
	int bombDisposalTime = -1;
	int bombX = -1, bombY = -1, bombRoom = -1;

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
	void handleBomb(Point& p, int x, int y);
	void activateBomb(Screen& screen, int x, int y, int roomNum);
	void handleObstacle(Point& p, int x, int y);
	void moveObstacle(int left, int right, int down, int up);
	void handleDoor(Point& currentPlayer, char doorNum);
	bool bothPlayersAtSameChar(Point& pyr1, char checker, char& inv1, char& inv2);
	bool hasTorch();
	void onOffLight(bool& dark);
	bool printOutput(const char* output);
	void eraseOutput();
	bool handleAnswer(char correct, char ans, Point& p);
	void turnOff(int x, int y, int roomNum);
	char printRiddle0();
	char printRiddle1();
	void setBombTimer(int x, int y, int roomNum);

private:
	std::vector<Obstacle> obstacles;
	Obstacle* findObs(int x, int y);
	void obsDef();
};