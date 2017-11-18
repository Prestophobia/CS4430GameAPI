/**
 * @file /CS4430GameAPI/GameData.cpp
 * @author Neek
 * @date Nov 16, 2017
 * @brief .
 *
 * @details .
 */

#include "Data/GameData.h"

GameData::GameData(Sprites &gsprites) :
		gsprites(gsprites) {
	initBoard();
}

void GameData::initBoard() {
// anchor locations
//  float sqrSzX = 51.75 so /2 = 26
//  float sqrSzY = 50.5 so /2 = 25

	sqrSzX += 0.7f;			// tweaking values
	sqrSzY += 0.7f;

// all 32 anchors on the board
	int x0 = ch_bdPosX + ch_bdOffX + 26;
	int y0 = ch_bdPosY + ch_bdOffY + 25;
	for (int i = 0; i < Nanchors; ++i) {
		if ((i / 4) % 2)    // odd rows
			anchorArr1[i].first = x0 + (int) (sqrSzX * (2 * (i % 4)));
		else
			anchorArr1[i].first = x0 + (int) (sqrSzX * (1 + 2 * (i % 4)));

		anchorArr1[i].second = y0 + (int) (sqrSzY * (i / 4));
	}

	return;
}

