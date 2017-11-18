#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include "Graphics/dragDropRect.h"

#include "Data/GameData.h"

#include "Graphics/Sprites.h"
#include "Graphics/Menu.h"
#include "Graphics/Animations.h"
#include "Graphics/Drawing.h"

#include "Database/Database.h"

#include "Actions/MenuHit.h"
#include "Actions/GameHit.h"

void checkEvents(sf::Event &event, sf::Window &window, GameData &gdata,
		Animations &ganimators, Menu &gmenu, Database &gdatabase,
		MenuHit &gmenuHit, GameHit &ggameHit);
void gameAnimations(Animations &ganimators);

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

	try {
		Database gdatabase;
		Sprites gsprites(150, 50);
		gsprites.initText();
		Menu gmenu(gsprites);
		gmenu.initButtons();
		GameData gdata(gsprites);
		gdata.initBoard();
		Animations ganimators(gdata, gdatabase);
		ganimators.initPaths();
		ganimators.initDragDrops();
		MenuHit gmenuHit(ganimators, gmenu);
		GameHit ggameHit(ganimators);

		// create the SFML window
		sf::RenderWindow window(sf::VideoMode(gdata.w_szX, gdata.w_szY),
				"Checkers");
		window.setActive();

		Drawing gdrawer(&window, ganimators, gmenu);

		// local vars
		float frPeriod = 1.0f / 30.0f; // for 30 fps
		sf::Clock frClock;
		frClock.restart();

//		button::pWndw = &window;
		ganimators.wh_dealPath.inUse = false;
		ganimators.bk_dealPath.inUse = false;

		window.setVerticalSyncEnabled(true); // default = false

		gdata.last_move_clock.restart();

		if (window.isOpen()) {
			do {
				if (!gdata.pause
						&& frClock.getElapsedTime().asSeconds() > frPeriod) {
					frClock.restart();
					gameAnimations(ganimators);

					// draw stuff
					window.clear(sf::Color(0, 50, 100)); // Color bkgd

					gdrawer.gameDraw(window);

					window.display();
				}

				sf::Event event;
				while (window.pollEvent(event)) {
					checkEvents(event, window, gdata, ganimators, gmenu,
							gdatabase, gmenuHit, ggameHit);
				}
			} while (window.isOpen());
		}
	} catch (std::exception &e) {
		perror(e.what());
	}

	return 0;
} // end of main

void checkEvents(sf::Event &event, sf::Window &window, GameData &gdata,
		Animations &ganimators, Menu &gmenu, Database &gdatabase,
		MenuHit &gmenuHit, GameHit &ggameHit) {
	switch (event.type) {
	case sf::Event::Closed:
		window.close();
		break;
	case sf::Event::MouseButtonPressed:
		if (!gdata.pause && event.mouseButton.button == sf::Mouse::Left) {
			if (!gmenuHit.menuHitDown()) {
				window.close(); // file I/O error
			}
			ggameHit.gameHitDown();
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (!gdata.pause && event.mouseButton.button == sf::Mouse::Left) {
			gmenuHit.menuHitUp();
			ggameHit.gameHitUp();
		}
		break;
	case sf::Event::MouseMoved:
		gdata.mseX = event.mouseMove.x;
		gdata.mseY = event.mouseMove.y;

		// button mouseovers
		gmenu.newButt.mseOver(gdata.mseX, gdata.mseY);
		gmenu.savedButt.mseOver(gdata.mseX, gdata.mseY);

		if (gdata.gameOn) {
			gmenu.saveGameButt.mseOver(gdata.mseX, gdata.mseY);
		}

		// dragDrop object move
		ganimators.chObj.drag(gdata.mseX, gdata.mseY);

		break;
	case sf::Event::KeyPressed:
		switch (event.key.code) {
		case sf::Keyboard::Escape: // kill app via escape key
			//	Cleanup();
			window.close();
			break;
		case sf::Keyboard::P:			// provides a play/pause function
			gdata.pause = !gdata.pause;			// toggle state
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void gameAnimations(Animations &ganimators) {
	// the checker deal animation
	if (ganimators.gdata.reset) {
		ganimators.wh_dealPath.move();
		ganimators.bk_dealPath.move();
		if (!ganimators.wh_dealPath.inUse && !ganimators.bk_dealPath.inUse) // timer went off. Animation is done
				{
			ganimators.gdata.reset = false;
			ganimators.gdata.gameOn = true;
		}
	}

	if ((ganimators.animateCapt || ganimators.animateSplit)
			&& ganimators.gdata.gameOn) {
		ganimators.gameCapture_SplitAniLogic();
	}

	// test for end of game
	if ((ganimators.Nwh_capt == 12 || ganimators.Nbk_capt == 12)
			&& !ganimators.gdata.gameOver) {
		ganimators.gdata.gameOver = true;
		ganimators.textFX = true;
		ganimators.textFXdelay = 30;

		if (ganimators.Nwh_capt == 12) {
			ganimators.gsprites.p_FXmsg = &ganimators.gsprites.msg_BLACKWINS;
		} else {
			ganimators.gsprites.p_FXmsg = &ganimators.gsprites.msg_WHITEWINS;
		}

		ganimators.textExpand(*ganimators.gsprites.p_FXmsg, 1.0f, 7.0f, 50,
				true);
		ganimators.textFade(*ganimators.gsprites.p_FXmsg, 255, 1, 50, true);
	}

	if (!ganimators.gdata.gameOver) {
		ganimators.gameKingMeAniLogic();
	}

	// textFX
	if (ganimators.textFX) {
		if (ganimators.textFXdelay > 1) {
			--ganimators.textFXdelay;
		} else {
			ganimators.textFX = ganimators.textExpand(
					*ganimators.gsprites.p_FXmsg, 1.0f, 7.0f, 50, false);
			ganimators.textFade(*ganimators.gsprites.p_FXmsg, 255, 1, 50,
					false);
		}
	}

	return;
}

