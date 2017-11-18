/**
 * @file /CS4430GameAPI/src/Database/CheckerPos.h
 * @author Neek
 * @date Nov 16, 2017
 * @brief .
 *
 * @details .
 */

#include <string>

#ifndef DATABASE_CHECKERPOS_H_
#define DATABASE_CHECKERPOS_H_

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

#endif /* DATABASE_CHECKERPOS_H_ */
