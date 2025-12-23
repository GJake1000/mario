#pragma once
#include "auxThing.h"


class Point;

class Screen {
public:
	static constexpr int MAX_X = 79;
	static constexpr int MAX_Y = 24;
	static constexpr int NUM_OF_ROOMS = 3; //2 rooms + final end room
	static const char EMPTY_ROW[];
private:
	static constexpr char initialRooms[NUM_OF_ROOMS][MAX_Y + 1][MAX_X + 2] = 
	{
	   {
			// =====================================FIERST ROOM=====================================	
			//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
				"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
				"W    W                     W           W    !     D    W                       W", // 1
				"W  WWW                     W           W          D    W    WWWWWWWWWWWW       W", // 2
				"W           WWWWWWW    K   W            WWWWWWWWWWW    W    W           W      W", // 3
				"W  WW       W  /  W        WWWWWWWWWW             W    W    W   W       W      W", // 4
				"W   W       W     WWWWWWWWWW            W         W    W    W   W       W  @   W", // 5
				"W   W       W          W     WWW        W         W    W    W   W   WWWWWWWWWWWW", // 6
				"WWWWW   WWWWWWWWWWW    W         W      W         W    W    W   W              W", // 7
				"W#      W              W         W      W         W         W   WWWWWWWWWWWW   W", // 8
				"W#  WWWWW              WWWWWW    WWWWWWWWWWWWWWWWWWWWW          W              W", // 9
				"W   W   W              W         W          W      W            W              W", // 10
				"W   W   WWWWWWWWWWW    WWWWWW               W      WWWWWWWWWWWWWWWW    WWWWW   W", // 11
				"W   W   W    W                                                             W   W", // 12
				"W       W    WWWWWWWWWWWWWWWWWWWWWWWW       WWWWWWWWWWWWWWWWWWWWWWWWWW     W   W", // 13
				"W       W####                      ?                             W         W   W", // 14
				"W       W              WWWWWWWWWWWWWWWWWWWWWWWWWWWW          W   W         W   W", // 15
				"W       WWWWWWWWWWW   #W#             ##W         W          W   WWWWWWW   W   W", // 16
				"W                     #W    W   W       W   WWWWWWWWWWW      W   W         W   W", // 17
				"WWWWWWWWWW   WWWWWWWWWWW    #   WWWW    W   W                W   W         W   W", // 18
				"W##               W         W   W       W   WWW   WWWWWWWWWWWW   W             W", // 19
				"WWWW            #WW    #       WWW      W   W                W                1W", // 20
				"W####                       ####W#          W                W                1W", // 21
				"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 22
				"                                                                                ", // 23
				"Player &:                             INVENTORY                   Player $:     ", // 24
		},
		{

			// =====================================SECOND ROOM=====================================
			//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
				"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
				"W     W                                                                   W#W#WW", // 2
				"WWWWWWW                WWWWWWWWWWWWWWWWWWWWW                        WW      W#WW", // 1
				"W                      WW      WWWWWWWWWWWWW             WWWW       WW        WW", // 3
				"W                      WW  WW  W         WWW             W     WW   WW        WW", // 4
				"W                      WW  WW  W  !   W  WWWWWWWWWWWWWWWWW   WWWW   WW         W", // 5
				"W    WWWWWWWWWW            WW  W      W  DDD                WWWWW   WW         W", // 6
				"W    WWWWWWWWWWWWWWWW  WW  WW  WWWWWWWW  WWW           WWWWW   WW   WW         W", // 7
				"W    WWWWWWWWWWWWWWWW  WW                WWW           WWWW    WW   WW         W", // 8
				"W    WWWWWWWWWW    DD  WWWWWWWWWWWWWWWWWWWWW       WWWWWWWW    WW   WW         W", // 9
				"W        WWW       WWWWWWWWWWWWWWWWWWWWWWWWW       WWWWWWWW    WW   WW         W", // 10
				"W        WWW       WWWW         WW      WWW            WWWW    WW   WW         W", // 11
				"W  WWW   WWW              WW    WW   K  WWW   WWWWWW   WWWW    WW   WW         W", // 12
				"W  WWW   WWW       WWWW   WW    WW      WWW   WWWWWW   WWWW    WW   WW         W", // 13
				"W  WWW             WWWW   WW    WW      DDD            WWWW    WW   WW         W", // 14
				"W  WWW                    WW    WW      WWWWWWWWW      WWWW    WW              W", // 15
				"WWWWWWWWWWWWWW     WWWW   WW    WWWW  WWWWW  ?  W      WWWW    WW   WDDDDDDDDDDW", // 16
				"WWWWWWWWWWWWWW     WWWW   WW            WWW  W  W   WWWWWWWWWWWWW   WW         W", // 17
				"W        /  WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW  W  W   WWWWWWWWWWWWW  #WWW        W", // 18
				"W    WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW  W  W                  #WWWWW    **W", // 19
				"W0          WWWWW             WWWWWWWWW     #W  WWWWWWWWWWWWWWWWW  #WWWWWW   *2W", // 20
				"W0      WW          WWWWWWW                 #W                     #WWWWWWW  *2W", // 21
				"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 22
				"                                                                                ", // 23
				"Player &:                            INVENTORY                   Player $:      ", // 24
		},
		{
			// =====================================FINAL ROOM=====================================
			//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
				"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
				"W                                                                              W", // 1
				"W                                                                              W", // 2
				"W  WWWWWW  WWWWW  W   W  WWWWW  W           W      WWWWW  W   W  WWWWW  W      W", // 3
				"W  W         W    WW  W  W   W  W           W      W      W   W  W      W      W", // 5
				"W  WWWWW     W    W W W  WWWWW  W           W      WWWW   W   W  WWWW   W      W", // 4
				"W  W         W    W  WW  W   W  W           W      W       W W   W      W      W", // 6
				"W  W       WWWWW  W   W  W   W  WWWWW       WWWWW  WWWWW    W    WWWWW  WWWWW  W", // 7
				"W                                                                              W", // 8
				"W                                                                              W", // 9
				"W                                                                              W", // 10
				"W                                                                              W", // 11
				"W                                                                              W", // 12
				"W                                                                              W", // 13
				"W                                                                              W", // 14
				"W                                                                              W", // 15
				"W                                                                              W", // 16
				"W                                                                              W", // 17
				"W W                                                                            W", // 18
				"WW W                                                                           W", // 19
				"W W                                                                            W", // 20
				"WW W                                                                           W", // 21
				"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 22
				"                                                                                ", // 23
				"Player &:                            INVENTORY                   Player $:      ", // 24
		}
	};

	char rooms[NUM_OF_ROOMS][MAX_Y + 1][MAX_X + 2];

public:
	void colorItem(char item) const;
	Screen();
	void resetRoom();
	void resetRoom(int roomNum);
	char charAt(const Point& p, int roomNum) const;
	char charAt(int x, int y, int roomNum) const;
	void draw(int roomNum) const;
	bool isWall(int x, int y, int roomNum) const;
	void setChar(int x, int y, int roomNum, char ch);
	void setDark() const;
	void helpLockPlayers() const;
	char getInitialChar(int x, int y, int roomNum) const;
	bool searchItem(int roomNum, char item) const;
};