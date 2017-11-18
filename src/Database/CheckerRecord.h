/**
 * @file /CS4430GameAPI/src/Database/CheckerRecord.h
 * @author Neek
 * @date Nov 16, 2017
 * @brief .
 *
 * @details .
 */

#include <string>

#ifndef DATABASE_CHECKERRECORD_H_
#define DATABASE_CHECKERRECORD_H_

#include "Database/CheckerPos.h"

class CheckerRecord {
public:
	int id = -1;
	int posFrom = 0;
	int posTo = 0;
	bool king = false;
	std::string color;
	double time = 0;

	CheckerRecord() {
	}
	CheckerRecord(int id, CheckerPos checkerFrom, CheckerPos checker,
			double time) :
			id(id), posFrom(checkerFrom.pos), posTo(checker.pos), king(
					checker.king), color(checker.color), time(time) {
	}
	CheckerRecord(int id, int posFrom, int posTo, bool king, std::string color,
			double time) :
			id(id), posFrom(posFrom), posTo(posTo), king(king), color(color), time(
					time) {
	}
};

#endif /* DATABASE_CHECKERRECORD_H_ */
