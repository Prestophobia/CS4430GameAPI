/**
 * @file /CS4430GameAPI/src/Actions/GameHit.cpp
 * @author Neek
 * @date Nov 18, 2017
 * @brief .
 *
 * @details .
 */

#include "Actions/GameHit.h"

GameHit::GameHit(Animations &ganimators) :
		gsprites(ganimators.gsprites), gdatabase(ganimators.gdatabase), gdata(
				ganimators.gdata), ganimators(ganimators) {

}

// finds which anchor was hit. Returns anchor index if valid anchor was hit. Returns -1 if not.
int GameHit::hitAnchor(std::string turn) // global turn not used as other value may be considered
		{
	int hSz = gdata.chSz / 2;
	int idx = 0;
	int ret = -1;

	for (idx = 0; idx < gdata.Nanchors; ++idx) {
		if (gdata.mseX < gdata.anchorArr1[idx].first - hSz)
			continue;
		if (gdata.mseX > gdata.anchorArr1[idx].first + hSz)
			continue;
		if (gdata.mseY < gdata.anchorArr1[idx].second - hSz)
			continue;
		if (gdata.mseY > gdata.anchorArr1[idx].second + hSz)
			continue;
		break;    // because anchor idx was hit
	}
	CheckerPos currentCheckerPos = gdatabase.getCheckerPos(idx + 1);
	if (idx == 32) {
		ret = -1;    // all anchors were missed
	} else if (turn == currentCheckerPos.color) {
		ret = idx;
	}
	return ret;
}

