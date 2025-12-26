#pragma once
#include "Screen.h"
#include "Point.h"
#include "Obstacle.h"
#include "lives.h"
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
	lives gameLives;
public:
	//========flow control========
	game_manager();
	void run();
	void initilDefine();
	void movePlayer(Point& p);
	void textOpt(bool text, int& time);
	bool handleKB();
	bool loadMenu();
	void printInstructionAndKeys();
	void printCredits() const;
	bool printPauseScreen();

	//=========game mechanics=========
	//general mechanics
	void handleSpacialItem(Point &p, int x, int y, char item);
	bool printOutput(const char* output);
	void eraseOutput();
	bool removeLife();

	//torch mechanics
	void handleTorch(Point& p, int x, int y);
	bool hasTorch();
	void onOffLight(bool& dark);

	//switch mechanics
	void handleSwitch(int x, int y);
	void turnOff(int x, int y, int roomNum);

	//riddle mechanics
	void handleRiddle(Point& p, int x, int y);
	char printRiddle(int index);
	bool handleAnswer(char correct, char ans, Point& p);

	//bomb mechanics
	void handleBomb(Point& p, int x, int y);
	void activateBomb(Screen& screen, int x, int y, int roomNum);
	bool playerHit(int bombX, int bombY, int radius);
	void setBombTimer(int x, int y, int roomNum);
	void checkBombActivation();

	//obstacle mechanics
	void handleObstacle(Point& p, int x, int y);
	void moveObstacle(int left, int right, int down, int up);
	void drawObs();

	//door mechanics
	void handleDoor(Point& currentPlayer, char doorNum);
	void handleKey(Point& p, int x, int y);
	bool bothPlayersAtSameChar(Point& pyr1, char checker, char& inv1, char& inv2);
	void removeKeyAfterUse(char inv1, char inv2, Point& currentPlayer);
	void posSetAfterDoor(char doorNum);
	
	

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
		char correctOption;

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
	char presentRiddle(int riddleIndex);
};