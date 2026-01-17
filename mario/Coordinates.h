#pragma once


struct Coord {
	int x;
	int y;

	Coord() = default;
	Coord(int x_, int y_) : x(x_), y(y_) {}	

	bool operator==(const Coord& other) const {
		return x == other.x && y == other.y;
	}	

	bool operator!=(const Coord& other) const {
		return !(*this == other);
	}	
};