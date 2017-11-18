/**
 * @file /CS4430GameAPI/src/Database/GameState.h
 * @author Neek
 * @date Nov 16, 2017
 * @brief .
 *
 * @details .
 */

#include <string>

#ifndef DATABASE_GAMESTATE_H_
#define DATABASE_GAMESTATE_H_

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

#endif /* DATABASE_GAMESTATE_H_ */
