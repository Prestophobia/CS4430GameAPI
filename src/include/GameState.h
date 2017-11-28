/**
 * @file /CS4430GameAPI/src/Database/GameState.h
 * @author Neek
 * @date Nov 16, 2017
 * @brief .
 *
 * @details .
 */

#ifndef DATABASE_GAMESTATE_H_
#define DATABASE_GAMESTATE_H_

#include <string>

class GameState {
public:
	int id = -1;
	std::string turn;
	double clock = 0;

	GameState() {
	}
	GameState(int id, std::string turn, double clock) :
			id(id), turn(turn), clock(clock) {
	}
};

#endif /* DATABASE_GAMESTATE_H_ */
