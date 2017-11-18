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

#include "Data/GameData.h"

#include "Database/Database.h"

#include "Graphics/Menu.h"
#include "Graphics/Sprites.h"
#include "Graphics/Animations.h"

class MenuHit {
public:
	Sprites &gsprites;
	Menu &gmenu;
	Database &gdatabase;
	GameData &gdata;
	Animations &ganimators;

	MenuHit(Animations &ganimators, Menu &gmenu);
	bool menuHitDown(void); // returns false if file I/O error
	void menuHitUp(void);
};

#endif /* ACTIONS_MENUHIT_H_ */
