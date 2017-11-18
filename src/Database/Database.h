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

//static auto database = make_storage(":memory:",
//		make_table("Checker_Positions",
//				make_column("Position", &CheckerPos::pos, primary_key()),
//				make_column("Color", &CheckerPos::color),
//				make_column("King", &CheckerPos::king)),
//		make_table("Game_State",
//				make_column("ID", &GameState::id, primary_key()),
//				make_column("Turn", &GameState::turn)),
//		make_table("Checker_Record",
//				make_column("ID", &CheckerRecord::id, primary_key()),
//				make_column("Position", &CheckerRecord::pos),
//				make_column("Color", &CheckerRecord::color),
//				make_column("King", &CheckerRecord::king),
//				make_column("Time", &CheckerRecord::time)));

class Database {

public:

//	static auto database = make_storage(":memory:",
//			make_table("Checker_Positions",
//					make_column("Position", &CheckerPos::pos, primary_key()),
//					make_column("Color", &CheckerPos::color),
//					make_column("King", &CheckerPos::king)),
//			make_table("Game_State",
//					make_column("ID", &GameState::id, primary_key()),
//					make_column("Turn", &GameState::turn)),
//			make_table("Checker_Record",
//					make_column("ID", &CheckerRecord::id, primary_key()),
//					make_column("Position", &CheckerRecord::pos),
//					make_column("Color", &CheckerRecord::color),
//					make_column("King", &CheckerRecord::king),
//					make_column("Time", &CheckerRecord::time)));

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
	bool initCheckerPositionsNew();
};

#endif /* DATABASE_DATABASE_H_ */
