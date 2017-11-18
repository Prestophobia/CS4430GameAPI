/**
 * @file /CS4430GameAPI/src/GameData.h
 * @author Neek
 * @date Nov 16, 2017
 * @brief .
 *
 * @details .
 */

#ifndef GAMEDATA_H_
#define GAMEDATA_H_

#include <SFML/System.hpp>

#include "Graphics/Sprites.h"

#include "Graphics/dragDropRect.h"

#define NANCHORS 32

class GameData {
public:
	Sprites &gsprites;

	sf::Clock last_move_clock;

	// a checker board
	int Nanchors = NANCHORS; // use for checker board
	std::array<std::pair<int, int>, NANCHORS> anchorArr1; // anchor locations for dragDrop objects

	int Nmoves = 5; // use for legal move anchor list
	int moveIdxList[5]; // anchor indexes for legal moves

	// turn logic
	bool jumpMade = false, canJump = false;
	bool reset = false; // reset to new game
	bool testMode = false; // read checker positions from a file
	bool gameOn = false; // true once a game selection is made
	bool gameOver = false; // true once all checkers of one color are captured
	bool pause = false;

	float sqrSzX = 51.75f;
	float sqrSzY = 50.f;
	int chSz = 40; // checker size

	// Mouse
	int mseX = 0;
	int mseY = 0;

	// Window
	int w_szX = 800, w_szY = 600;
	int w_posX = 50, w_posY = 50;

	// Board
	int ch_bdPosX = 150;
	int ch_bdPosY = 50;
	int ch_bdOffX = 44;
	int ch_bdOffY = 43;

	GameData(Sprites &gsprites);
	void initBoard();
};

#endif /* GAMEDATA_H_ */