// returns true if a jump may be made
bool GameHit::fillMoveList(int hm) // called when a checker is grabbed for a move
		{
	gdata.Nmoves = 0;
	CheckerPos currentCheckerPos = gdatabase.getCheckerPos(hm + 1);
	GameState currentState = gdatabase.getGameState();

	if (currentCheckerPos.color != "") {
		std::string opCol;
		if (currentState.turn == "White") {
			opCol = "Black";
		} else {
			opCol = "White";
		}
		try {
			if (currentState.turn == "White" || currentCheckerPos.king) // white or king
					{
//        if( hm < 28 )// not in bottom row
				if (hm < 28 && !gdata.jumpMade)    // not in bottom row
						{
					if (hm % 8 == 3 || hm % 8 == 4)    // is edge position
							{
						auto checkCheckerPos4 = gdatabase.getCheckerPos(
								hm + 1 + 4);
						if (checkCheckerPos4.color == "") {
							gdata.moveIdxList[gdata.Nmoves++] = hm + 4;
						}
					} else if ((hm / 4) % 2)    // odd row ( 1, 3, 5 )
							{
						auto checkCheckerPos3 = gdatabase.getCheckerPos(
								hm + 1 + 3);
						auto checkCheckerPos4 = gdatabase.getCheckerPos(
								hm + 1 + 4);
						if (checkCheckerPos3.color == "") {
							gdata.moveIdxList[gdata.Nmoves++] = hm + 3;
						}
						if (checkCheckerPos4.color == "") {
							gdata.moveIdxList[gdata.Nmoves++] = hm + 4;
						}
					} else    // even row ( 0, 2, 4, 6 )
					{
						auto checkCheckerPos4 = gdatabase.getCheckerPos(
								hm + 1 + 4);
						auto checkCheckerPos5 = gdatabase.getCheckerPos(
								hm + 1 + 5);
						if (checkCheckerPos4.color == "") {
							gdata.moveIdxList[gdata.Nmoves++] = hm + 4;
						}
						if (checkCheckerPos5.color == "") {
							gdata.moveIdxList[gdata.Nmoves++] = hm + 5;
						}
					}
				}
				if (hm < 24)    // check for jumps
						{
					if (hm % 8 == 3)    // on right edge
							{
						auto checkCheckerPos4 = gdatabase.getCheckerPos(
								hm + 1 + 4);
						auto checkCheckerPos7 = gdatabase.getCheckerPos(
								hm + 1 + 7);
						if (checkCheckerPos4.color == opCol
								&& checkCheckerPos7.color == "") { // a jump over hm+4 to hm+7 can be made
							gdata.moveIdxList[gdata.Nmoves++] = hm + 7;
						}
					} else if (hm % 8 == 4)    // on left edge
							{
						auto checkCheckerPos4 = gdatabase.getCheckerPos(
								hm + 1 + 4);
						auto checkCheckerPos9 = gdatabase.getCheckerPos(
								hm + 1 + 9);
						if (checkCheckerPos4.color == opCol
								&& checkCheckerPos9.color == "") { // a jump over hm+4 to hm+7 can be made
							gdata.moveIdxList[gdata.Nmoves++] = hm + 9;
						}
					} else if ((hm / 4) % 2)    // odd row ( 1, 3, 5 )
							{
						auto checkCheckerPos3 = gdatabase.getCheckerPos(
								hm + 1 + 3);
						auto checkCheckerPos7 = gdatabase.getCheckerPos(
								hm + 1 + 7);
						if (checkCheckerPos3.color == opCol
								&& checkCheckerPos7.color == "") {
							gdata.moveIdxList[gdata.Nmoves++] = hm + 7;
						}
						auto checkCheckerPos4 = gdatabase.getCheckerPos(
								hm + 1 + 4);
						auto checkCheckerPos9 = gdatabase.getCheckerPos(
								hm + 1 + 9);
						if (checkCheckerPos4.color == opCol
								&& checkCheckerPos9.color == "") {
							gdata.moveIdxList[gdata.Nmoves++] = hm + 9;
						}
					} else    // even row ( 0, 2, 4 )
					{
						auto checkCheckerPos4 = gdatabase.getCheckerPos(
								hm + 1 + 4);
						auto checkCheckerPos7 = gdatabase.getCheckerPos(
								hm + 1 + 7);
						if (checkCheckerPos4.color == opCol
								&& checkCheckerPos7.color == "") {
							gdata.moveIdxList[gdata.Nmoves++] = hm + 7;
						}
						auto checkCheckerPos5 = gdatabase.getCheckerPos(
								hm + 1 + 5);
						auto checkCheckerPos9 = gdatabase.getCheckerPos(
								hm + 1 + 9);
						if (checkCheckerPos5.color == opCol
								&& checkCheckerPos9.color == "") {
							gdata.moveIdxList[gdata.Nmoves++] = hm + 9;
						}
					}
				}    // end check for jumps
			}
			if (currentState.turn == "Black" || currentCheckerPos.king) // black or king
					{
				//     if( hm >3 )// not in top row
				if (hm > 3 && !gdata.jumpMade)    // not in top row
						{
					if (hm % 8 == 3 || hm % 8 == 4)    // is edge position
							{
						auto checkCheckerPos4 = gdatabase.getCheckerPos(
								hm + 1 - 4);
						if (checkCheckerPos4.color == "") {
							gdata.moveIdxList[gdata.Nmoves++] = hm - 4;
						}
					} else if ((hm / 4) % 2)    // odd row ( 1, 3, 5, 7 )
							{
						auto checkCheckerPos4 = gdatabase.getCheckerPos(
								hm + 1 - 4);
						auto checkCheckerPos5 = gdatabase.getCheckerPos(
								hm + 1 - 5);
						if (checkCheckerPos4.color == "") {
							gdata.moveIdxList[gdata.Nmoves++] = hm - 4;
						}
						if (checkCheckerPos5.color == "") {
							gdata.moveIdxList[gdata.Nmoves++] = hm - 5;
						}
					} else    // even row ( 2, 4, 6 )
					{
						auto checkCheckerPos3 = gdatabase.getCheckerPos(
								hm + 1 - 3);
						auto checkCheckerPos4 = gdatabase.getCheckerPos(
								hm + 1 - 4);
						if (checkCheckerPos3.color == "") {
							gdata.moveIdxList[gdata.Nmoves++] = hm - 3;
						}
						if (checkCheckerPos4.color == "") {
							gdata.moveIdxList[gdata.Nmoves++] = hm - 4;
						}
					}
				}
				if (hm > 7)    // check for jumps
						{
					if (hm % 8 == 3)    // on right edge
							{
						auto checkCheckerPos4 = gdatabase.getCheckerPos(
								hm + 1 - 4);
						auto checkCheckerPos9 = gdatabase.getCheckerPos(
								hm + 1 - 9);
						if (checkCheckerPos4.color == opCol
								&& checkCheckerPos9.color == "") { // a jump over hm+4 to hm+7 can be made
							gdata.moveIdxList[gdata.Nmoves++] = hm - 9;
						}
					} else if (hm % 8 == 4)    // on left edge
							{
						auto checkCheckerPos4 = gdatabase.getCheckerPos(
								hm + 1 - 4);
						auto checkCheckerPos7 = gdatabase.getCheckerPos(
								hm + 1 - 7);
						if (checkCheckerPos4.color == opCol
								&& checkCheckerPos7.color == "") { // a jump over hm+4 to hm+7 can be made
							gdata.moveIdxList[gdata.Nmoves++] = hm - 7;
						}
					} else if ((hm / 4) % 2)    // odd row ( 3, 5, 7 )
							{
						auto checkCheckerPos4 = gdatabase.getCheckerPos(
								hm + 1 - 4);
						auto checkCheckerPos7 = gdatabase.getCheckerPos(
								hm + 1 - 7);
						if (checkCheckerPos4.color == opCol
								&& checkCheckerPos7.color == "") {
							gdata.moveIdxList[gdata.Nmoves++] = hm - 7;
						}
						auto checkCheckerPos5 = gdatabase.getCheckerPos(
								hm + 1 - 5);
						auto checkCheckerPos9 = gdatabase.getCheckerPos(
								hm + 1 - 9);
						if (checkCheckerPos5.color == opCol
								&& checkCheckerPos9.color == "") {
							gdata.moveIdxList[gdata.Nmoves++] = hm - 9;
						}
					} else    // even row ( 0, 2, 4 )
					{
						auto checkCheckerPos3 = gdatabase.getCheckerPos(
								hm + 1 - 3);
						auto checkCheckerPos7 = gdatabase.getCheckerPos(
								hm + 1 - 7);
						if (checkCheckerPos3.color == opCol
								&& checkCheckerPos7.color == "") {
							gdata.moveIdxList[gdata.Nmoves++] = hm - 7;
						}
						auto checkCheckerPos4 = gdatabase.getCheckerPos(
								hm + 1 - 4);
						auto checkCheckerPos9 = gdatabase.getCheckerPos(
								hm + 1 - 9);
						if (checkCheckerPos4.color == opCol
								&& checkCheckerPos9.color == "") {
							gdata.moveIdxList[gdata.Nmoves++] = hm - 9;
						}
					}
				}    // end check for jumps
			}
		} catch (std::exception &e) {
//			perror("fillMoveList: ");
//			perror(e.what());
		}
	}

// check if any jump moves were found
	for (int i = 0; i < gdata.Nmoves; ++i) {
		//        for white                           for black
		if ((gdata.moveIdxList[i] - hm > 5)
				|| (gdata.moveIdxList[i] - hm < -5)) { // jump found
			return true;
		}
	}

	return false;    // no jumps found
}

