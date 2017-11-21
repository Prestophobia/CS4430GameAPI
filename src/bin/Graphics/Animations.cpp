/**
 * @file /CS4430GameAPI/src/Graphics/Animations.cpp
 * @author Neek
 * @date Nov 16, 2017
 * @brief .
 *
 * @details .
 */

#include "bin/Graphics/Animations.h"

Animations::Animations(GameData &gdata) :
		gsprites(gdata.gsprites), gdata(gdata) {
	initPaths();
	initDragDrops();
}

void Animations::initPaths() {
	int i = 0;    // for looping

	// for the checker deal animation
	// allocate and INIT Legs. The array of Leg*'s were allocated in the Path ctor
	for (i = 0; i < wh_dealPath.nLegs; ++i) {
		wh_dealPath.ppLeg[i] = new LinLeg;
		wh_dealPath.ppSprite[i] = &gsprites.wh_chSprite;
	}

	for (i = 0; i < bk_dealPath.nLegs; ++i) {
		bk_dealPath.ppLeg[i] = new LinLeg;
		bk_dealPath.ppSprite[i] = &gsprites.bk_chSprite;
	}

	// for the one-legged anis in the game ( capture, king split, "king me" )
	p_aniPathLeg = new LinLeg; // used for both capture and kink split animations
	*aniPath.ppLeg = p_aniPathLeg;

	p_kingMePathLeg = new LinLeg;
	*kingMePath.ppLeg = p_kingMePathLeg;

	return;
}

// call after INITcheckerPositions()
void Animations::initPathLegs() {
	int i = 0;    // for looping
	int Nwh_ch = 0, Nbk_ch = 0;
	int Nwh_k = 0, Nbk_k = 0;
	float hSz = gdata.chSz / 2.0f;

	for (i = 0; i < 32; ++i) {
		CheckerPos currentCheckerPos = Database::getCheckerPos(i + 1);
		if (currentCheckerPos.color == "White") {
			if (!currentCheckerPos.king) {
				wh_dealPath.ppLeg[Nwh_ch]->INIT(400.0f - hSz, -20.0f - hSz,
						static_cast<float>(gdata.anchorArr1[i].first) - hSz,
						static_cast<float>(gdata.anchorArr1[i].second) - hSz,
						30.0f);
				wh_dealPath.ppSprite[Nwh_ch++] = &gsprites.wh_chSprite;
			} else {
				wh_dealPath.ppLeg[Nwh_ch]->INIT(400.0f - hSz, -20.0f - hSz,
						static_cast<float>(gdata.anchorArr1[i].first) - hSz,
						static_cast<float>(gdata.anchorArr1[i].second) - hSz,
						30.0f);
				wh_dealPath.ppSprite[Nwh_ch++] = &gsprites.wh_kSprite;
				++Nwh_k;
			}
		} else if (currentCheckerPos.color == "Black") {
			if (!currentCheckerPos.king) {
				bk_dealPath.ppLeg[Nbk_ch]->INIT(400.0f - hSz, 620.0f - hSz,
						static_cast<float>(gdata.anchorArr1[i].first) - hSz,
						static_cast<float>(gdata.anchorArr1[i].second) - hSz,
						30.0f);
				bk_dealPath.ppSprite[Nbk_ch++] = &gsprites.bk_chSprite;
			} else {
				bk_dealPath.ppLeg[Nbk_ch]->INIT(400.0f - hSz, 620.0f - hSz,
						static_cast<float>(gdata.anchorArr1[i].first) - hSz,
						static_cast<float>(gdata.anchorArr1[i].second) - hSz,
						30.0f);
				bk_dealPath.ppSprite[Nbk_ch++] = &gsprites.bk_kSprite;
				++Nbk_k;
			}
		}
	}

	wh_dealPath.nLegs_inUse = 12 - Nwh_k;
	bk_dealPath.nLegs_inUse = 12 - Nbk_k;

	for (i = Nwh_ch; i < wh_dealPath.nLegs_inUse; ++i) {
		wh_dealPath.ppLeg[i]->INIT(820.0f, wh_captY,
				wh_captX + (i - Nwh_ch) * capt_dx, wh_captY, 30.0f);
		wh_dealPath.ppSprite[i] = &gsprites.wh_chSprite;
	}

	for (i = Nbk_ch; i < bk_dealPath.nLegs_inUse; ++i) {
		bk_dealPath.ppLeg[i]->INIT(820.0f, bk_captY,
				bk_captX + (i - Nbk_ch) * capt_dx, bk_captY, 30.0f);
		bk_dealPath.ppSprite[i] = &gsprites.bk_chSprite;
	}

	return;
}

