/**
 * @file /CS4430GameAPI/src/Database/Database.h
 * @author Neek
 * @date Nov 16, 2017
 * @brief .
 *
 * @details .
 */

#ifndef DATABASE_DATABASE_H_
#define DATABASE_DATABASE_H_

#include "sqlite_orm/sqlite_orm.h"

#include "Database/CheckerPos.h"
#include "Database/GameState.h"
#include "Database/CheckerRecord.h"

using namespace sqlite_orm;

class Database {

public:

	Database();

	void saveDatabase(std::string saveFileName,
			void (*progressFunction)(int, int), sqlite3 *originalDatabase);
	void saveGame(std::string saveFileName);

	void loadDatabase(std::string saveFileName,
			void (*progressFunction)(int, int), sqlite3 *originalDatabase);
	void loadGame(std::string saveFileName);

	CheckerPos getCheckerPos(int pos);
	void updateCheckerPos(CheckerPos &checker);

	GameState getGameState();
	void updateGameState(GameState &state);

	CheckerRecord getCheckerRecord(int id);
	void insertCheckerRecord(CheckerRecord &checkerRecord);
	void updateCheckerRecord(CheckerRecord &checkerRecord);

	bool initCheckerPositionsNew();
};

#endif /* DATABASE_DATABASE_H_ */