void GameHit::gameHitDown() {
	int idx = -1;

	GameState currentState = gdatabase.getGameState();

	if (gdata.jumpMade && gdata.canJump)        // handle multi-jump
			{
		if (ganimators.chObj.grab(gdata.mseX, gdata.mseY)) {
			return;        // moveList already filled after 1st jump
		}

		idx = hitAnchor(currentState.turn); // see if other color anchor was hit
		if (idx != -1) // it was!
				{
			// change turn

			if (currentState.turn == "Black") {
				currentState.turn = "White";
			} else {
				currentState.turn = "Black";
			}
			gdatabase.updateGameState(currentState);
			gdata.jumpMade = gdata.canJump = false;
		}
	} else {
		// normal treatment
		idx = hitAnchor(currentState.turn);
	}

// normal case
	if (idx != -1)        // a valid anchor was hit
			{
		gdata.jumpMade = false;
		fillMoveList(idx);
		if (gdata.Nmoves > 0)        // move is possible from anchor idx
				{
			// relocate chObj to anchor idx
			ganimators.chObj.homeIdx = idx;
			ganimators.chObj.docked = false;
			ganimators.chObj.snap();
			ganimators.chObj.grab(gdata.mseX, gdata.mseY);
			CheckerPos currentCheckerPos;
			try {
				currentCheckerPos = gdatabase.getCheckerPos(idx + 1);
				if (currentCheckerPos.color == "White") {
					if (!currentCheckerPos.king) {
						ganimators.chObj.pSprite = &gsprites.wh_chSprite;
					} else {
						ganimators.chObj.pSprite = &gsprites.wh_kSprite;
					}
				} else if (currentCheckerPos.color == "Black") {
					if (!currentCheckerPos.king) {
						ganimators.chObj.pSprite = &gsprites.bk_chSprite;
					} else {
						ganimators.chObj.pSprite = &gsprites.bk_kSprite;
					}
				}
			} catch (std::exception &e) {
				perror("gameHitDown: ");
				perror(e.what());
			}
		}
	}

	return;
}

