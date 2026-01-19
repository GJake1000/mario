=================================================================

-----------------------------------------------------------------------
1. Level Configuration File Format (.txt)
-----------------------------------------------------------------------
The system parses dynamic game objects from text files using the following format:

[DOOR] - Door definition and room transitions
Format: DOOR <x> <y> <target_room> <door_char> <target_x> <target_y> [conditions]
Fields:
- x, y: Door coordinates in the current room.
- target_room: The ID of the room this door leads to.
- door_char: Visual character representation.
- target_x, target_y: Player spawn coordinates in the target room.
- conditions: Requirements to open (e.g., KEY, RIDDLE, SWITCH <x> <y> <state>).
-The designer should also add the char to the correct coordinate

[SWITCH] - Switch definition
Format: SWITCH <x> <y> <initial_state>
Fields:
- initial_state: 0 for OFF, 1 for ON.
- Note: Switches are typically used as conditions for unlocking specific doors.

[DARK] - Lighting definition
Format: DARK
Description: Presence of this keyword marks the room as "Dark" (requiring a torch for visibility).

[START] - Player Spawn Points
Format: START <p1_x> <p1_y> <p2_x> <p2_y>
Description: Defines start coordinates for Player 1 and Player 2 in the specific room.

* Note to Level Designers: Ensure that (x,y) coordinates in the text file match the visual layout in the corresponding .screen file.

-----------------------------------------------------------------------
2. Gameplay Mechanics & Logic
-----------------------------------------------------------------------

A. Legend / Status Bar ('L'):
   - Dimensions: 2x80 characters.
   - Collision: The Legend is non-collidable ("transparent"). Players can pass through it if it overlays the game map.

B. Keys & Doors:
   - Key Logic: Keys are room-global. A door requiring a key will unlock if the player possesses any key found within that room.
   - Final Room (Co-op): The final level contains two distinct keys, enforcing co-op gameplay where both players must survive and reach the end to complete the game.

C. Riddles:
   - Progression: Rooms containing riddles require solving them to proceed (if linked to door conditions).
   -Can add any amount of riddles to room

-----------------------------------------------------------------------
3. Submission Notes & Version History
-----------------------------------------------------------------------


Code Refactoring & Improvements in this version:
1. Encapsulation: The `Riddle` class and related structures were moved to `private/protected` scope within `game_manager` to adhere to Information Hiding principles.
2. Code Standards: Refactored the codebase to replace Magic Numbers with named Constants/Literals.
3. Obstacle Algorithm: Fixed the obstacle movement logic. Previous versions had inconsistencies between different rooms; the current version implements a unified and correct BFS-based approach for all levels.

========================================================================