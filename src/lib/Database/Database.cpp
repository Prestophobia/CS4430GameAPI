/**
 * @file /CS4430GameAPI/src/Database/Database.cpp
 * @author Neek
 * @date Nov 16, 2017
 * @brief .
 *
 * @details .
 */

#include "lib/Database/Database.h"
#include <iostream>
using namespace sqlite_orm;

auto database = sqlite_orm::make_storage(":memory:",
		sqlite_orm::make_table("Checker_Positions",
				sqlite_orm::make_column("Position", &CheckerPos::pos,
						sqlite_orm::primary_key()),
				sqlite_orm::make_column("Color", &CheckerPos::color),
				sqlite_orm::make_column("King", &CheckerPos::king)),
		sqlite_orm::make_table("Game_State",
				sqlite_orm::make_column("ID", &GameState::id,
						sqlite_orm::primary_key()),
				sqlite_orm::make_column("Turn", &GameState::turn),
				sqlite_orm::make_column("Clock", &GameState::clock)),
		sqlite_orm::make_table("Frame_State",
				sqlite_orm::make_column("Time", &FrameState::time),
				sqlite_orm::make_column("Frame_Number",
						&FrameState::frame_number),
				sqlite_orm::make_column("Input", &FrameState::input),
				sqlite_orm::make_column("State", &FrameState::state)),
		sqlite_orm::make_table("Checker_Record",
				sqlite_orm::make_column("ID", &CheckerRecord::id,
						sqlite_orm::primary_key()),
				sqlite_orm::make_column("Position_From",
						&CheckerRecord::posFrom),
				sqlite_orm::make_column("Position_To", &CheckerRecord::posTo),
				sqlite_orm::make_column("Color", &CheckerRecord::color),
				sqlite_orm::make_column("King", &CheckerRecord::king),
				sqlite_orm::make_column("Game_Time", &CheckerRecord::time)));

void Database::initDatabase() {
	database.sync_schema();
	Database::initCheckerPositionsNew();
}

void Database::saveDatabase(std::string saveFileName,
		void (*progressFunction)(int, int), sqlite3 *originalDatabase) {
	int sqliteReturnCode; /* Function return code */
	sqlite3 *saveFilePtr; /* Database connection opened on saveFile */
	sqlite3_backup *sqliteBackupObject; /* Backup handle used to copy data */

	/* Open the database file identified by saveFile. */
	sqliteReturnCode = sqlite3_open(saveFileName.c_str(), &saveFilePtr);
	if (sqliteReturnCode == SQLITE_OK) {

		/* Open the sqlite3_backup object used to accomplish the transfer */
		sqliteBackupObject = sqlite3_backup_init(saveFilePtr, "main",
				originalDatabase, "main");
		if (sqliteBackupObject) {

			/* Each iteration of this loop copies 5 database pages from database
			 ** memoryDBPtr to the backup database. If the return value of backup_step()
			 ** indicates that there are still further pages to copy, sleep for
			 ** 250 ms before repeating. */
			do {
				sqliteReturnCode = sqlite3_backup_step(sqliteBackupObject, 5);
				if (progressFunction != 0) {
					progressFunction(
							sqlite3_backup_remaining(sqliteBackupObject),
							sqlite3_backup_pagecount(sqliteBackupObject));
				}
				if (sqliteReturnCode == SQLITE_OK
						|| sqliteReturnCode == SQLITE_BUSY
						|| sqliteReturnCode == SQLITE_LOCKED) {
					sqlite3_sleep(250);
				}
			} while (sqliteReturnCode == SQLITE_OK
					|| sqliteReturnCode == SQLITE_BUSY
					|| sqliteReturnCode == SQLITE_LOCKED);

			(void) sqlite3_backup_finish(sqliteBackupObject);
		}
		sqliteReturnCode = sqlite3_errcode(saveFilePtr);
	}

	/* Close the database connection opened on database file saveFile
	 ** and return the result of this function. */
	(void) sqlite3_close(saveFilePtr);
}

void Database::saveGame(std::string saveFileName) {
	Database::saveDatabase(saveFileName, nullptr,
			database.getConnection()->get_db());
}

/*
 * Loads the database 5 pages at a time to memory.  Database is still usable during process.
 * progressFunction (numPagesLeft, numTotalPages)
 */
void Database::loadDatabase(std::string saveFileName,
		void (*progressFunction)(int, int), sqlite3 *originalDatabase) {
	int sqliteReturnCode; /* Function return code */
	sqlite3 *saveFilePtr; /* Database connection opened on saveFile */
	sqlite3_backup *sqliteBackupObject; /* Backup handle used to copy data */

	/* Open the database file identified by saveFile. */
	sqliteReturnCode = sqlite3_open(saveFileName.c_str(), &saveFilePtr);
	if (sqliteReturnCode == SQLITE_OK) {

		/* Open the sqlite3_backup object used to accomplish the transfer */
		sqliteBackupObject = sqlite3_backup_init(originalDatabase, "main",
				saveFilePtr, "main");
		if (sqliteBackupObject) {

			/* Each iteration of this loop copies 5 database pages from database
			 ** memoryDBPtr to the backup database. If the return value of backup_step()
			 ** indicates that there are still further pages to copy, sleep for
			 ** 250 ms before repeating. */
			do {
				sqliteReturnCode = sqlite3_backup_step(sqliteBackupObject, 5);
				if (progressFunction != 0) {
					progressFunction(
							sqlite3_backup_remaining(sqliteBackupObject),
							sqlite3_backup_pagecount(sqliteBackupObject));
				}
				if (sqliteReturnCode == SQLITE_OK
						|| sqliteReturnCode == SQLITE_BUSY
						|| sqliteReturnCode == SQLITE_LOCKED) {
					sqlite3_sleep(250);
				}
			} while (sqliteReturnCode == SQLITE_OK
					|| sqliteReturnCode == SQLITE_BUSY
					|| sqliteReturnCode == SQLITE_LOCKED);

			(void) sqlite3_backup_finish(sqliteBackupObject);
		}
		sqliteReturnCode = sqlite3_errcode(saveFilePtr);
	}

	/* Close the database connection opened on database file saveFile
	 ** and return the result of this function. */
	(void) sqlite3_close(saveFilePtr);
}

