#include "game_manager.h"
#include <iostream>
#include <conio.h>  
#include <windows.h> 
#include <string>
#include <fstream>


//=========================new game starter=================================
void game_manager::newGameStarter()
{
	//reset positions
	currentRoom = 0;
	points[0].setPosition(1, 15);
	points[1].setPosition(1, 17);
	gameLives.resetLives();
	gameLives.draw();
	screen.resetRoom();
	resetSpringState();
	springDefFromMap(currentRoom);
	obsDef();
	loadRiddles("riddles.txt");
}

//=========================game manager constructor=================================
game_manager::game_manager() : points{
	// initial positions	
	Point(1 ,15, '&', STARDARD_PLAYER_1_KEYS, Color::red, 10),  // w - up, d - right, x - down, a - left, s - stay
	Point(1 ,17, '$', STARDARD_PLAYER_2_KEYS, Color::blue, 75)  // i - up, l - right, m - down, j - left, k - stay
	}, gameLives()
{
	// set game manager for each point
	points[0].setGameManager(this);
	points[1].setGameManager(this);
}

//=========================run game manager=================================
void game_manager::run() {
	// main game loop
	bool displayMenu = true;
	while (displayMenu) {
		bool isExit = loadMenu();
	
		if (isExit == false)
		{
			hideCursor();
			screen.draw(currentRoom);
			gameLives.draw();

			bool dark = false;

			while (true) {
				onOffLight(dark);
				if (gameLives.getLives() <= 0) break; // game over go to menu

				// check for bomb activation
				if (bombDisposalTime != -1 && turn - bombDisposalTime >= 5) {
					activateBomb(screen, bombX, bombY, bombRoom);
					bombDisposalTime = -1; // reset bomb timer
				}

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

					int idx = (p.getPlayerChar() == points[0].getPlayerChar()) ? 0 : 1;
					tryTriggerSpringRelease(idx, p, canMove);

					p.move(canMove);
					p.draw();

					applyLaunchMovementIfNeeded(p);
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
				//////maybe make into a function somehow/////////
				if (textAppears == true) {
					output_time++;
					if (output_time > 150)
					{
						output_time = 0;
						eraseOutput();
					}
				}
				/////////////////////////////////////////////////
				
				turn++;	//counts turns in the game
				Sleep(50);

			}
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
			gameLives.setColor(false);
			screen.draw(0); // draw first room
			return false;
		}
		case '2': {  //set color chose to true and get back to "run" function and start the game	
			Point::setColorChose(true);
			gameLives.setColor(true);
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
		std::cout << "Up              : " << keys[i][0] << "\n";
		std::cout << "Right           : " << keys[i][1] << "\n";
		std::cout << "Down            : " << keys[i][2] << "\n";
		std::cout << "Left            : " << keys[i][3] << "\n";
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

	case BOMB:
		handleBomb(p, x, y);
		break;

	case OBSTACLE:
		handleObstacle(p, x, y);
		break;

	case SPRING:
		handleSpring(p, x, y);
		break;

	case DOOR:		//door to 0 (probably does not exist)
	case '1':		//door to 1
	case '2':
	case '3':       //door ??? win maybe?
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
	
	char correct = printRiddle(currentRoom); // for now, always the first riddle
	while (true) {
		if (_kbhit()) {
			char ans = _getch();
			if ('4' < ans || '0' > ans) continue;  // not in boundries
			bool wasRight = handleAnswer(correct, ans, p);
			if (wasRight) screen.setChar(x, y, currentRoom, ' ');
			cls();
			screen.draw(currentRoom);
			gameLives.draw();

			if (currentRoom == 1 && !hasTorch())
				screen.setDark();

			return;
		}
	}
}

//===========================load riddles=================================
void game_manager::loadRiddles(const char* fileName) {
	std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cerr << "Failed to open riddles file: " << fileName << std::endl;
		return;
	}
	riddles.clear();
	Riddle riddle;
	std::string line;

	while (std::getline(file, riddle.question)) {
		for (int i = 0; i < 4; ++i) {
			std::getline(file, riddle.options[i]);
		}
		std::string correct;
		std::getline(file, correct);
		if (!correct.empty())
			riddle.correctOption = correct[0];
		riddles.push_back(riddle);
	}
	file.close();
}

//=========================print riddle=================================
char game_manager::printRiddle(int index) {
	if (index < 0 || index >= riddles.size()) 
		return '\0'; // invalid index
	cls();
	std::cout << riddles[index];
	return riddles[index].correctOption;
}

//================================handle answer====================================
bool game_manager::handleAnswer(char correct, char ans, Point& p) {
	if (ans == correct) {
		std::cout << "\n\n\n\n\n\n          CORRECT!";
		Sleep(2000);
		return true;
	}
	else {
		bool isDead = removeLife();
		std::cout << "\n\n\n\n\n\n          WRONG!";
		Sleep(2000);
		if (isDead) return false;
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

//=========================handle bomb=================================
void game_manager::handleBomb(Point& p, int x, int y) {
	if (p.drawToInventory(screen, currentRoom, BOMB)) {
		screen.setChar(x, y, currentRoom, EMPTY_CELL); // remove bomb from the room
	}
}

//=========================set bomb timer=================================
void game_manager::setBombTimer(int x, int y, int roomNum) {
	bombDisposalTime = turn;
	bombX = x;
	bombY = y;
	bombRoom = roomNum;
}

//=========================activate bomb=================================
void game_manager::activateBomb(Screen& screen, int x, int y, int roomNum) {
	// explode bomb at (x,y) in roomNum
	int radius = 3; // radius of explosion
	for (int row = y - radius; row <= y + radius; row++) {
		for (int col = x - radius; col <= x + radius; col++) {
			int distX = col - x;
			int distY = row - y;
			int distanceSquared = distX * distX + distY * distY;
			bool isOuterWall = (col == 0 || col == Screen::MAX_X || row == 0 || row == Screen::MAX_Y - 3);
			if (!isOuterWall && distanceSquared <= radius * radius) { // do not destroy outer walls
				screen.setChar(col, row, roomNum, EMPTY_CELL);
			}
		}
	}
	if (playerHit(x, y, radius)) {
		removeLife();
	}
}

//===========================player hit by bomb=================================
bool game_manager::playerHit(int bombX, int bombY, int radius) {
	if (bombRoom == currentRoom){
		for (const auto& p : points) {
			int dx = p.getX() - bombX;
			int dy = p.getY() - bombY; 
			int distanceSquared = dx * dx + dy * dy;
			if (distanceSquared <= radius * radius) { // radius squared (3*3)
				return true;
			
			}
		}
	}
	return false;
}

//===========================lose life=================================
bool game_manager::removeLife() {
	if (!gameLives.loseLife()) {
		cls();
		gotoxy(30, 10);
		std::cout << "GAME OVER!";
		Sleep(2000);
		return true;
	}
	return false;
}

//===========================handle obstacle=================================
void game_manager::handleObstacle(Point& p, int x, int y) {
	Obstacle* obs = findObs(x, y);

	Point& secPyr = (p.getPlayerChar() == points[0].getPlayerChar()) ? points[1] : points[0];
	bool secPush = obs->loc(secPyr.getNextX(), secPyr.getNextY(), currentRoom);
	bool sameDir = (p.getDifX() == secPyr.getDifX() && p.getDifY() == secPyr.getDifY());

	if (secPush && sameDir) { // both players are pushing the obstacle in the same direction
		obs->tryMove(p.getDifX(), p.getDifY(), screen);
	}
}


//===========================handle spring=================================

void game_manager::handleSpring(Point& p, int x, int y)
{
	Spring* spr = findSpring(x, y);
	if (!spr)
		return;

	int idx;	//player 1 or player 2

	if (p.getPlayerChar() == points[0].getPlayerChar())
		idx = 0;
	else
		idx = 1;

	// If player is already being launched, spring tiles behave like normal obstacles/tiles.
	// (Spec: other rules still apply, but you don't "re-compress" while launched.)
	if (p.isSpringActive())
		return;

	// If this is the first spring tile for this compression, initialize compression direction toward wall
	if (charging[idx] == false) {
		int twDx = 0, twDy = 0;	//toward wall direction
		if (!spr->getTowardWallDir(screen, currentRoom, twDx, twDy))
			return;

		charging[idx] = true;
		chargeDirX[idx] = twDx;
		chargeDirY[idx] = twDy;
		chargingCount[idx] = 0;
		restoreHidden(idx); // restore any previously hidden cells for this player
	}

	// Only compress when moving toward the wall
	if (p.getDifX() == chargeDirX[idx] && p.getDifY() == chargeDirY[idx]) {
		chargingCount[idx]++;
		hideCell(idx, x, y); // visually collapse this spring char
	}
	// If the player tries to go sideways/back while still on spring tiles,
	// we do NOT release here; release is triggered centrally by tryTriggerSpringRelease().
}

Spring* game_manager::findSpring(int x, int y)
{
	for (auto& spr : springs)
		if (spr.contains(x, y, currentRoom))
			return &spr;
	return nullptr; // if not found 
}

void game_manager::springDefFromMap(int roomNum)
{
	springs.clear();

	for (int y = 0; y <= Screen::MAX_Y; y++) {
		for (int x = 0; x <= Screen::MAX_X; x++) {
			//we care only about coordinates that have a spring in them
			if (screen.getInitialChar(x, y, roomNum) != SPRING)		
				continue;
			
			//finds if spring has a connection to another springs
            bool left  = (x > 0 && screen.getInitialChar(x - 1, y, roomNum) == SPRING);
            bool right = (x < Screen::MAX_X && screen.getInitialChar(x + 1, y, roomNum) == SPRING);
            bool up    = (y > 0 && screen.getInitialChar(x, y - 1, roomNum) == SPRING);
            bool down  = (y < Screen::MAX_Y && screen.getInitialChar(x, y + 1, roomNum) == SPRING);
			int len;

			//pushes to the spring vector all adjacent springs
			if (!left && right) {
				len = 1;
				while (x + len <= Screen::MAX_X && screen.getInitialChar(x + len, y, roomNum) == SPRING)
					len++;
				springs.push_back(Spring(x, y, len, roomNum, false));
			}
			else if (!up && down) {
				len = 1;
				while (y + len <= Screen::MAX_Y && screen.getInitialChar(x, y + len, roomNum) == SPRING)
					len++;
				springs.push_back(Spring(x, y, len, roomNum, true));
			}
			else if (!left && !right && !up && !down) {
				len = 1;
				springs.push_back(Spring(x, y, len, roomNum, false));
				//what if i add here also vertical spring of len 1?
				//how do i do that :(
			}
		}
	}
}

void game_manager::hideCell(int idx, int x, int y)
{
	for (const auto& pr : hiddenCells[idx])
		if (pr.first == x && pr.second == y) 
			return;

	hiddenCells[idx].push_back({ x, y });
	screen.setChar(x, y, currentRoom, EMPTY_CELL); // hide it visually
}

void game_manager::restoreHidden(int idx)
{
	for (const auto& pr : hiddenCells[idx]) {
        screen.setChar(pr.first, pr.second, currentRoom, SPRING);
    }
    hiddenCells[idx].clear();
}

void game_manager::applyLaunchMovementIfNeeded(Point& p)
{
	if (!p.isSpringActive())
		return;

	int dx = p.getSpringDx();
	int dy = p.getSpringDy();
	int speed = p.getSpringSpeed();

	Point* otherP;

	if (p.getPlayerChar() == points[0].getPlayerChar())
		otherP = &points[1];
	else
		otherP = &points[0];

	for (int i = 0; i < speed; i++) {
		int nx = p.getX() + dx;		//new x
		int ny = p.getY() + dy;		//new y

		if (screen.isWall(nx, ny, currentRoom))
			break;

		// COLLISION: launched player hits the other player
		if (nx == otherP->getX() && ny == otherP->getY()) {
			// give other player the same launch direction and speed
			otherP->setDirection(Direction::STAY);      // ignore previous direction
			otherP->startSpringEffect(dx, dy, speed);   // starts speed for speed^2 cycles (your existing API)
			break; // do not move into the other player's cell
		}

		// BOUNCE: launched player hits another spring
		if (screen.getInitialChar(nx, ny, currentRoom) == SPRING) 
		{	
			Spring* nextSpr = findSpring(nx, ny); // spring we are about to hit
			Spring* curSpr = findSpring(p.getX(), p.getY()); // spring under current position (if any)

			// If still moving inside the same spring segment, do NOT bounce.
			if (nextSpr != nullptr && nextSpr == curSpr) {
				// continue normally (do nothing special)
			}
			else if (nextSpr != nullptr) {

				int compressCount = traverseSpringTowardWallEnd(*nextSpr, nx, ny, &p);
				int twDx = 0, twDy = 0;
				nextSpr->getTowardWallDir(screen, currentRoom, twDx, twDy);

				int launchDx = -twDx;
				int launchDy = -twDy;

				p.setDirection(Direction::STAY);
				p.startSpringEffect(launchDx, launchDy, compressCount);

				return;
			}
		}

		// ERASE CORRECTLY: redraw the underlying map char at current position
		char under = screen.charAt(p, currentRoom);
		p.draw(under);

		// move + draw player
		p.setPosition(nx, ny);
		p.draw();
	}
	p.tickSpringEffect();
}

void game_manager::tryTriggerSpringRelease(int idx, Point& p, bool canMove)
{
	if (!charging[idx])
		return;

	int dx = p.getDifX();
	int dy = p.getDifY();

	bool stay = (dx == 0 && dy == 0);

	// "attempts to change direction" (not the compression direction)
	bool changeDir = !stay && !(dx == chargeDirX[idx] && dy == chargeDirY[idx]);

	// "reaches the wall": moving toward wall but can't move
	bool hitWall = (dx == chargeDirX[idx] && dy == chargeDirY[idx] && !canMove);

	if (!(stay || changeDir || hitWall))
		return;

	int speed = chargingCount[idx];
	int launchDx = -chargeDirX[idx];
	int launchDy = -chargeDirY[idx];

	// Spring returns to original length within a single cycle
	restoreHidden(idx);

	// reset compression state
	charging[idx] = false;
	chargingCount[idx] = 0;
	chargeDirX[idx] = 0;
	chargeDirY[idx] = 0;

	if (speed <= 0)
		return;

	// prevent the normal move this cycle; movement will come from spring effect
	p.setDirection(Direction::STAY);

	// launch direction is opposite of compression direction
    p.startSpringEffect(launchDx, launchDy, speed);
}

void game_manager::resetSpringState()
{
	for (int i = 0; i < 2; i++) {
		restoreHidden(i);
		hiddenCells[i].clear();
		charging[i] = false;
		chargingCount[i] = 0;
		chargeDirX[i] = 0;
		chargeDirY[i] = 0;
	}
}

int game_manager::traverseSpringTowardWallEnd(const Spring& spr, int startX, int startY, Point* pToMove)
{
	int twDx = 0, twDy = 0;
	if (!spr.getTowardWallDir(screen, currentRoom, twDx, twDy))
		return 1;

	int count = 0;
	int cx = startX, cy = startY;

	while (true) {
		if (screen.getInitialChar(cx, cy, currentRoom) != SPRING)
			break;

		// Optional: move+draw player along the spring
		if (pToMove != nullptr) {
			char under = screen.charAt(*pToMove, currentRoom);
			pToMove->draw(under);
			pToMove->setPosition(cx, cy);
			pToMove->draw();
		}

		count++;

		int nx = cx + twDx;
		int ny = cy + twDy;

		// Stop when the spring hits the wall-end
		if (screen.isWall(nx, ny, currentRoom))
			break;

		// Or when spring tiles stop (safety)
		if (screen.getInitialChar(nx, ny, currentRoom) != SPRING)
			break;

		cx = nx;
		cy = ny;
	}

	return (count > 0) ? count : 1;
}



//===========================find obstacle=================================
Obstacle* game_manager::findObs(int x, int y) {
	for (auto& obs : obstacles)
		if (obs.loc(x, y, currentRoom))
			return &obs;
	return nullptr;
}

//===========================define obstacles=================================
void game_manager::obsDef() {
	obstacles.clear();
	// Define obstacles here if needed
	obstacles.push_back(Obstacle(36, 16, 2, 1, 1)); // obstacle 1
	for (const auto& obs : obstacles)
		obs.draw(screen);
}

//===========================handle door=================================
void game_manager::handleDoor(Point& currentPlayer, char doorNum) {
	char inv1 = '\0', inv2 = '\0';
	if (!bothPlayersAtSameChar(currentPlayer, doorNum, inv1, inv2)) {
		textAppears = printOutput("Both players must be at the door to enter !");
		return;
	}

	if (screen.searchItem(currentRoom, KEY) && doorNum - '0' > currentRoom) {		// if not all the keys been collected, the door will not open
		textAppears = printOutput("Door is locked !");
		return;
	}

	if (screen.searchItem(currentRoom, RIDDLE) && doorNum - '0' > currentRoom) {
		textAppears = printOutput("Must answer correctly to the riddle to enter!");
		return;
	}

	removeKeyAfterUse(inv1, inv2, currentPlayer); // remove key from inventory if used

	posSetAfterDoor(doorNum); // set players position after door

	currentRoom = doorNum - '0'; //update current room
	cls();
	screen.draw(currentRoom);
	gameLives.draw();

	if (currentRoom == 3)
		screen.helpLockPlayers();
}

//===========================both players at same char=================================
bool game_manager::bothPlayersAtSameChar(Point& pyr1, char checker, char& inv1, char& inv2) {
	for (const auto& player : points) {
		if (player.getPlayerChar() == pyr1.getPlayerChar()) {
			inv1 = player.checkInventory(screen, currentRoom);
			continue;
		}
		char secPlayerChar = screen.charAt(player.getX(), player.getY(), currentRoom);
		inv2 = player.checkInventory(screen, currentRoom);
		if (secPlayerChar != checker)
			return false;
	}
	return true;
}

//===========================remove key after use=================================
void game_manager::removeKeyAfterUse(char inv1, char inv2, Point& currentPlayer) {
	if (inv1 == KEY || inv2 == KEY) { // remove key from inventory if used
		if (inv1 == KEY)
			currentPlayer.drawToInventory(screen, currentRoom, EMPTY_CELL);
		else
			points[(currentPlayer.getPlayerChar() == points[0].getPlayerChar()) ? 1 : 0].drawToInventory(screen, currentRoom, EMPTY_CELL);
	}
}

//===========================set position after door=================================
void game_manager::posSetAfterDoor(char doorNum) {
	if (doorNum - '0' < currentRoom) { //go back a floor (as of now it's only possible from floor 1 to floor 0)
		points[0].setPosition(77, 20);
		points[1].setPosition(77, 21);
	}
	else {
		points[0].setPosition(2, 19);
		points[1].setPosition(2, 21);
	}
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
	gameLives.draw();
	gotoxy(35, 23);
	std::cout << "LIVE | SCORE";
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
	if (roomNum == 1 && !hasTorch())
		screen.setDark();
}