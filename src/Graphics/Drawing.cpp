/**
 * @file /CS4430GameAPI/src/Graphics/Drawing.cpp
 * @author Neek
 * @date Nov 16, 2017
 * @brief .
 *
 * @details .
 */

#include "Graphics/Drawing.h"

Drawing::Drawing(Animations &ganimators, Menu &gmenu) :
		gsprites(ganimators.gsprites), gmenu(gmenu), gdata(ganimators.gdata), ganimators(
				ganimators), gdatabase(ganimators.gdatabase) {
}

void Drawing::gameDraw(sf::RenderWindow& rApp) {
	gmenu.newButt.draw();        // game reset
	gmenu.savedButt.draw();

	if (gdata.gameOn) {
		gmenu.saveGameButt.draw();
	}

	rApp.draw(gsprites.boardSprite);
	drawCheckers(rApp);
	if (ganimators.textFX) {
		rApp.draw(*gsprites.p_FXmsg);
	}

	return;
}

void Drawing::drawCheckers(sf::RenderWindow& rApp) {
// draw all checkers except the moving one
	float hSz = gdata.chSz / 2;
	int i = 0;    // for looping

	if (gdata.reset)    // animated checker display
	{
		ganimators.wh_dealPath.draw();
		ganimators.bk_dealPath.draw();
		rApp.draw(gsprites.msg);
	}

	if (gdata.gameOn)    // normal checker display
	{
		for (i = 0; i < gdata.Nanchors; ++i)
			if (i != ganimators.chObj.homeIdx)    // exclude the moving chObj
					{
				CheckerPos currentCheckerPos = gdatabase.getCheckerPos(i + 1);
				if (currentCheckerPos.color == "White") {
					if (!currentCheckerPos.king) {
						gsprites.wh_chSprite.setPosition(
								static_cast<float>(gdata.anchorArr1[i].first)
										- hSz,
								static_cast<float>(gdata.anchorArr1[i].second)
										- hSz);
						rApp.draw(gsprites.wh_chSprite);
					} else {
						gsprites.wh_kSprite.setPosition(
								static_cast<float>(gdata.anchorArr1[i].first)
										- hSz,
								static_cast<float>(gdata.anchorArr1[i].second)
										- hSz);
						rApp.draw(gsprites.wh_kSprite);
					}
				} else if (currentCheckerPos.color == "Black") {
					if (!currentCheckerPos.king) {
						gsprites.bk_chSprite.setPosition(
								static_cast<float>(gdata.anchorArr1[i].first)
										- hSz,
								static_cast<float>(gdata.anchorArr1[i].second)
										- hSz);
						rApp.draw(gsprites.bk_chSprite);
					} else {
						gsprites.bk_kSprite.setPosition(
								static_cast<float>(gdata.anchorArr1[i].first)
										- hSz,
								static_cast<float>(gdata.anchorArr1[i].second)
										- hSz);
						rApp.draw(gsprites.bk_kSprite);
					}
				}
			}

		ganimators.chObj.draw();

		GameState currentState = gdatabase.getGameState();

		// some text too
		if (!gdata.gameOver) {
			rApp.draw(gsprites.msg_Turn);
			if (currentState.turn == "White") {
				rApp.draw(gsprites.msg_Whites);
			} else {
				rApp.draw(gsprites.msg_Blacks);
			}
		}

		// draw the captured checkers
		for (i = 0; i < ganimators.Nwh_capt; ++i) {
			gsprites.wh_chSprite.setPosition(
					ganimators.wh_captX + ganimators.capt_dx * (float) i,
					ganimators.wh_captY);
			rApp.draw(gsprites.wh_chSprite);
		}
		for (i = 0; i < ganimators.Nbk_capt; ++i) {
			gsprites.bk_chSprite.setPosition(
					ganimators.bk_captX + ganimators.capt_dx * (float) i,
					ganimators.bk_captY);
			rApp.draw(gsprites.bk_chSprite);
		}

		// single animations
//		if (aniPath.inUse)
//			aniPath.draw();
		if (ganimators.kingMePath.inUse)
			ganimators.kingMePath.draw();
	}

	return;
}
