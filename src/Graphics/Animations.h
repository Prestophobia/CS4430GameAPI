/**
 * @file /CS4430GameAPI/src/Graphics/Animations.h
 * @author Neek
 * @date Nov 16, 2017
 * @brief .
 *
 * @details .
 */

#ifndef GRAPHICS_ANIMATIONS_H_
#define GRAPHICS_ANIMATIONS_H_

#include "Graphics/Path.h"
#include "Graphics/linLeg.h"

#include "Graphics/Sprites.h"

#include "Database/Database.h"

#include "Data/GameData.h"

class Animations {

public:
	Sprites &gsprites;
	Database &gdatabase;
	GameData &gdata;

	int textFXdelay = 30; // for "WELCOME"
	bool textFX = true; // and "GAME OVER" message effects

	float wh_captX = 150.0f, wh_captY = 550.0f; // base position for captured checkers
	float bk_captX = 150.0f, bk_captY = 5.0f;
	float capt_dx = 50.0f; // distance between captured checkers
	int Nwh_capt = 0, Nbk_capt = 0;

	// the user moved checker
	dragDropRect chObj { 200, 200, 0 };

	Path aniPath { 1, 0, 0, 100.0f, 100.0f }; // start using this!!
	linLeg* p_aniPathLeg = NULL; // for calling INITlin() on aniPath leg

	Path kingMePath { 1, 0, 0, 100.0f, 100.0f }; // start using this!!
	linLeg* p_kingMePathLeg = NULL; // for calling INITlin() on aniPath leg

	// Checker Setup Animation Paths
	Path wh_dealPath { 12, 50, 3, 400.0f, -40.0f };
	Path bk_dealPath { 12, 50, 3, 400.0f, 620.0f };

	// checker capture animation
	bool animateCapt = false; // true in LBUTT_DN. false in frame logic
	char colorCapt = ' '; // 'w' or 'b'

	// other animations
	bool justKinged = false; // true in LBUTT_DN. false in frame logic
	bool animateSplit = false; // split a captured king in two. true and false in frame logic
	bool animateKing = false;

	Animations(GameData &gdata, Database &gdatabase);
	void initPaths();
	void initPathLegs();
	void initDragDrops();
	bool textExpand(sf::Text& r_text, float scale_i, float scale_f, int Nframes,
			bool reset);
	bool textFade(sf::Text& r_text, int alpha_i, int alpha_f, int Nframes,
			bool reset);
	void gameCapture_SplitAniLogic();
	void gameKingMeAniLogic();
};

#endif /* GRAPHICS_ANIMATIONS_H_ */
