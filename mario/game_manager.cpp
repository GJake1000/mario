#include "game_manager.h"
#include <iostream>
#include <conio.h>  
#include <windows.h> 


//=========================new game starter=================================
void game_manager::newGameStarter()
{
	//reset positions
	currentRoom = 0;
	points[0].setPosition(1, 15);
	points[1].setPosition(1, 17);
	screen.resetRoom();
}

//=========================game manager constructor=================================
game_manager::game_manager() : points{
	// initial positions	
	Point(1 ,15, '&', STARDARD_PLAYER_1_KEYS, Color::red, 10),  // w - up, d - right, x - down, a - left, s - stay
	Point(1 ,17, '$', STARDARD_PLAYER_2_KEYS, Color::blue, 75)  // i - up, l - right, m - down, j - left, k - stay
}
{
}

//=========================run game manager=================================
void game_manager::run() {
	// main game loop
	bool isExit = false;
	isExit = loadMenu();
	
	if (isExit == false)
	{
		hideCursor();
		screen.draw(currentRoom);

		bool dark = false;

		while (true) {
			onOffLight(dark);
			for (auto& p : points) {
				char curChar = screen.charAt(p, currentRoom);
				p.draw(curChar);             // erase previous position
				int nextX = p.getNextX();    // calculate next position
				int nextY = p.getNextY();
				char item = screen.charAt(nextX, nextY, currentRoom);
				if (item != ' ') {
					handleSpacialItem(p, nextX, nextY, item); // handle item at next position
				}
				bool canMove = !screen.isWall(nextX, nextY, currentRoom); // check for wall
				p.move(canMove);
				p.draw();
			}
			if (_kbhit()) {
				char key = _getwch();
				if (key == ESC) {
					if (printPauseScreen()) break; // pause menu
				}
				else {
					for (auto& p : points) {
						p.handleKeyPressed(key, screen, currentRoom); // update direction based on key press
					}
				}
			}
			if (textAppears == true) {
				output_time++;
				if(output_time < 150)
				{
					output_time = 0;
					eraseOutput();
				}
			}
				
			turn++;	//counts turns in the game
			Sleep(50);
		}
	}
	cls();
	printCredits();		//end game
}


//=========================load menu=================================
bool game_manager::loadMenu()
{
	// initialize a new game menu

	newGameStarter(); // reset game state
	char choice;

	while (true)
	{
		cls();
		std::cout << "(1) Start a new game no colors" << "\n";
		std::cout << "(2) Start a new game colors" << "\n";
		std::cout << "(8) Present instructions and keys" << "\n";
		std::cout << "(9) EXIT" << "\n";
		choice = _getch();

		switch (choice) {
		case '1': {    //get back to "run" function and start the game
			Point::setColorChose(false);
			screen.draw(0); // draw first room
			return false;
		}
		case '2': {  //set color chose to true and get back to "run" function and start the game	
			Point::setColorChose(true);
			screen.draw(0); // draw first room
			return false;
		}
		case '8': {		//print the keys and continue the loop
			printInstructionAndKeys();
			std::cout << "Press any key to return the menu:\n";
			(void)_getch();
			break;
		}

		case '9':			//isExit = true: end the program without exit(0)
			return true;

		default: {
			std::cout << "invalid key!\n\n";
			Sleep(2000);
			break;
		}
		}
	}
}

//=========================print instructions and keys=================================
void game_manager::printInstructionAndKeys()
{
	std::string instructions = "instructions of the game: ";// will be long (probably we will take this from some file)
	std::string keys[2] = { STARDARD_PLAYER_1_KEYS , STARDARD_PLAYER_2_KEYS };

	std::cout << instructions << std::endl;

	for (int i = 0; i < 2; i++)
	{
		std::cout << "\n Player " << (i + 1) << " keys:\n";
		std::cout << "Right           : " << keys[i][0] << "\n";
		std::cout << "Down            : " << keys[i][1] << "\n";
		std::cout << "Left            : " << keys[i][2] << "\n";
		std::cout << "Up              : " << keys[i][3] << "\n";
		std::cout << "Stay            : " << keys[i][4] << "\n";
		std::cout << "Dispose element : " << keys[i][5] << "\n";
	}
	std::cout << '\n';
}

