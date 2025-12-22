#pragma once
#include "Screen.h"
#include "Point.h"
#include "Obstacle.h"
#include "lives.h"
#include <iostream>
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
	char printRiddle(int index);
	void handleKey(Point& p, int x, int y);
	void handleBomb(Point& p, int x, int y);
	void activateBomb(Screen& screen, int x, int y, int roomNum);
	bool playerHit(int bombX, int bombY, int radius);
	void handleObstacle(Point& p, int x, int y);
	void moveObstacle(int left, int right, int down, int up);
	void handleDoor(Point& currentPlayer, char doorNum);
	bool bothPlayersAtSameChar(Point& pyr1, char checker, char& inv1, char& inv2);
	void removeKeyAfterUse(char inv1, char inv2, Point& currentPlayer);
	void posSetAfterDoor(char doorNum);
	bool hasTorch();
	void onOffLight(bool& dark);
	bool printOutput(const char* output);
	void eraseOutput();
	bool handleAnswer(char correct, char ans, Point& p);
	void turnOff(int x, int y, int roomNum);
	void setBombTimer(int x, int y, int roomNum);
	bool removeLife();

private:
	std::vector<Obstacle> obstacles;
	Obstacle* findObs(int x, int y);
	void obsDef();
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