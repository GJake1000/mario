#include "lives.h"

//===================================draw===================================
void lives::draw() const {
	gotoxy(livesX, livesY);
	if (color)
		setTextColor(Color::red);
	
	for (int i = 0; i < count; ++i) {
		std::cout << "<3 " << std::flush; // heart symbol
	}
	for (int i = count; i < maxLives; ++i) {
		std::cout << "  "  << std::flush; // empty space for lost lives
	}
	setTextColor(Color::white);
}

//===================================lose life===================================
bool lives::loseLife() {
	if (count > 0) {
		--count;
		draw();
	}
	return count > 0;
}
