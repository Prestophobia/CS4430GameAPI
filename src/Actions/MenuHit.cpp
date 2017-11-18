/**
 * @file /CS4430GameAPI/src/Actions/MenuHit.cpp
 * @author Neek
 * @date Nov 18, 2017
 * @brief .
 *
 * @details .
 */

#include "Actions/MenuHit.h"

MenuHit::MenuHit(Animations &ganimators, Menu &gmenu) :
		gsprites(ganimators.gsprites), gmenu(gmenu), gdatabase(
				ganimators.gdatabase), gdata(
				ganimators.gdata), ganimators(ganimators) {

}

bool MenuHit::menuHitDown(void)    // returns false if file I/O error
		{
	bool init_game = false;

	if (gdata.gameOn)
		if (gmenu.saveGameButt.hit_dn(gdata.mseX, gdata.mseY)) {
			gdatabase.saveGame("save.db");
		}
	if (gmenu.newButt.hit_dn(gdata.mseX, gdata.mseY)) {
		init_game = true;
		gdatabase.initCheckerPositionsNew();
	}
	if (gmenu.savedButt.hit_dn(gdata.mseX, gdata.mseY)) {
		init_game = true;
		gdatabase.loadGame("save.db");
	}

	if (init_game)    // resets game
	{
		init_game = false;

		ganimators.initPathLegs();
		int i = 0;
		int num_white = 0;
		int num_black = 0;
		bool whiteFound = false;
		int whiteIndex = 32;
		for (i = 0; i < 32; ++i) {
			CheckerPos currentCheckerPos = gdatabase.getCheckerPos(i + 1);
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
		ganimators.chObj.homeIdx = whiteIndex;
		ganimators.chObj.docked = false;
		ganimators.chObj.snap();
		ganimators.chObj.pSprite = &gsprites.wh_chSprite;
		gdata.reset = true;
		gdata.gameOn = gdata.gameOver = false;
		ganimators.animateKing = ganimators.justKinged = false;
		ganimators.wh_dealPath.reset(true, 0);
		ganimators.bk_dealPath.reset(true, 0);
		ganimators.Nwh_capt = 12 - num_white;
		ganimators.Nbk_capt = 12 - num_black;
		//        textFX = true;
		//        textFXdelay = 30;
		//        textExpand( msg_WELCOME, 1.0f, 7.0f, 20, true );
		//        textFade( msg_WELCOME, 255, 1, 20, true );
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