void Database::loadGame(std::string saveFileName) {
	Database::loadDatabase(saveFileName, nullptr,
			database.getConnection()->get_db());
}

CheckerPos Database::getCheckerPos(int pos) {
	try {
		return database.get<CheckerPos>(pos);
	} catch (std::exception &e) {
//		perror("GetCheckerPos");
//		perror(e.what());
		return CheckerPos(-1, false, "OUT_OF_RANGE");
	}
}

void Database::updateCheckerPos(CheckerPos &checker) {
	try {
		database.update(checker);
	} catch (std::exception &e) {
		perror("UpdateCheckerPos");
		perror(e.what());
	}
}

GameState Database::getGameState() {
	try {
		return database.get<GameState>(1);
	} catch (std::exception &e) {
		perror("GetGameState");
		perror(e.what());
	}
	return GameState();
}

void Database::updateGameState(GameState &state) {
	try {
		database.update(state);
	} catch (std::exception &e) {
		perror("UpdateGameState");
		perror(e.what());
	}
}

bool Database::initCheckerPositionsNew() {
// initial checker positions
	database.drop_table("Checker_Positions");
	database.drop_table("Game_State");
	database.drop_table("Checker_Record");
	database.sync_schema();
	try {
		for (int i = 0; i < 12; ++i) {
			database.insert(CheckerPos(i, false, "White"));
		}

		for (int i = 12; i < 20; i++) {
			database.insert(CheckerPos(i, false, ""));
		}

		for (int i = 20; i < 32; ++i) {
			database.insert(CheckerPos(i, false, "Black"));
		}

		database.insert(GameState(1, "White", 0));
	} catch (std::exception &e) {
		perror("initCheckerPositionsNew");
		perror(e.what());
	}

	return true;
}

CheckerRecord Database::getCheckerRecord(int id) {
	try {
		return database.get<CheckerRecord>(id);
	} catch (std::exception &e) {
		perror("GetCheckerRecord");
		perror(e.what());
		return CheckerRecord(-1, -1, -1, false, "OUT_OF_RANGE", 0);
	}
}

void Database::insertCheckerRecord(CheckerRecord &checkerRecord) {
	try {
		database.insert(checkerRecord);
	} catch (std::exception &e) {
		perror("AddCheckerRecord");
		perror(e.what());
	}
}

void Database::updateCheckerRecord(CheckerRecord &checkerRecord) {
	try {
		database.update(checkerRecord);
	} catch (std::exception &e) {
		perror("UpdateCheckerRecord");
		perror(e.what());
	}
}

std::vector<FrameState> Database::getFrameStates(int frameNumber) {
	try {
		return database.get_all<FrameState>(
				sqlite_orm::where(
						sqlite_orm::eq(&FrameState::frame_number, frameNumber)));
	} catch (std::exception &e) {
		perror("GetFrameStates");
		perror(e.what());
	}
	return std::vector<FrameState>();
}

void Database::insertFrameState(FrameState &frameState) {
	try {
		database.insert(frameState);
	} catch (std::exception &e) {
		perror("InsertFrameState");
		perror(e.what());
	}
}

char *Database::interop_getFrameStates(int frameNumber) {
	std::vector<FrameState> frameStates = getFrameStates(frameNumber);
	std::vector<std::string> frameStateStrings;
	for (auto frameState : frameStates) {
		frameStateStrings.push_back(
				std::to_string(frameState.frame_number) + "\t"
						+ std::to_string(frameState.time) + "\t"
						+ frameState.input + "\t" + frameState.state);
	}
	char *returnFrameStateStrings = nullptr;
	int currentPosition = 0;
	for (auto stateString : frameStateStrings) {
		returnFrameStateStrings = (char *) std::realloc(returnFrameStateStrings,
				sizeof(char) * (currentPosition + stateString.size() + 1));
		std::strcpy(&returnFrameStateStrings[currentPosition],
				stateString.c_str());
		currentPosition += stateString.size() + 1;
	}
	returnFrameStateStrings = (char *) std::realloc(returnFrameStateStrings,
			sizeof(char) * (currentPosition + 1));
	returnFrameStateStrings[currentPosition] = '\0';
	return returnFrameStateStrings;
}

void Database::interop_destroyFrameStates(char *frameStates) {
	if (frameStates != 0) {
		free(frameStates);
	}
}

void Database::interop_insertFrameState(char *frameState) {
	char internalFrameStateChar[std::strlen(frameState) + 1];
	std::strcpy(internalFrameStateChar, frameState);
	FrameState realFrameState;
	char *pointer = std::strtok(internalFrameStateChar, "\t");
	realFrameState.frame_number = std::strtod(frameState, 0);
	pointer = std::strtok(0, "\t");
	realFrameState.time = std::strtol(pointer, 0, 10);
	pointer = std::strtok(0, "\t");
	realFrameState.input = pointer;
	pointer = std::strtok(0, "\t");
	realFrameState.state = pointer;
	database.insert(realFrameState);
}
