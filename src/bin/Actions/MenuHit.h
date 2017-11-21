/**
 * @file /CS4430GameAPI/src/Actions/MenuHit.h
 * @author Neek
 * @date Nov 18, 2017
 * @brief .
 *
 * @details .
 */

#ifndef ACTIONS_MENUHIT_H_
#define ACTIONS_MENUHIT_H_

#include "bin/Data/GameData.h"

#include "lib/Database/Database.h"

#include "bin/Graphics/Menu.h"
#include "bin/Graphics/Sprites.h"
#include "bin/Graphics/Animations.h"

class MenuHit {
public:
	Sprites &gsprites;
	Menu &gmenu;
	GameData &gdata;
	Animations &ganimators;

	MenuHit(Animations &ganimators, Menu &gmenu);
	bool menuHitDown(void); // returns false if file I/O error
	void menuHitUp(void);
};

#endif /* ACTIONS_MENUHIT_H_ */
