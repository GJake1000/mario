#include "fileHandler.h"
#include "auxThing.h"

fileHandler::fileHandler() {
	p1keys = STARDARD_PLAYER_1_KEYS;
	p2keys = STARDARD_PLAYER_2_KEYS;
	riddleFile = "riddles.txt";
	riddleScore = 150;
	bombTimer = 5;
}

bool fileHandler::loadGlobal(const std::string& fName) {
	std::ifstream file(fName);
	if (!file.is_open()) {
		std::cerr << "Failed to open global config file: " << fName << std::endl;
		return false;
	}
	std::string line;
	while (file >> line) {
		if (line == "KEYS_P1")
			file >> p1keys;
		else if (line == "KEYS_P2")
			file >> p2keys;
		else if (line == "RIDDLE_FILE")
			file >> riddleFile;
		else if (line == "RIDDLE_SCORE")
			file >> riddleScore;
		else if (line == "BOMB_TIMER")
			file >> bombTimer;
		else if (line == "BOMB_RADIUS")
			file >> bombRadius;
		else if (line == "INITIAL_LIVES")
			file >> initialLives;
	}
	file.close();
	return true;
}

bool fileHandler::loadRiddles() {
	std::ifstream file(riddleFile);
	if (!file.is_open())
		return false;
	rids.clear();
	Riddle rid;
	std::string line;
	while (std::getline(file, rid.question)) {
		if (rid.question.empty())
			continue;
		std::string correct;
		std::getline(file, correct);
		if (!correct.empty())
			rid.correctOption = correct[0];
		rids.push_back(rid);
	}
	file.close();
	return true;
}

const Riddle& fileHandler::getRid(int idx) const {
	static Riddle emptyRid;
	if (idx >= 0 && idx < rids.size())
		return rids[idx];
	return emptyRid;
}

std::vector<Obstacle> fileHandler::createObstacles(const Screen& screen, int roomNum) {
	std::vector<Obstacle> obstacles;
	const auto& obsList = screen.getObstacleData(roomNum);
	for (const auto& obs : obsList) {
		obstacles.push_back(Obstacle(obs.x, obs.y, obs.width, obs.height, roomNum, Color::brown));
	}
	return obstacles;
}