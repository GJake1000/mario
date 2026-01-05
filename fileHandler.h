#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Obstacle.h"
#include "Spring.h"  
#include "Screen.h"  

struct Riddle {
	std::string question;
	std::string options[4];
	char correctOption;

};

class fileHandler {
	std::string p1keys;
	std::string p2keys;
	std::string riddleFile;
	int riddleScore;
	int bombTimer;
	int bombRadius;
	int initialLives;
	int initialScore;

	std::vector<Riddle> rids;
public:
	fileHandler();
	bool loadGlobal(const std::string& fName);
	bool loadRiddles();

	std::vector<Obstacle> createObstacles(const Screen& screen, int roomNum);

	const std::string& getP1Keys() const { return p1keys; }
	const std::string& getP2Keys() const { return p2keys; }
	int getRidScore() const { return riddleScore; }
	int getBombTimer() const { return bombTimer; }
	int getBombRadius() const { return bombRadius; }
	int getInitialLives() const { return initialLives; }
	int getInitialScore() const { return initialScore; }

	const Riddle& getRid(int idx) const;
	int getRidCnt() const { return rids.size(); }
};

