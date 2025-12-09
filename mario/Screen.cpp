#include "Screen.h"
#include "Point.h" 
#include "utils.h"
#include <iostream>
#include <windows.h> 
#include <cstring>


//==============================color item==============================
void Screen::colorItem(char item) const {
	if (!Point::isColorChose())
		return;

	switch (item) {
	case TORCH:
		setTextColor(Color::yellow);
		break;
	case SWITCH:
	case OFF_SWITCH:
		setTextColor(Color::green);
		break;
	case DOOR:
	case '1':
	case '2':
		setTextColor(Color::brown);
		break;
	case RIDDLE:
		setTextColor(Color::cyan);
		break;
	case '&':
		setTextColor(Color::red);
		break;
	case '$':
		setTextColor(Color::blue);
		break;
	default:
		setTextColor(Color::white);
		break;
	}
}

// =========================Screen constructor=================================
Screen::Screen() {
	resetRoom();
}

// =========================reset rooms to initial state=================================
void Screen::resetRoom() {
	for (int i = 0; i < NUM_OF_ROOMS; ++i) {
		for (int j = 0; j < MAX_Y + 1; ++j) {
			for (int k = 0; k < MAX_X + 2; ++k) {
				rooms[i][j][k] = initialRooms[i][j][k];
			}
		}
	}
}

void Screen::resetRoom(int roomNum) {
	for (int j = 0; j < MAX_Y + 1; ++j) {
		for (int k = 0; k < MAX_X + 2; ++k) {
			rooms[roomNum][j][k] = initialRooms[roomNum][j][k];
		}
	}
}

// =========================char at=================================
char Screen::charAt(const Point& p, int roomNum) const {
	return rooms[roomNum][p.getY()][p.getX()];
}

char Screen::charAt(int x, int y, int roomNum) const {
	if (x >= 0 && x <= MAX_X && y >= 0 && y <= MAX_Y) {
		return rooms[roomNum][y][x];
	}
	return ' ';
}

// =========================draw room to console with colors=================================
void Screen::draw(int roomNum) const {
	int y = 0;
	for (const auto& row : rooms[roomNum]) {
		gotoxy(0, y++);
		for (int i = 0; row[i] != '\0'; i++) {
			char item = row[i];
			colorItem(item);
			std::cout << item;
		}
	}
	std::cout << std::flush;
}

// =========================checks of we are going to bump in to a wall =================================
bool Screen::isWall(int x, int y, int roomNum) const {
	if (x >= 0 && x <= MAX_X && y >= 0 && y <= MAX_Y) {
		return rooms[roomNum][y][x] == 'W' || rooms[roomNum][y][x] == 'D';
	}
	return true; // out of bounds is considered a wall
}

// =========================set character at (x,y) in room=================================
void Screen::setChar(int x, int y, int roomNum, char ch) {
	if (x >= 0 && x <= MAX_X && y >= 0 && y <= MAX_Y) {
		rooms[roomNum][y][x] = ch;
	}
	gotoxy(x, y);
	colorItem(ch);
	std::cout << ch << std::flush;
}

// =========================set room to dark=================================
const char Screen::EMPTY_ROW[] = "                                                                                "; // row of spaces

void Screen::setDark() const {
	for (int col = 0; col <= MAX_Y - 2; col++) {
		gotoxy(0, col);
		std::cout << EMPTY_ROW << std::flush; // fill each row with spaces to simulate darkness
	}
	gotoxy(20, 23);
	std::cout << "ROOM IS TOO DARK TO SEE" << std::flush;
	Sleep(60);
}

// =========================lock the players in place in final room=================================
void Screen::helpLockPlayers() const {

	for (int col = 18; col <= 21; col++) {
		for (int row = 1; row <= 3; row++) {
			gotoxy(row, col);
			std::cout << " " << std::flush; // fill each row with spaces to simulate spaces instead if walls
		}
	}
}

// =========================get initial character at (x,y) in room=================================
char Screen::getInitialChar(int x, int y, int roomNum) const {
	if (x >= 0 && x <= MAX_X && y >= 0 && y <= MAX_Y) {
		return initialRooms[roomNum][y][x];
	}
	return ' ';
}


// =========================search item=================================
bool Screen::searchItem(int roomNum, char item) const {
	for (int col = 0; col <= MAX_X; col++)
		for (int row = 0; row <= MAX_Y; row++)
			if (rooms[roomNum][row][col] == item)
				return true;
	return false;
}