bool GameHit::didJump(int hm_0, int hm_f, int& jumpIdx) // returns true if a jump was made and assigns jumpIdx = space# jumped
		{
//     moved up or down only 1 row
	if ((hm_f - hm_0 >= -5) && (hm_f - hm_0 <= 5))
		return false;    // no jump was made

//    bool isKing = checkerPos[hm_f] == 'W' || checkerPos[hm_f] == 'B';

	if (hm_f - hm_0 > 5)    //  jump downward
			{
		if ((hm_0 / 4) % 2)    // moved from odd row
				{
			if (hm_f - hm_0 == 7)
				jumpIdx = hm_0 + 3;
			else
				jumpIdx = hm_0 + 4;
		} else    // moved from even row
		{
			if (hm_f - hm_0 == 7)
				jumpIdx = hm_0 + 4;
			else
				jumpIdx = hm_0 + 5;
		}
		return true;
	}

	if (hm_f - hm_0 < -5)    //  jump upward
			{
		if ((hm_0 / 4) % 2)    // moved from odd row
				{
			if (hm_0 - hm_f == 7)
				jumpIdx = hm_f + 3;
			else
				jumpIdx = hm_f + 4;
		} else    // moved from even row
		{
			if (hm_0 - hm_f == 7)
				jumpIdx = hm_f + 4;
			else
				jumpIdx = hm_f + 5;
		}
		return true;
	}
	return false;    // NEW - this line should never be reached!
}