//=========================print credits=================================
void game_manager::printCredits() const {
	std::cout << "\nfinished in " << turn << " turns\n";
	std::cout << "\nBy Saar and Shahar\n...\n";
}

//=========================print pause screen=================================
bool game_manager::printPauseScreen()
{
	cls();
	std::cout << "\n\n\n\n\n\n\nGame Paused. Press ESC to continue or H to go back to main menu...\n";
	char key = _getwch();
	while (key != ESC && key != 'H' && key != 'h' && key != HEB_YOD)
		key = _getwch();

	if (key == 'H' || key == 'h' || key == HEB_YOD)
		return loadMenu();

	if (key == ESC) {
		cls();
		screen.draw(currentRoom);
		return false;
	}
	return false;
}

//=========================handle spacial item=================================
void game_manager::handleSpacialItem(Point& p, int x, int y, char item) {
	switch (item) {
	case TORCH:
		handleTorch(p, x, y);
		break;

	case SWITCH:
		handleSwitch(x, y);
		break;

	case OFF_SWITCH:
		turnOff(x, y, currentRoom);
		break;

	case RIDDLE:
		handleRiddle(p, x, y);
		break;

	case KEY:
		handleKey(p, x, y);
		break;

	case DOOR:		//door to 0 (probably does not exist)
	case '1':		//door to 1
	case '2':		//door ??? win maybe?
		handleDoor(p, item); //only if has key == true
		break;
	}
}

//=========================handle torch=================================
void game_manager::handleTorch(Point& p, int x, int y) {
	if (p.drawToInventory(screen, currentRoom, TORCH)) {
		screen.setChar(x, y, currentRoom, EMPTY_CELL); // remove torch from the room 
	}
}

//=========================has torch=================================
bool game_manager::hasTorch() {
	return (points[0].checkInventory(screen, currentRoom) == TORCH || points[1].checkInventory(screen, currentRoom) == TORCH);
}

//=========================handle switch=================================
void game_manager::handleSwitch(int x, int y) {
	screen.setChar(x, y, currentRoom, OFF_SWITCH);

	for (int row = 0; row <= Screen::MAX_Y; row++)
		for (int col = 0; col <= Screen::MAX_X; col++)
			if (screen.charAt(col, row, currentRoom) == DOOR_D)
				screen.setChar(col, row, currentRoom, EMPTY_CELL); // open the door by putting empty cells where it was
}

//=========================handle riddle=================================
void game_manager::handleRiddle(Point& p, int x, int y) {
	
	char correct;
	if (currentRoom == 0)
		correct = printRiddle0();
	if (currentRoom == 1)
		correct = printRiddle1();

	while (true) {
		if (_kbhit()) {
			char ans = _getch();
			bool wasRight = handleAnswer(correct, ans, p);
			if (wasRight) screen.setChar(x, y, currentRoom, ' ');
			cls();
			screen.draw(currentRoom);

			if (currentRoom == 1 && !hasTorch())
				screen.setDark();

			return;
		}
	}
}


//=========================riddle 0=================================
char game_manager::printRiddle0() {
	cls();
	std::cout << "\n\n\n         Riddle: To the blind I'm nothing, to the hrveller I'm everything.\n                 I am the sun held in your hand.\n                 Without me, the next room will be your grave.\n\n                 What am I?\n\n";
	std::cout << "         (1) A Sword\n";
	std::cout << "         (2) A Torch\n";
	std::cout << "         (3) The Moon\n";
	std::cout << "         (4) A Light bulb\n";
	return '2';
}

