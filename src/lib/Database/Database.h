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

#include "lib/sqlite_orm/sqlite_orm.h"

#include "include/CheckerPos.h"
#include "include/GameState.h"
#include "include/FrameState.h"
#include "include/CheckerRecord.h"

#ifdef __cplusplus
extern "C" {
#endif

namespace Database {

void initDatabase();

void saveDatabase(std::string saveFileName, void (*progressFunction)(int, int),
		sqlite3 *originalDatabase);
void saveGame(std::string saveFileName);

void loadDatabase(std::string saveFileName, void (*progressFunction)(int, int),
		sqlite3 *originalDatabase);
void loadGame(std::string saveFileName);

CheckerPos getCheckerPos(int pos);
void updateCheckerPos(CheckerPos &checker);

GameState getGameState();
void updateGameState(GameState &state);

CheckerRecord getCheckerRecord(int id);
void insertCheckerRecord(CheckerRecord &checkerRecord);
void updateCheckerRecord(CheckerRecord &checkerRecord);

std::vector<FrameState> getFrameStates(int frameNumber);
void insertFrameState(FrameState &frameState);

char *interop_getFrameStates(int frameNumber);
void interop_destroyFrameStates(char *frameStates);
void interop_insertFrameState(char *frameState);

bool initCheckerPositionsNew();

}

#ifdef __cplusplus
}
#endif

#endif /* DATABASE_DATABASE_H_ */
