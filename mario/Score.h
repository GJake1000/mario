#pragma once

class Score {
	int additionalScore = 0;
	const int scoreX = 60, scoreY = 23;
	const int initialScore = 15000;
	const int lifeBonus = 200; 
	const int ridBonus = 150;
	const int timeReduce = 2;
public:
	void draw(int time, int lives) const;
	void add(int amount);
	void reset();
	int calc(int time, int lives) const;
};
