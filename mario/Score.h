#pragma once
#include "utils.h"

class Score {
	int additionalScore = 0;
	int scoreX = 60; //scoreY will be set to legendY in draw, so we will just call for g_currentLegendY
	int initialScore = 0;
	const int lifeBonus = 200; 
	const int ridBonus = 150;
	const int timeReduce = 2;
public:
	void draw(int time, int lives) const;
	void add(int amount);
	void reset(int initScore);
	int calc(int time, int lives) const;
};
