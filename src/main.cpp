#include <windows.h>
#include <SFML/Graphics.hpp>

#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include "buttonRectImage.h"
#include "buttonRectDrawn.h"
#include "dragDropRect.h"
#include "linLeg.h"
#include "Path.h"
#include "Font.h"

void EVENTcheck(sf::Event &event, sf::Window &window);
HDC hdc;
int mseX = 0, mseY = 0;
int w_szX = 800, w_szY = 600;
int w_posX = 50, w_posY = 50;

// static vars
const int& button::r_mseX = mseX;
const int& button::r_mseY = mseY;
const int& dragDrop::r_mseX = mseX;
const int& dragDrop::r_mseY = mseY;

// buttons
sf::Sprite buttSprite1;
sf::Image buttImg1;
sf::Texture buttTex1;
buttonRectImage newButt('m', 50, 100, NULL); // start a new game
buttonRectImage savedButt('m', 50, 170, NULL); // save the current game
buttonRectImage saveGameButt('m', 50, 240, NULL); // start the saved game

//** dragDrop objects **
sf::Sprite wh_chSprite; // player 1 = white
sf::Image wh_chImg;
sf::Texture wh_chTex;
sf::Sprite wh_kSprite;
sf::Image wh_kingImg;
sf::Texture wh_kingTex;

sf::Sprite bk_chSprite; // player 0 = black
sf::Image bk_chImg;
sf::Texture bk_chTex;
sf::Sprite bk_kSprite;
sf::Image bk_kingImg;
sf::Texture bk_kingTex;

dragDropRect chObj(200, 200, NULL); // the user moved checker

// a checker board
const int Nanchors = 32; // use for checker board
std::pair<int, int> anchorArr1[Nanchors]; // anchor locations for dragDrop objects
char checkerPos[32]; // 'b'=black, 'w'=white, 'n'=none (open square)

int Nmoves = 5; // use for legal move anchor list
int moveIdxList[5]; // anchor indexes for legal moves

sf::Sprite boardSprite;
sf::Texture boardTex;
int ch_bdPosX = 150; // dimensional data
int ch_bdPosY = 50;
int ch_bdOffX = 44;
int ch_bdOffY = 43;
float sqrSzX = 51.75f;
float sqrSzY = 50.f;
int chSz = 40; // checker size

// turn logic
bool turn = true; // true = white, false = black
bool jumpMade = false, canJump = false;
bool reset = false; // reset to new game
bool testMode = false; // read checker positions from a file
bool gameOn = false; // true once a game selection is made
bool gameOver = false; // true once all checkers of one color are captured
bool pause = false;

// functions
bool LoadImages(void);
void INITbuttons(void);
void INITboard(void);
bool INITcheckerPositions_NEW(void); // for a new game
bool INITcheckerPositions_SAVED(const char* fname); // returns false on bad file read attempt
void INITdragDrops(void);
void INITtext(void); // check
bool saveGameToFile(const char* fname);
void drawCheckers(sf::RenderWindow& rApp);

void gameLogic(void);
void gameDraw(sf::RenderWindow& rApp);
void gameHitDown(void);
void gameHitUp(void);
void gameCapture_SplitAniLogic(void);
void gameKingMeAniLogic(void);
bool menuHitDown(void); // returns false if file I/O error
void menuHitUp(void);

int hitAnchor(bool Turn); // finds which anchor was hit. Returns anchor index if valid anchor was hit. Returns -1 if not.
bool fillMoveList(int idx); // called when a checker is grabbed for a move. Returns true if a jump may be made
bool didJump(int hm_0, int hm_f, int& jumpIdx);

// checker  setup animation
Path wh_dealPath(12, 50, 3, 400.0f, -40.0f);
Path bk_dealPath(12, 50, 3, 400.0f, 620.0f);
void ALLOC_paths(void);
void INITpathLegs(void);

sf::Text msg;
sf::Text msg_Turn;
sf::Text msg_Whites;
sf::Text msg_Blacks;
sf::Text msg_WELCOME;
sf::Text msg_GAMEOVER;
sf::Text msg_WHITEWINS;
sf::Text msg_BLACKWINS;
sf::Text* p_FXmsg = &msg_WELCOME;
int textFXdelay = 30; // for "WELCOME"
bool textFX = true; // and "GAME OVER" message effects
bool textExpand(sf::Text& r_text, float scale_i, float scale_f, int Nframes,
		bool reset = false);
bool textFade(sf::Text& r_text, int alpha_i, int alpha_f, int Nframes,
		bool reset = false);

// checker capture animation
bool animateCapt = false; // true in LBUTT_DN. false in frame logic
char colorCapt; // 'w' or 'b'
float wh_captX = 150.0f, wh_captY = 550.0f; // base position for captured checkers
float bk_captX = 150.0f, bk_captY = 5.0f;
float capt_dx = 50.0f; // distance between captured checkers
int Nwh_capt = 0, Nbk_capt = 0;
Path aniPath(1, 0, 0, 100.0f, 100.0f); // start using this!!
linLeg* p_aniPathLeg = NULL; // for calling INITlin() on aniPath leg