void Animations::initDragDrops() {
// call set_anchors() before assign_size()
	chObj.set_anchors(gdata.anchorArr1.data(), gdata.Nanchors, 0); // currently Nanchors = 32
	chObj.assign_Size(&gsprites.wh_chSprite);

	gdata.chSz = chObj.szX;

	return;
}

bool Animations::textExpand(sf::Text& r_text, float scale_i, float scale_f,
		int Nframes, bool reset) {
	static int frCount = 0;
	static float oldRt = r_text.getLocalBounds().width;
	static float oldBot = r_text.getLocalBounds().height;
	if (reset) {
		frCount = 0;
		oldRt = r_text.getLocalBounds().width;
		oldBot = r_text.getLocalBounds().height;
	}

	if (frCount < Nframes)
		++frCount;
	else
		return false;        // not expanding anymore

	float scl = scale_i
			+ (scale_f - scale_i) * (float) frCount / (float) Nframes;
	r_text.setScale(scl, scl);
	float newRt = r_text.getLocalBounds().width;
	float newBot = r_text.getLocalBounds().height;
	r_text.move((oldRt - newRt) / 2.0f, (oldBot - newBot) / 2.0f);
	oldRt -= (oldRt - newRt) / 2.0f;
	oldBot -= (oldBot - newBot) / 2.0f;

	return true;
}

bool Animations::textFade(sf::Text& r_text, int alpha_i, int alpha_f,
		int Nframes, bool reset) {
	static int frCount = 0;
	static unsigned int oldRed = r_text.getFillColor().r;
	static unsigned int oldGrn = r_text.getFillColor().g;
	static unsigned int oldBlu = r_text.getFillColor().b;
	if (reset) {
		frCount = 0;
		oldRed = r_text.getFillColor().r;
		oldGrn = r_text.getFillColor().g;
		oldBlu = r_text.getFillColor().b;
	}

	if (frCount < Nframes)
		++frCount;
	else
		return false;        // not fading anymore

	int alf = (unsigned int) ((float) alpha_i
			+ (float) (alpha_f - alpha_i) * (float) frCount / (float) Nframes);
	r_text.setFillColor(sf::Color(oldRed, oldGrn, oldBlu, alf));

	return true;
}

void Animations::gameCapture_SplitAniLogic() {
	aniPath.move();

	// checker capture animation
	if (animateCapt && !aniPath.inUse)    // capture ani just ended
			{
		animateCapt = false;
		if (colorCapt == 'w' || colorCapt == 'W') {
			++Nwh_capt;
		} else {
			++Nbk_capt;
		}

		// split captured king ani trigger
		if (colorCapt == 'W' || colorCapt == 'B') {
			animateSplit = true;
			if (colorCapt == 'W') {
				p_aniPathLeg->INIT(wh_captX + (Nwh_capt - 1) * capt_dx,
						wh_captY, wh_captX + Nwh_capt * capt_dx, wh_captY,
						3.0f);
				*aniPath.ppSprite = &gsprites.wh_chSprite;
			} else {
				p_aniPathLeg->INIT(bk_captX + (Nbk_capt - 1) * capt_dx,
						bk_captY, bk_captX + Nbk_capt * capt_dx, bk_captY,
						3.0f);
				*aniPath.ppSprite = &gsprites.bk_chSprite;
			}
			aniPath.reset(true, 0);
		}
	}

	// captured king split animation terminal assigns. (trigger in code above)
	if (animateSplit && !aniPath.inUse) {
		animateSplit = false;
		if (colorCapt == 'W') {
			++Nwh_capt;
		} else {
			++Nbk_capt;
		}
	}
	return;
}

void Animations::gameKingMeAniLogic() {
// "King me" animation trigger
	if (justKinged && !aniPath.inUse) {
		justKinged = false;
		animateKing = true;
		kingMePath.reset(true, 0);
		if (*kingMePath.ppSprite == &gsprites.wh_chSprite)
			--Nwh_capt;
		else
			--Nbk_capt;
	}

	kingMePath.move();

// "King me" animation termination
	if (animateKing && !kingMePath.inUse) {
		animateKing = false;
		if (*kingMePath.ppSprite == &gsprites.wh_chSprite)
			chObj.pSprite = &gsprites.wh_kSprite;
		else
			chObj.pSprite = &gsprites.bk_kSprite;

	}
	return;
}