void GameHit::gameHitUp() {

	int hm_0 = ganimators.chObj.homeIdx;
	ganimators.chObj.release(gdata.moveIdxList, gdata.Nmoves);
	ganimators.chObj.snap();
	int hm_f = ganimators.chObj.homeIdx;
	if (hm_f != hm_0) {

		GameState currentState = gdatabase.getGameState();

		// Move checker in database
		CheckerPos checkerPos = gdatabase.getCheckerPos(hm_f + 1);
		CheckerPos checkerPosFrom = gdatabase.getCheckerPos(hm_0 + 1);

		checkerPos.color = checkerPosFrom.color;
		checkerPos.king = checkerPosFrom.king;

		checkerPosFrom.color = "";
		checkerPosFrom.king = false;

		gdatabase.updateCheckerPos(checkerPosFrom);
		gdatabase.updateCheckerPos(checkerPos);

		// Add record of move
		CheckerRecord newRecord(-1, checkerPosFrom, checkerPos,
				currentState.clock
						+ gdata.gameClock.getElapsedTime().asSeconds());
		gdatabase.insertCheckerRecord(newRecord);
		gdata.lastMoveClock.restart();

		float hSz = gdata.chSz / 2;

		// Check for king; King me if necessary
		ganimators.justKinged = false;
		float xf = (float) (gdata.anchorArr1[hm_f].first) - hSz;
		float yf = (float) (gdata.anchorArr1[hm_f].second) - hSz;
		if (currentState.turn == "White" && hm_f > 27
				&& checkerPos.color == "White" && !checkerPos.king) {

			// Update database
			checkerPos.king = true;
			gdatabase.updateCheckerPos(checkerPos);

			// Update animation
			*ganimators.kingMePath.ppSprite = &gsprites.wh_chSprite;
			ganimators.p_kingMePathLeg->INIT(
					ganimators.wh_captX
							+ (ganimators.Nwh_capt - 1) * ganimators.capt_dx,
					ganimators.wh_captY, xf, yf, 20.0f);
			ganimators.justKinged = true;

		} else if (currentState.turn == "Black" && hm_f < 4
				&& checkerPos.color == "Black" && !checkerPos.king) {

			// Update database
			checkerPos.king = true;
			gdatabase.updateCheckerPos(checkerPos);

			// Update animation
			*ganimators.kingMePath.ppSprite = &gsprites.bk_chSprite;
			ganimators.p_kingMePathLeg->INIT(
					ganimators.bk_captX
							+ (ganimators.Nbk_capt - 1) * ganimators.capt_dx,
					ganimators.bk_captY, xf, yf, 20.0f);
			ganimators.justKinged = true;
		}

		// Perform jump
		int jumpIdx = 0;
		gdata.jumpMade = didJump(hm_0, hm_f, jumpIdx);
		if (gdata.jumpMade) {

			CheckerPos jumpedCheckerPos;
			jumpedCheckerPos = gdatabase.getCheckerPos(jumpIdx + 1);

			// Setup capture animation
			// TODO Make capture animation work
			if (jumpedCheckerPos.color == "White" && !jumpedCheckerPos.king) {
				ganimators.colorCapt = 'w';
			} else if (jumpedCheckerPos.color == "White"
					&& jumpedCheckerPos.king) {
				ganimators.colorCapt = 'W';
			} else if (jumpedCheckerPos.color == "Black"
					&& !jumpedCheckerPos.king) {
				ganimators.colorCapt = 'b';
			} else if (jumpedCheckerPos.color == "Black"
					&& jumpedCheckerPos.king) {
				ganimators.colorCapt = 'B';
			}

			// Remove checker
			jumpedCheckerPos.color = "";
			jumpedCheckerPos.king = false;
			gdatabase.updateCheckerPos(jumpedCheckerPos);
			ganimators.animateCapt = true;
			float xi = (float) (gdata.anchorArr1[jumpIdx].first) - hSz;
			float yi = (float) (gdata.anchorArr1[jumpIdx].second) - hSz;

			// Update animation
			if (jumpedCheckerPos.color == "White") {
				ganimators.p_aniPathLeg->INIT(xi, yi,
						ganimators.wh_captX
								+ ganimators.Nwh_capt * ganimators.capt_dx,
						ganimators.wh_captY, 40.0f);
			} else {
				ganimators.p_aniPathLeg->INIT(xi, yi,
						ganimators.bk_captX
								+ ganimators.Nbk_capt * ganimators.capt_dx,
						ganimators.bk_captY, 40.0f);
			}

			if (jumpedCheckerPos.color == "White") {
				if (!jumpedCheckerPos.king) {
					*ganimators.aniPath.ppSprite = &gsprites.wh_chSprite;
				} else {
					*ganimators.aniPath.ppSprite = &gsprites.wh_kSprite;
				}
			} else if (jumpedCheckerPos.color == "Black") {
				if (!jumpedCheckerPos.king) {
					*ganimators.aniPath.ppSprite = &gsprites.bk_chSprite;
				} else {
					*ganimators.aniPath.ppSprite = &gsprites.bk_kSprite;
				}
			}
			ganimators.aniPath.reset(true, 0);

			// See if another jump can be made
			gdata.canJump = false;
			if (!ganimators.justKinged) {
				gdata.canJump = fillMoveList(hm_f);
			}
		} else {
			gdata.canJump = false;        // no jump = no next jump
		}

		// If no more jumps for this player, change turn
		if (!gdata.canJump) {
			GameState currentState = gdatabase.getGameState();
			if (currentState.turn == "Black") {
				currentState.turn = "White";
			} else {
				currentState.turn = "Black";
			}
			gdatabase.updateGameState(currentState);
		}
	}

	return;
}