Path kingMePath(1, 0, 0, 100.0f, 100.0f); // start using this!!
linLeg* p_kingMePathLeg = NULL; // for calling INITlin() on aniPath leg

// other animations
bool justKinged = false; // true in LBUTT_DN. false in frame logic
bool animateSplit = false; // split a captured king in two. true and false in frame logic
bool animateKing = false;

template<class T>
float to_sf_string(sf::String& strArg, T x) // returns position of end of strArg
		{
	std::stringstream ss;
	ss << x;
	std::string tempStr;
	ss >> tempStr;
	strArg = tempStr;
	return strArg.getSize();
}

int main(int argc, char *argv[]) {
	// load images
	if (!LoadImages())
		return 0; // return error code!

	// create the SFML window
	sf::RenderWindow window(sf::VideoMode(w_szX, w_szY), "Checkers");
	window.setActive();

	// local vars
	float frPeriod = 1.0f / 30.0f; // for 30 fps
	sf::Clock frClock;
	frClock.restart();

	// INIT stuff
	button::pWndw = &window;
	dragDrop::pWndw = &window;
	Path::pWndw = &window;
	INITboard();
	ALLOC_paths(); // dynamic allocation of legs to the deal paths
	INITbuttons();
	INITtext();
	INITdragDrops();
	wh_dealPath.inUse = false;
	bk_dealPath.inUse = false;

	window.setVerticalSyncEnabled(true); // default = false

	if (window.isOpen()) {
		do {
			if (!pause && frClock.getElapsedTime().asSeconds() > frPeriod) {
				frClock.restart();
				gameLogic();

				// draw stuff
				window.clear(sf::Color(0, 50, 100)); // Color bkgd

				gameDraw(window);

				window.display();
			}

			sf::Event event;
			while (window.pollEvent(event)) {
				EVENTcheck(event, window);
			}
		} while (window.isOpen());
	}

	return 0;
} // end of main

