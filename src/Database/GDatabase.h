/**
 * @file /CS4430GameAPI/src/Database/GDatabase.h
 * @author Neek
 * @date Nov 18, 2017
 * @brief .
 *
 * @details .
 */

#ifndef DATABASE_GDATABASE_H_
#define DATABASE_GDATABASE_H_

#include "sqlite_orm/sqlite_orm.h"

#include "Database/CheckerPos.h"
#include "Database/GameState.h"
#include "Database/CheckerRecord.h"

//using namespace sqlite_orm;
//
//virtual class gDatabase {
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
//					make_column("Position_From", &CheckerRecord::posFrom),
//					make_column("Position_To", &CheckerRecord::posTo),
//					make_column("Color", &CheckerRecord::color),
//					make_column("King", &CheckerRecord::king),
//					make_column("Wait_Time", &CheckerRecord::time)));
//};

#endif /* DATABASE_GDATABASE_H_ */
