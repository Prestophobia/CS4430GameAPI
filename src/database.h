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
	int pos = -1;
	bool king = false;
	std::string color;

	CheckerPos() {
	}
	CheckerPos(int pos, bool king, std::string color) :
			pos(pos), king(king), color(color) {
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

class CheckerRecord {
public:
	int id = -1;
	int pos = 0;
	bool king = false;
	std::string color;
	double time = 0;

	CheckerRecord() {
	}
	CheckerRecord(int id, int pos, bool king, std::string color, double time) :
			id(id), pos(pos), king(king), color(color), time(time) {
	}
};

#endif /* DATABASE_H_ */