////=========================riddle 1=================================
char game_manager::printRiddle1() {
	cls();
	std::cout << "\n\n\n         Riddle: I exist only when there is light, but direct light kills me.\n                 I grow tall when the sun goes down, but disappear completly in the dark\n                 What am I?\n\n";
	std::cout << "         (1) A Vampire\n";
	std::cout << "         (2) A Dream\n";
	std::cout << "         (3) A Shdow\n";
	std::cout << "         (4) A Mushroom\n";
	return '3';
}

//================================handle answer====================================
bool game_manager::handleAnswer(char correct, char ans, Point& p) {
	if (ans == correct) {
		std::cout << "\n\n\n\n\n\n          CORRECT!";
		Sleep(2000);
		return true;
	}
	else {
		std::cout << "\n\n\n\n\n\n          WRONG!";
		Sleep(2000);
		p.setDirection(Direction::STAY);
		return false;
	}
}

//=========================handle key=================================
void game_manager::handleKey(Point& p, int x, int y) {
	if (p.drawToInventory(screen, currentRoom, KEY)) {
		screen.setChar(x, y, currentRoom, EMPTY_CELL); // remove key from the room
	}
}

//===========================handle door=================================
void game_manager::handleDoor(Point& currentPlayer, char doorNum) {
	char inv1 = '\0', inv2 = '\0';
	for (const auto& player : points) {
		if (player.getPlayerChar() == currentPlayer.getPlayerChar()) {
			inv1 = player.checkInventory(screen, currentRoom);
			continue;
		}
		char secPlayerChar = screen.charAt(player.getX(), player.getY(), currentRoom);
		inv2 = player.checkInventory(screen, currentRoom);
		if (secPlayerChar != doorNum)
			return;
	}

	if (inv1 != KEY && inv2 != KEY && doorNum - '0' > currentRoom && screen.searchItem(currentRoom, KEY)) {		//if none of the players have a key, the door will not open
		textAppears = printOutput("Door is locked !");
		return;
	}

	if (doorNum - '0' < currentRoom) { //go back a floor (as of now it's only possible from floor 1 to floor 0)
		points[0].setPosition(77, 20);
		points[1].setPosition(77, 21);
	}
	else { 
		points[0].setPosition(2, 19);
		points[1].setPosition(2, 21);
	}

	currentRoom = doorNum - '0'; //update current room
	cls();
	screen.draw(currentRoom);

	if (inv1 == KEY || inv2 == KEY) { // remove key from inventory if used
		if (inv1 == KEY)
			currentPlayer.drawToInventory(screen, currentRoom, EMPTY_CELL);
		else
			points[(currentPlayer.getPlayerChar() == points[0].getPlayerChar()) ? 1 : 0].drawToInventory(screen, currentRoom, EMPTY_CELL);
	}

	if (currentRoom == 2)
		screen.helpLockPlayers();
}

//==============================on off lights=============================
void game_manager::onOffLight(bool& dark) {
	if (currentRoom != 1) {
		dark = false;
		return;
	}

	bool darkNow = !hasTorch(); // if niether has torch it will become dark
	if (darkNow != dark) {      // check about now if anyone has torch
		if (darkNow) screen.setDark();
		else screen.draw(currentRoom);
	}
	dark = darkNow;
}

//===========================print output=================================
bool game_manager::printOutput(const char* output) {
	eraseOutput();

	int len = strlen(output);
	int spaces_to_center = (Screen::MAX_X - len) / 2;

	gotoxy(spaces_to_center, 23);

	for (int i = 0; i < len; i++) {
		std::cout << output[i];
		if (i % 2 == 0)
			Sleep(1);
	}
	return true;
}

//===========================erase output=================================
void game_manager::eraseOutput() {
	gotoxy(0, 23);
	std::cout << std::string(Screen::MAX_X, ' ');
}

//==============================turn off================================
void game_manager::turnOff(int x, int y, int roomNum) {
	for (int row = 0; row < Screen::MAX_Y; row++) {
		for (int col = 0; col <= Screen::MAX_X; col++) {
			if (screen.getInitialChar(col, row, roomNum) == 'D')
				screen.setChar(col, row, roomNum, 'D');
		}
	}
	screen.setChar(x, y, roomNum, SWITCH);
}