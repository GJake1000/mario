#pragma once
#include "utils.h"
#include <iostream>

class lives {
	int count;
	int maxLives;
	int livesX;
	int livesY;
	bool color;
public:
	lives(int maxL = 3, int x = 25, int y = 23, bool isColor = true) : count(maxL), maxLives(maxL), livesX(x), livesY(y), color(isColor) {}
	void setColor(bool mode) { color = mode; }
	void resetLives(int amount) { count = amount; }
	void draw() const;
	bool loseLife();
	int getLives() const { return count; }
};

