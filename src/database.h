/*
 * database.h
 *
 *  Created on: Oct 22, 2017
 *      Author: Neek
 */

#include <string>

#ifndef DATABASE_H_
#define DATABASE_H_

class CheckerPos {
public:
	int id = -1;
	int pos = 0;
	bool king = false;
	std::string color;

	CheckerPos() {
	}
	CheckerPos(int id, int pos, bool king, std::string color) :
			id(id), pos(pos), king(king), color(color) {
	}
};

class GameState {
public:
	int id = -1;
	std::string turn;

	GameState() {
	}
	GameState(int id, std::string turn) :
			id(id), turn(turn) {
	}
	;
};

#endif /* DATABASE_H_ */