void EVENTcheck(sf::Event &event, sf::Window &window) {
	switch (event.type) {
	case sf::Event::Closed:
		window.close();
		break;
	case sf::Event::MouseButtonPressed:
		if (!pause && event.mouseButton.button == sf::Mouse::Left) {
			if (!menuHitDown()) {
				window.close(); // file I/O error
			}
			gameHitDown();
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (!pause && event.mouseButton.button == sf::Mouse::Left) {
			menuHitUp();
			gameHitUp();
		}
		break;
	case sf::Event::MouseMoved:
		mseX = event.mouseMove.x;
		mseY = event.mouseMove.y;

		// button mouseovers
		newButt.mseOver();
		savedButt.mseOver();

		if (gameOn) {
			saveGameButt.mseOver();
		}

		// dragDrop object move
		chObj.drag();

		break;
	case sf::Event::KeyPressed:
		switch (event.key.code) {
		case sf::Keyboard::Escape: // kill app via escape key
			//	Cleanup();
			window.close();
			break;
		case sf::Keyboard::P:				// provides a play/pause function
			pause = !pause;				// toggle state
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

bool LoadImages(void) {
// font
	if (!font.loadFromFile("images/Enchanted Land.otf"))
		return false;

// buttons
	if (!buttImg1.loadFromFile("images/buttonsImageAlt.png")) // 33x22px - from Ultifinitus
		return false;
	buttImg1.createMaskFromColor(sf::Color(0, 0, 0));
	buttTex1.loadFromImage(buttImg1);
	buttSprite1.setTexture(buttTex1);

// dragDrop objects
	if (!wh_chImg.loadFromFile("images/white_checker.png"))		// 40 x 40 px
		return false;
	wh_chImg.createMaskFromColor(sf::Color(0, 0, 0));
	wh_chTex.loadFromImage(wh_chImg);
	wh_chSprite.setTexture(wh_chTex);

	if (!wh_kingImg.loadFromFile("images/white_checker_King.png"))// 40 x 40 px
		return false;
	wh_kingImg.createMaskFromColor(sf::Color(0, 0, 0));
	wh_kingTex.loadFromImage(wh_kingImg);
	wh_kSprite.setTexture(wh_kingTex);

	if (!bk_chImg.loadFromFile("images/black_checker.png"))		// 40 x 40 px
		return false;
	bk_chImg.createMaskFromColor(sf::Color(0, 0, 0));
	bk_chTex.loadFromImage(bk_chImg);
	bk_chSprite.setTexture(bk_chTex);

	if (!bk_kingImg.loadFromFile("images/black_checker_King.png"))// 40 x 40 px
		return false;
	bk_kingImg.createMaskFromColor(sf::Color(0, 0, 0));
	bk_kingTex.loadFromImage(bk_kingImg);
	bk_kSprite.setTexture(bk_kingTex);

// a checker board
	if (!boardTex.loadFromFile("images/checker_board.jpg"))		// 499 x 491 px
		return false;
	boardSprite.setTexture(boardTex);
	boardSprite.setPosition(static_cast<float>(ch_bdPosX),
			static_cast<float>(ch_bdPosY));

	return true;
}

void INITbuttons(void) {
	newButt.assign_Sprite(&buttSprite1);
	newButt.INITlabel(sf::Text("Start New Game", font, 16),
			sf::Color(0, 255, 0), 'b');

	savedButt.assign_Sprite(&buttSprite1);
	savedButt.INITlabel(sf::Text("Load Saved Game", font, 16),
			sf::Color(0, 255, 0), 'b');

	saveGameButt.assign_Sprite(&buttSprite1);
	saveGameButt.INITlabel(sf::Text("Save This Game", font, 16),
			sf::Color(0, 255, 0), 'b');

	return;
}

void INITboard(void) {
// anchor locations
//  float sqrSzX = 51.75 so /2 = 26
//  float sqrSzY = 50.5 so /2 = 25

	sqrSzX += 0.7f;    // tweaking values
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

bool INITcheckerPositions_NEW(void) {
	int i = 0;    // for looping

// initial checker positions
	for (i = 0; i <= 11; ++i)
		checkerPos[i] = 'w';

	for (i = 12; i <= 19; ++i)
		checkerPos[i] = 'n';

	for (i = 20; i <= 31; ++i)
		checkerPos[i] = 'b';

	turn = true;
	Nwh_capt = Nbk_capt = 0;

	return true;
}

bool INITcheckerPositions_SAVED(const char* fname) {
	int i = 0;    // for looping

// initial checker positions
	for (i = 0; i < 32; ++i)
		checkerPos[i] = 'n';

	std::ifstream infile(fname);
	int Nwh_reg = 0, Nwh_k = 0;
	int Nbk_reg = 0, Nbk_k = 0;
	int Turn = 0;
	int idx = 0;

	if (!infile) {
		std::ofstream fout(fname);
		fout.close();
		infile = std::ifstream(fname);
	}
// white checkers
	infile >> Nwh_reg >> Nwh_k >> Nbk_reg >> Nbk_k >> Turn;
	for (i = 0; i < Nwh_reg; ++i) {
		infile >> idx;
		checkerPos[idx] = 'w';
	}
	for (i = 0; i < Nwh_k; ++i) {
		infile >> idx;
		checkerPos[idx] = 'W';
	}

// black checkers
	for (i = 0; i < Nbk_reg; ++i) {
		infile >> idx;
		checkerPos[idx] = 'b';
	}
	for (i = 0; i < Nbk_k; ++i) {
		infile >> idx;
		checkerPos[idx] = 'B';
	}

	Nwh_capt = 12 - Nwh_reg - 2 * Nwh_k;
	Nbk_capt = 12 - Nbk_reg - 2 * Nbk_k;
	if (Turn)
		turn = true;
	else
		turn = false;

	infile.close();
	return true;
}

bool saveGameToFile(const char* fname) {
	int i = 0;
	int Nwh_reg = 0, Nwh_k = 0;
	int Nbk_reg = 0, Nbk_k = 0;

	for (i = 0; i < 32; ++i)
		switch (checkerPos[i]) {
		case 'w':
			++Nwh_reg;
			break;
		case 'W':
			++Nwh_k;
			break;
		case 'b':
			++Nbk_reg;
			break;
		case 'B':
			++Nbk_k;
			break;
		default:
			break;
		}

	std::ofstream fout(fname);
	if (fout) {
		// white checkers
		fout << Nwh_reg << " " << Nwh_k << " " << Nbk_reg << " " << Nbk_k
				<< " ";
		if (turn)
			fout << 1 << '\n';
		else
			fout << 0 << '\n';

		for (i = 0; i < 32; ++i)
			if (checkerPos[i] == 'w')
				fout << i << " ";
		fout << '\n';

		for (i = 0; i < 32; ++i)
			if (checkerPos[i] == 'W')
				fout << i << " ";
		fout << '\n';

		for (i = 0; i < 32; ++i)
			if (checkerPos[i] == 'b')
				fout << i << " ";
		fout << '\n';

		for (i = 0; i < 32; ++i)
			if (checkerPos[i] == 'B')
				fout << i << " ";
		fout << '\n';

		fout.close();
		return true;
	}

	return false;
}

void INITdragDrops(void) {
// call set_anchors() before assign_size()
	chObj.set_anchors(anchorArr1, Nanchors, 0);    // currently Nanchors = 32
	chObj.assign_Size(&wh_chSprite);

	chSz = chObj.szX;

	return;
}

void INITtext(void) {
	msg.setString("Loading");
	msg.setPosition(300.0f, 30.0f);
	msg.setFont(font);
	msg.setFillColor(sf::Color(255, 255, 255));
	msg.setCharacterSize(16.0);

	msg_Whites.setString("White's");
	msg_Whites.setPosition(700.0f, 280.0f);
	msg_Whites.setFont(font);
	msg_Whites.setFillColor(sf::Color(255, 255, 255));
	msg_Whites.setCharacterSize(18.0);

	msg_Blacks.setString("Black's");
	msg_Blacks.setPosition(700.0f, 280.0f);
	msg_Blacks.setFont(font);
	msg_Blacks.setFillColor(sf::Color(255, 255, 255));
	msg_Blacks.setCharacterSize(18.0);

	msg_Turn.setString("Turn");
	msg_Turn.setPosition(720.0f, 295.0f);
	msg_Turn.setFont(font);
	msg_Turn.setFillColor(sf::Color(255, 255, 255));
	msg_Turn.setCharacterSize(16.0);

	msg_WELCOME.setString("WELCOME");
	msg_WELCOME.setFont(font);
	msg_WELCOME.setFillColor(sf::Color(0, 100, 200));
	msg_WELCOME.setPosition(320.0f, 255.0f);

	msg_GAMEOVER.setString("GAME OVER");
	msg_GAMEOVER.setFont(font);
	msg_GAMEOVER.setFillColor(sf::Color(0, 100, 200));
	msg_GAMEOVER.setPosition(320.0f, 255.0f);

	msg_WHITEWINS.setString("WHITE WINS!");
	msg_WHITEWINS.setFont(font);
	msg_WHITEWINS.setFillColor(sf::Color(0, 100, 200));
	msg_WHITEWINS.setPosition(320.0f, 255.0f);

	msg_BLACKWINS.setString("BLACK WINS!");
	msg_BLACKWINS.setFont(font);
	msg_BLACKWINS.setFillColor(sf::Color(0, 100, 200));
	msg_BLACKWINS.setPosition(320.0f, 255.0f);
}

void ALLOC_paths(void) {
	int i = 0;    // for looping

// for the checker deal animation
// allocate and INIT Legs. The array of Leg*'s were allocated in the Path ctor
	for (i = 0; i < wh_dealPath.nLegs; ++i) {
		wh_dealPath.ppLeg[i] = new linLeg;
		wh_dealPath.ppSprite[i] = &wh_chSprite;
	}

	for (i = 0; i < bk_dealPath.nLegs; ++i) {
		bk_dealPath.ppLeg[i] = new linLeg;
		bk_dealPath.ppSprite[i] = &bk_chSprite;
	}

// for the one-legged anis in the game ( capture, king split, "king me" )
	p_aniPathLeg = new linLeg; // used for both capture and kink split animations
	*aniPath.ppLeg = p_aniPathLeg;

	p_kingMePathLeg = new linLeg;
	*kingMePath.ppLeg = p_kingMePathLeg;

	return;
}

// call after INITcheckerPositions()
void INITpathLegs(void) {
	int i = 0;    // for looping
	int Nwh_ch = 0, Nbk_ch = 0;
	int Nwh_k = 0, Nbk_k = 0;
	float hSz = chSz / 2.0f;

	for (i = 0; i < 32; ++i) {
		switch (checkerPos[i]) {
		case 'w':
			wh_dealPath.ppLeg[Nwh_ch]->INIT(400.0f - hSz, -20.0f - hSz,
					static_cast<float>(anchorArr1[i].first) - hSz,
					static_cast<float>(anchorArr1[i].second) - hSz, 30.0f);
			wh_dealPath.ppSprite[Nwh_ch++] = &wh_chSprite;
			break;
		case 'W':
			wh_dealPath.ppLeg[Nwh_ch]->INIT(400.0f - hSz, -20.0f - hSz,
					static_cast<float>(anchorArr1[i].first) - hSz,
					static_cast<float>(anchorArr1[i].second) - hSz, 30.0f);
			wh_dealPath.ppSprite[Nwh_ch++] = &wh_kSprite;
			++Nwh_k;
			break;
		case 'b':
			bk_dealPath.ppLeg[Nbk_ch]->INIT(400.0f - hSz, 620.0f - hSz,
					static_cast<float>(anchorArr1[i].first) - hSz,
					static_cast<float>(anchorArr1[i].second) - hSz, 30.0f);
			bk_dealPath.ppSprite[Nbk_ch++] = &bk_chSprite;
			break;
		case 'B':
			bk_dealPath.ppLeg[Nbk_ch]->INIT(400.0f - hSz, 620.0f - hSz,
					static_cast<float>(anchorArr1[i].first) - hSz,
					static_cast<float>(anchorArr1[i].second) - hSz, 30.0f);
			bk_dealPath.ppSprite[Nbk_ch++] = &bk_kSprite;
			++Nbk_k;
			break;
		default:
			break;
		}
	}

	wh_dealPath.nLegs_inUse = 12 - Nwh_k;
	bk_dealPath.nLegs_inUse = 12 - Nbk_k;

	for (i = Nwh_ch; i < wh_dealPath.nLegs_inUse; ++i) {
		wh_dealPath.ppLeg[i]->INIT(820.0f, wh_captY,
				wh_captX + (i - Nwh_ch) * capt_dx, wh_captY, 30.0f);
		wh_dealPath.ppSprite[i] = &wh_chSprite;
	}

	for (i = Nbk_ch; i < bk_dealPath.nLegs_inUse; ++i) {
		bk_dealPath.ppLeg[i]->INIT(820.0f, bk_captY,
				bk_captX + (i - Nbk_ch) * capt_dx, bk_captY, 30.0f);
		bk_dealPath.ppSprite[i] = &bk_chSprite;
	}

	return;
}

// returns true if a jump may be made
bool fillMoveList(int hm)    // called when a checker is grabbed for a move
		{
	Nmoves = 0;    // global
// locals
	bool isKing = checkerPos[hm] == 'W' || checkerPos[hm] == 'B';
	char opCol = turn ? 'b' : 'w';
	char opColK = turn ? 'B' : 'W';

	if (turn || isKing)    // white or king
			{
//        if( hm < 28 )// not in bottom row
		if (hm < 28 && !jumpMade)    // not in bottom row
				{
			if (hm % 8 == 3 || hm % 8 == 4)    // is edge position
					{
				if (checkerPos[hm + 4] == 'n')
					moveIdxList[Nmoves++] = hm + 4;
			} else if ((hm / 4) % 2)    // odd row ( 1, 3, 5 )
					{
				if (checkerPos[hm + 3] == 'n')
					moveIdxList[Nmoves++] = hm + 3;
				if (checkerPos[hm + 4] == 'n')
					moveIdxList[Nmoves++] = hm + 4;
			} else    // even row ( 0, 2, 4, 6 )
			{
				if (checkerPos[hm + 4] == 'n')
					moveIdxList[Nmoves++] = hm + 4;
				if (checkerPos[hm + 5] == 'n')
					moveIdxList[Nmoves++] = hm + 5;
			}
		}
		if (hm < 24)    // check for jumps
				{
			if (hm % 8 == 3)    // on right edge
					{
				if ((checkerPos[hm + 4] == opCol || checkerPos[hm + 4] == opColK)
						&& checkerPos[hm + 7] == 'n') // a jump over hm+4 to hm+7 can be made
					moveIdxList[Nmoves++] = hm + 7;
			} else if (hm % 8 == 4)    // on left edge
					{
				if ((checkerPos[hm + 4] == opCol || checkerPos[hm + 4] == opColK)
						&& checkerPos[hm + 9] == 'n') // a jump over hm+4 to hm+7 can be made
					moveIdxList[Nmoves++] = hm + 9;
			} else if ((hm / 4) % 2)    // odd row ( 1, 3, 5 )
					{
				if ((checkerPos[hm + 3] == opCol || checkerPos[hm + 3] == opColK)
						&& checkerPos[hm + 7] == 'n')
					moveIdxList[Nmoves++] = hm + 7;
				if ((checkerPos[hm + 4] == opCol || checkerPos[hm + 4] == opColK)
						&& checkerPos[hm + 9] == 'n')
					moveIdxList[Nmoves++] = hm + 9;
			} else    // even row ( 0, 2, 4 )
			{
				if ((checkerPos[hm + 4] == opCol || checkerPos[hm + 4] == opColK)
						&& checkerPos[hm + 7] == 'n')
					moveIdxList[Nmoves++] = hm + 7;
				if ((checkerPos[hm + 5] == opCol || checkerPos[hm + 5] == opColK)
						&& checkerPos[hm + 9] == 'n')
					moveIdxList[Nmoves++] = hm + 9;
			}
		}    // end check for jumps
	}
	if (!turn || isKing)    // black or king
			{
		//     if( hm >3 )// not in top row
		if (hm > 3 && !jumpMade)    // not in top row
				{
			if (hm % 8 == 3 || hm % 8 == 4)    // is edge position
					{
				if (checkerPos[hm - 4] == 'n')
					moveIdxList[Nmoves++] = hm - 4;
			} else if ((hm / 4) % 2)    // odd row ( 1, 3, 5, 7 )
					{
				if (checkerPos[hm - 4] == 'n')
					moveIdxList[Nmoves++] = hm - 4;
				if (checkerPos[hm - 5] == 'n')
					moveIdxList[Nmoves++] = hm - 5;
			} else    // even row ( 2, 4, 6 )
			{
				if (checkerPos[hm - 3] == 'n')
					moveIdxList[Nmoves++] = hm - 3;
				if (checkerPos[hm - 4] == 'n')
					moveIdxList[Nmoves++] = hm - 4;
			}
		}
		if (hm > 7)    // check for jumps
				{
			if (hm % 8 == 3)    // on right edge
					{
				if ((checkerPos[hm - 4] == opCol || checkerPos[hm - 4] == opColK)
						&& checkerPos[hm - 9] == 'n') // a jump over hm+4 to hm+7 can be made
					moveIdxList[Nmoves++] = hm - 9;
			} else if (hm % 8 == 4)    // on left edge
					{
				if ((checkerPos[hm - 4] == opCol || checkerPos[hm - 4] == opColK)
						&& checkerPos[hm - 7] == 'n') // a jump over hm+4 to hm+7 can be made
					moveIdxList[Nmoves++] = hm - 7;
			} else if ((hm / 4) % 2)    // odd row ( 3, 5, 7 )
					{
				if ((checkerPos[hm - 4] == opCol || checkerPos[hm - 4] == opColK)
						&& checkerPos[hm - 7] == 'n')
					moveIdxList[Nmoves++] = hm - 7;
				if ((checkerPos[hm - 5] == opCol || checkerPos[hm - 5] == opColK)
						&& checkerPos[hm - 9] == 'n')
					moveIdxList[Nmoves++] = hm - 9;
			} else    // even row ( 0, 2, 4 )
			{
				if ((checkerPos[hm - 3] == opCol || checkerPos[hm - 3] == opColK)
						&& checkerPos[hm - 7] == 'n')
					moveIdxList[Nmoves++] = hm - 7;
				if ((checkerPos[hm - 4] == opCol || checkerPos[hm - 4] == opColK)
						&& checkerPos[hm - 9] == 'n')
					moveIdxList[Nmoves++] = hm - 9;
			}
		}    // end check for jumps
	}

// check if any jump moves were found
	for (int i = 0; i < Nmoves; ++i) {
		//        for white                           for black
		if ((moveIdxList[i] - hm > 5) || (moveIdxList[i] - hm < -5)) // jump found
			return true;
	}

	return false;    // no jumps found
}    // end of fillMoveList()

bool didJump(int hm_0, int hm_f, int& jumpIdx) // returns true if a jump was made and assigns jumpIdx = space# jumped
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
}    // end of didJump()

// finds which anchor was hit. Returns anchor index if valid anchor was hit. Returns -1 if not.
int hitAnchor(bool Turn) // global turn not used as other value may be considered
		{
	int hSz = chSz / 2;
	int idx = 0;

	for (idx = 0; idx < Nanchors; ++idx) {
		if (mseX < anchorArr1[idx].first - hSz)
			continue;
		if (mseX > anchorArr1[idx].first + hSz)
			continue;
		if (mseY < anchorArr1[idx].second - hSz)
			continue;
		if (mseY > anchorArr1[idx].second + hSz)
			continue;
		break;    // because anchor idx was hit
	}
	if (idx == Nanchors)
		return -1;    // all anchors were missed
	if (Turn && (checkerPos[idx] == 'w' || checkerPos[idx] == 'W'))
		return idx;
	if (!Turn && (checkerPos[idx] == 'b' || checkerPos[idx] == 'B'))
		return idx;
	return -1;    // invalid anchor was hit
}

void drawCheckers(sf::RenderWindow& rApp) {
// draw all checkers except the moving one
	float hSz = chSz / 2;
	int i = 0;    // for looping

	if (reset)    // animated checker display
	{
		wh_dealPath.draw();
		bk_dealPath.draw();
		rApp.draw(msg);
	}

	if (gameOn)    // normal checker display
	{
		for (i = 0; i < Nanchors; ++i)
			if (i != chObj.homeIdx)    // exclude the moving chObj
					{
				switch (checkerPos[i]) {
				case 'w':
					wh_chSprite.setPosition(
							static_cast<float>(anchorArr1[i].first) - hSz,
							static_cast<float>(anchorArr1[i].second) - hSz);
					rApp.draw(wh_chSprite);
					break;
				case 'W':
					wh_kSprite.setPosition(
							static_cast<float>(anchorArr1[i].first) - hSz,
							static_cast<float>(anchorArr1[i].second) - hSz);
					rApp.draw(wh_kSprite);
					break;
				case 'b':
					bk_chSprite.setPosition(
							static_cast<float>(anchorArr1[i].first) - hSz,
							static_cast<float>(anchorArr1[i].second) - hSz);
					rApp.draw(bk_chSprite);
					break;
				case 'B':
					bk_kSprite.setPosition(
							static_cast<float>(anchorArr1[i].first) - hSz,
							static_cast<float>(anchorArr1[i].second) - hSz);
					rApp.draw(bk_kSprite);
					break;
				default:
					break;
				}
			}

		chObj.draw();

		// some text too
		if (!gameOver) {
			rApp.draw(msg_Turn);
			if (turn)
				rApp.draw(msg_Whites);
			else
				rApp.draw(msg_Blacks);
		}

		// draw the captured checkers
		for (i = 0; i < Nwh_capt; ++i) {
			wh_chSprite.setPosition(wh_captX + capt_dx * (float) i, wh_captY);
			rApp.draw(wh_chSprite);
		}
		for (i = 0; i < Nbk_capt; ++i) {
			bk_chSprite.setPosition(bk_captX + capt_dx * (float) i, bk_captY);
			rApp.draw(bk_chSprite);
		}

		// single animations
		if (aniPath.inUse)
			aniPath.draw();
		if (kingMePath.inUse)
			kingMePath.draw();
	}

	return;
}    // end of drawCheckers()

void gameCapture_SplitAniLogic(void) {
	aniPath.move();

// checker capture animation
	if (animateCapt && !aniPath.inUse)    // capture ani just ended
			{
		animateCapt = false;
		if (colorCapt == 'w' || colorCapt == 'W')
			++Nwh_capt;
		else
			++Nbk_capt;

		// split captured king ani trigger
		if (colorCapt == 'W' || colorCapt == 'B') {
			animateSplit = true;
			if (colorCapt == 'W') {
				p_aniPathLeg->INIT(wh_captX + (Nwh_capt - 1) * capt_dx,
						wh_captY, wh_captX + Nwh_capt * capt_dx, wh_captY,
						3.0f);
				*aniPath.ppSprite = &wh_chSprite;
			} else {
				p_aniPathLeg->INIT(bk_captX + (Nbk_capt - 1) * capt_dx,
						bk_captY, bk_captX + Nbk_capt * capt_dx, bk_captY,
						3.0f);
				*aniPath.ppSprite = &bk_chSprite;
			}
			aniPath.reset(true, 0);
		}
	}

// captured king split animation terminal assigns. (trigger in code above)
	if (animateSplit && !aniPath.inUse) {
		animateSplit = false;
		if (colorCapt == 'W')
			++Nwh_capt;
		else
			++Nbk_capt;
	}
	return;
}

void gameKingMeAniLogic(void) {
// "King me" animation trigger
	if (justKinged && !aniPath.inUse) {
		justKinged = false;
		animateKing = true;
		kingMePath.reset(true, 0);
		if (*kingMePath.ppSprite == &wh_chSprite)
			--Nwh_capt;
		else
			--Nbk_capt;
	}

	kingMePath.move();

// "King me" animation termination
	if (animateKing && !kingMePath.inUse) {
		animateKing = false;
		if (*kingMePath.ppSprite == &wh_chSprite)
			chObj.pSprite = &wh_kSprite;
		else
			chObj.pSprite = &bk_kSprite;

	}
	return;
}

bool menuHitDown(void)    // returns false if file I/O error
		{
	bool init_game = false;

	if (gameOn)
		if (saveGameButt.hit_dn()) {
			if (!saveGameToFile("save.chk"))
				return false;
		}
	if (newButt.hit_dn()) {
		init_game = true;
		INITcheckerPositions_NEW();
	}
	if (savedButt.hit_dn()) {
		init_game = true;
		if (!INITcheckerPositions_SAVED("save.chk"))
			return false;
	}

	if (init_game)    // resets game
	{
		init_game = false;

		INITpathLegs();
		int i = 0;
		for (i = 0; i < 32; ++i)
			if (checkerPos[i] == 'w')
				break;    // find 1st white checker
		chObj.homeIdx = i;
		chObj.docked = false;
		chObj.snap();
		chObj.pSprite = &wh_chSprite;
		//        turn = true;// whites turn
		reset = true;
		gameOn = gameOver = false;
		animateKing = justKinged = false;
		wh_dealPath.reset(true, 0);
		bk_dealPath.reset(true, 0);
		//        Nwh_capt = Nbk_capt = 0;
		//        textFX = true;
		//        textFXdelay = 30;
		//        textExpand( msg_WELCOME, 1.0f, 7.0f, 20, true );
		//        textFade( msg_WELCOME, 255, 1, 20, true );
	}

	return true;
}        // end of menuHitDown()

void menuHitUp(void) {
	newButt.hit_up();
	savedButt.hit_up();
	if (gameOn)
		saveGameButt.hit_up();

	return;
}

void gameHitDown(void) {
	int idx = -1;
	if (jumpMade && canJump)        // handle multi-jump
			{
		if (chObj.grab())
			return;        // moveList already filled after 1st jump
		idx = hitAnchor(!turn);        // see if other color anchor was hit
		if (idx != -1)        // it was!
				{
			turn = !turn;        // change turn
			jumpMade = canJump = false;
		}
	} else
		// normal treatment
		idx = hitAnchor(turn);

// normal case
	if (idx != -1)        // a valid anchor was hit
			{
		jumpMade = false;
		fillMoveList(idx);
		if (Nmoves > 0)        // move is possible from anchor idx
				{
			// relocate chObj to anchor idx
			chObj.homeIdx = idx;
			chObj.docked = false;
			chObj.snap();
			chObj.grab();
			switch (checkerPos[idx]) {
			case 'w':
				chObj.pSprite = &wh_chSprite;
				break;
			case 'W':
				chObj.pSprite = &wh_kSprite;
				break;
			case 'b':
				chObj.pSprite = &bk_chSprite;
				break;
			case 'B':
				chObj.pSprite = &bk_kSprite;
				break;
			default:
				break;
			}
		}
	}

	return;
}        // end of gameHitDown()

void gameHitUp(void) {
	int hm_0 = chObj.homeIdx;
	chObj.release(moveIdxList, Nmoves);
	chObj.snap();

	int hm_f = chObj.homeIdx;
	if (hm_f != hm_0)        // a move was made
			{
		// update list for moved checker
		checkerPos[hm_f] = checkerPos[hm_0];
		checkerPos[hm_0] = 'n';

		float hSz = chSz / 2;

		// King me!
		justKinged = false;
		float xf = (float) (anchorArr1[hm_f].first) - hSz;
		float yf = (float) (anchorArr1[hm_f].second) - hSz;
		if (turn && hm_f > 27 && checkerPos[hm_f] != 'W') {
			checkerPos[hm_f] = 'W';
//            chObj.pSprite = &wh_kSprite;
			*kingMePath.ppSprite = &wh_chSprite;
			p_kingMePathLeg->INIT(wh_captX + (Nwh_capt - 1) * capt_dx, wh_captY,
					xf, yf, 20.0f);
			justKinged = true;
		}
		if (!turn && hm_f < 4 && checkerPos[hm_f] != 'B') {
			checkerPos[hm_f] = 'B';
//            chObj.pSprite = &bk_kSprite;
			*kingMePath.ppSprite = &bk_chSprite;
			p_kingMePathLeg->INIT(bk_captX + (Nbk_capt - 1) * capt_dx, bk_captY,
					xf, yf, 20.0f);
			justKinged = true;
		}

		// was a jump made?
		int jumpIdx = 0;
		jumpMade = didJump(hm_0, hm_f, jumpIdx);
		if (jumpMade) {
			// for the capture animation
			colorCapt = checkerPos[jumpIdx];
			checkerPos[jumpIdx] = 'n';        // remove checker from board
			animateCapt = true;
			float xi = (float) (anchorArr1[jumpIdx].first) - hSz;
			float yi = (float) (anchorArr1[jumpIdx].second) - hSz;

			if (colorCapt == 'w' || colorCapt == 'W')
				p_aniPathLeg->INIT(xi, yi, wh_captX + Nwh_capt * capt_dx,
						wh_captY, 40.0f);
			else
				p_aniPathLeg->INIT(xi, yi, bk_captX + Nbk_capt * capt_dx,
						bk_captY, 40.0f);

			switch (colorCapt) {
			case 'w':
				*aniPath.ppSprite = &wh_chSprite;
				break;
			case 'W':
				*aniPath.ppSprite = &wh_kSprite;
				break;
			case 'b':
				*aniPath.ppSprite = &bk_chSprite;
				break;
			case 'B':
				*aniPath.ppSprite = &bk_kSprite;
				break;
			default:
				break;
			}
			aniPath.reset(true, 0);

			// see if another jump can be made
			canJump = false;
			if (!justKinged)
				canJump = fillMoveList(hm_f);
		} else
			canJump = false;        // no jump = no next jump

		if (!canJump)
			turn = !turn;        // change turns
	}

	return;
}        // end of gameHitUp()

void gameLogic(void) {
// the checker deal animation
	if (reset) {
		wh_dealPath.move();
		bk_dealPath.move();
		if (!wh_dealPath.inUse && !bk_dealPath.inUse) // timer went off. Animation is done
				{
			reset = false;
			gameOn = true;
		}
	}

	if ((animateCapt || animateSplit) && gameOn)
		gameCapture_SplitAniLogic();

// test for end of game
	if ((Nwh_capt == 12 || Nbk_capt == 12) && !gameOver) {
		gameOver = true;
		textFX = true;
		textFXdelay = 30;

		if (Nwh_capt == 12)
			p_FXmsg = &msg_BLACKWINS;
		else
			p_FXmsg = &msg_WHITEWINS;

		textExpand(*p_FXmsg, 1.0f, 7.0f, 50, true);
		textFade(*p_FXmsg, 255, 1, 50, true);
	}

	if (!gameOver)
		gameKingMeAniLogic();

// textFX
	if (textFX) {
		if (textFXdelay > 1)
			--textFXdelay;
		else {
			textFX = textExpand(*p_FXmsg, 1.0f, 7.0f, 50);
			textFade(*p_FXmsg, 255, 1, 50);
		}
	}

	return;
}

void gameDraw(sf::RenderWindow& rApp) {
	newButt.draw();        // game reset
	savedButt.draw();

	if (gameOn)
		saveGameButt.draw();

	rApp.draw(boardSprite);
	drawCheckers(rApp);
	if (textFX)
		rApp.draw(*p_FXmsg);

	return;
}

// text effects functions
bool textExpand(sf::Text& r_text, float scale_i, float scale_f, int Nframes,
		bool reset) {
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

bool textFade(sf::Text& r_text, int alpha_i, int alpha_f, int Nframes,
		bool reset) {
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
