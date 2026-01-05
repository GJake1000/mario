#pragma once
#include "Screen.h"
#include "ScreensData.h"
#include "Point.h"
#include "Obstacle.h"
#include "lives.h"
#include "Score.h"
#include "fileHandler.h"
#include <iostream>
#include "Spring.h"
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
	int playerAtDoor = -1, playerAtDoorX = -1, playerAtDoorY = -1, waitingRoom = -1;
	lives gameLives;
	Score gameScore;
	bool gameOver = false;
	fileHandler fileH;
public:
	//========flow control========
	game_manager();
	void run();
	bool gameFlow(bool& dark);
	void resetPoints();
	void resetDoorVars();
	void initilDefine();
	void movePlayer(Point& p);
	void textOpt();
	bool handleKB();
	bool loadMenu();
	void printInstructionAndKeys() const;
	void printCredits() const;
	bool printPauseScreen();

	//=========game mechanics=========
	//general mechanics
	void handleSpacialItem(Point &p, int x, int y, char item);
	bool printOutput(const char* output) const;
	void eraseOutput() const;
	bool removeLife();

	//torch mechanics
	void handleTorch(Point& p, int x, int y);
	bool hasTorch() const;
	void onOffLight(bool& dark);

	//switch mechanics
	void handleSwitch(int x, int y);
	void turnOff(int x, int y, int roomNum);
	bool doorCondSw(DoorInfo* door, size_t& i);

	//riddle mechanics
	void handleRiddle(Point& p, int x, int y);
	char printRiddle(int index) const;
	bool handleAnswer(char correct, char ans, Point& p);
	bool solveRiddle(Point& p);

	//bomb mechanics
	void handleBomb(Point& p, int x, int y);
	void activateBomb(Screen& screen, int x, int y, int roomNum);
	bool playerHit(int bombX, int bombY, int radius) const;
	void setBombTimer(int x, int y, int roomNum);
	void checkBombActivation();

	//obstacle mechanics
	void handleObstacle(Point& p, int x, int y);
	void drawObs();

	//door mechanics
	void handleDoor(Point& currentPlayer, int x, int y);
	bool canUnlock(Point& p, DoorInfo* door);
	void resetThingsAfterDoor(int doorNum, const DoorInfo* door, bool moveBoth);
	bool checkCond(bool& needKey, bool& needRiddle, Point& p, const char inv1, const char inv2, DoorInfo* door);
	void handleKey(Point& p, int x, int y);
	void removeKeyAfterUse(char inv1, char inv2, Point& currentPlayer);
	
	

private:
	std::vector<Obstacle> obstacles;
	Obstacle* findObs(int x, int y);
	void obsDef();

	//spring stuff
	std::vector<Spring> springs;
	Spring* findSpring(int x, int y);
	void springDefFromMap(int roomNum);
	void handleSpring(Point& p, int x, int y);

	std::vector<std::pair<int, int>> hiddenCells[2];  // store (x,y) hidden for each player that stepped on the spring
	void hideCell(int idx, int x, int y);
	void restoreHidden(int idx);
	
	bool charging[2] = { false, false };
	int chargeDirX[2] = { 0, 0 };
	int chargeDirY[2] = { 0, 0 };
	int chargingCount[2] = { 0, 0 };

	void applyLaunchMovementIfNeeded(Point& p); // called inside the per-player loop

	void tryTriggerSpringRelease(int idx, Point& p, bool canMove);

	void resetSpringState();

	int traverseSpringTowardWallEnd(const Spring& spr, int startX, int startY, Point* pToMove);


	struct Riddle {
		std::string question;
		std::string options[4];
		char correctOption =  ' ';

		friend std::ostream& operator<<(std::ostream& os, const Riddle& riddle) {
			std::string rid = riddle.question;
			size_t pos = 0;
			while ((pos = rid.find('|', pos)) != std::string::npos) {
				rid.replace(pos, 1, "\n          ");
				pos += 10; // Move past the newly inserted underscores
			}
			os << "\n\n\n          Riddle:\n";
			os << "          " << rid << "\n\n";
			for (int i = 0; i < 4; ++i) {
				os << "          (" << (i + 1) << ") " << riddle.options[i] << "\n";
			}
			return os;
		}
	};

	std::vector<Riddle> riddles;
	void loadRiddles(const char* fileName);
}; 