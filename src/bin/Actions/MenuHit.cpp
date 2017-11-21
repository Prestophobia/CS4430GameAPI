/**
 * @file /CS4430GameAPI/src/Actions/MenuHit.cpp
 * @author Neek
 * @date Nov 18, 2017
 * @brief .
 *
 * @details .
 */

#include "bin/Actions/MenuHit.h"

MenuHit::MenuHit(Animations &ganimators, Menu &gmenu) :
		gsprites(ganimators.gsprites), gmenu(gmenu), gdata(ganimators.gdata), ganimators(
				ganimators) {

}

bool MenuHit::menuHitDown(void)    // returns false if file I/O error
		{
	bool init_game = false;

	// Get menu option chosen
	if (gdata.gameOn)
		if (gmenu.saveGameButt.hit_dn(gdata.mseX, gdata.mseY)) {
			GameState currentState = Database::getGameState();
			currentState.clock += gdata.gameClock.getElapsedTime().asSeconds();
			Database::updateGameState(currentState);
			Database::saveGame("save.db");
			gdata.gameClock.restart();
		}
	if (gmenu.newButt.hit_dn(gdata.mseX, gdata.mseY)) {
		init_game = true;
		Database::initCheckerPositionsNew();
		gdata.gameClock.restart();
	}
	if (gmenu.savedButt.hit_dn(gdata.mseX, gdata.mseY)) {
		init_game = true;
		Database::loadGame("save.db");
		gdata.gameClock.restart();
	}

	// Reset game
	if (init_game) {

		// Count checker for each side
		// TODO use COUNT SQL command with SELECT on color
		int i = 0;
		int num_white = 0;
		int num_black = 0;
		bool whiteFound = false;
		int whiteIndex = 32;
		for (i = 0; i < 32; ++i) {
			CheckerPos currentCheckerPos = Database::getCheckerPos(i + 1);
			if (currentCheckerPos.color == "White") {
				if (whiteFound == false) {
					whiteFound = true;    // find 1st white checker
					whiteIndex = i;
				}
				num_white++;
			} else if (currentCheckerPos.color == "Black") {
				num_black++;
			}
		}

		// Set game flags
		gdata.reset = true;
		gdata.gameOn = gdata.gameOver = false;

		// Reset animations
		ganimators.initPathLegs();
		ganimators.chObj.homeIdx = whiteIndex;
		ganimators.chObj.docked = false;
		ganimators.chObj.snap();
		ganimators.chObj.pSprite = &gsprites.wh_chSprite;
		ganimators.animateKing = ganimators.justKinged = false;
		ganimators.wh_dealPath.reset(true, 0);
		ganimators.bk_dealPath.reset(true, 0);
		ganimators.Nwh_capt = 12 - num_white;
		ganimators.Nbk_capt = 12 - num_black;
//		ganimators.textFX = true;
//		ganimators.textFXdelay = 30;
//		ganimators.textExpand(gsprites.msg_WELCOME, 1.0f, 7.0f, 20, true);
//		ganimators.textFade(gsprites.msg_WELCOME, 255, 1, 20, true);
	}

	return true;
}

void MenuHit::menuHitUp(void) {
	gmenu.newButt.hit_up();
	gmenu.savedButt.hit_up();
	if (gdata.gameOn)
		gmenu.saveGameButt.hit_up();

	return;
}
