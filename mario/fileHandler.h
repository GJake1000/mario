#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "Obstacle.h"
#include "Spring.h"  
#include "Screen.h"  

class Riddle {
private:
    std::string question_;
    std::string options_[4];
    char correctOption_ = ' ';

public:
    std::string& question() { return question_; }
    const std::string& question() const { return question_; }

    std::string& option(int i) { return options_[i]; }
    const std::string& option(int i) const { return options_[i]; }

    char& correctOption() { return correctOption_; }
    char correctOption() const { return correctOption_; }

    friend std::ostream& operator<<(std::ostream& os, const Riddle& riddle) {
        std::string rid = riddle.question_;
        size_t pos = 0;
        while ((pos = rid.find('|', pos)) != std::string::npos) {
            rid.replace(pos, 1, "\n          ");
            pos += 10;
        }
        os << "\n\n\n          Riddle:\n";
        os << "          " << rid << "\n\n";
        for (int i = 0; i < 4; ++i) {
            os << "          (" << (i + 1) << ") " << riddle.options_[i] << "\n";
        }
        return os;
    }
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

