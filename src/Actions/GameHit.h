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

#include "Data/GameData.h"

#include "Database/Database.h"

#include "Graphics/Sprites.h"
#include "Graphics/Animations.h"

class GameHit {
public:
	Sprites &gsprites;
	Database &gdatabase;
	GameData &gdata;
	Animations &ganimators;

	GameHit(Animations &ganimators);
	int hitAnchor(std::string turn);
	bool fillMoveList(int hm);
	void gameHitDown();
	bool didJump(int hm_0, int hm_f, int& jumpIdx);
	void gameHitUp();
};

#endif /* ACTIONS_GAMEHIT_H_ */