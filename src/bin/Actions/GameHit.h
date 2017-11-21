/**
 * @file /CS4430GameAPI/src/Actions/GameHit.h
 * @author Neek
 * @date Nov 18, 2017
 * @brief .
 *
 * @details .
 */

#ifndef ACTIONS_GAMEHIT_H_
#define ACTIONS_GAMEHIT_H_

#include "bin/Data/GameData.h"

#include "lib/Database/Database.h"

#include "bin/Graphics/Sprites.h"
#include "bin/Graphics/Animations.h"

class GameHit {
private:
	int hitAnchor(std::string turn);
	bool fillMoveList(int hm);
	bool didJump(int hm_0, int hm_f, int& jumpIdx);

public:
	Sprites &gsprites;
	GameData &gdata;
	Animations &ganimators;

	GameHit(Animations &ganimators);
	void gameHitDown();
	void gameHitUp();
};

#endif /* ACTIONS_GAMEHIT_H_ */
