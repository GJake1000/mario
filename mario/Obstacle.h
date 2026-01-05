#pragma once
#include "Screen.h"
#include "utils.h"
#include "Coordinates.h"
#include <vector>


class Obstacle {
	//int x, y; // position of the right up corner of obstacle

	std::vector<Coord> cords;
	int volume = 0;

	//int width, height; // dimensions of the obstacle
	int roomNum;
	Color color;
public:
	Obstacle(std::vector<Coord> crd, Color clr, int room) : roomNum(room), color(clr), cords(std::move(crd)) 
	{
		volume = (int)cords.size();	
	}
	
		//Obstacle(int x1, int y1, int w, int h, int rN, Color c) : x(x1), y(y1), width(w), height(h), roomNum(rN), color(c) {}
	
	bool contains(const Coord& crd) const;

	void draw(Screen& screen) const;
	void erase(Screen& screen) const;
	bool tryMove(int dx, int dy, Screen& screen);	
	//bool loc(int cx, int cy, int curRoom) const;

	int getRoom() const {return roomNum; };
	int getVolume() const { return volume; } 
};

