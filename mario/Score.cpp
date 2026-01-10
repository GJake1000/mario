#include "Score.h"
#include "utils.h"
#include <iostream>
void Score::draw(int time, int lives) const {
	gotoxyLegendSafe(scoreX, scoreY);
	int score = calc(time, lives);
	std::cout << score << "    "; // extra spaces to clear previous longer scores
}

void Score::add(int amount) {
	additionalScore += amount;
}

void Score::reset(int initScore) {
	
	additionalScore = 0;
	initialScore = initScore;
}

int Score::calc(int time, int lives) const {
	int score = initialScore - (time * timeReduce) + (lives * lifeBonus) + additionalScore;
	return score <= 0 ? 0 : score;
}
