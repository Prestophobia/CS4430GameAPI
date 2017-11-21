/**
 * @file /CS4430GameAPI/src/Graphics/Menu.cpp
 * @author Neek
 * @date Nov 18, 2017
 * @brief .
 *
 * @details .
 */

#include "bin/Graphics/Menu.h"

Menu::Menu(Sprites &gsprites) :
		gsprites(gsprites) {
	initButtons();
}

void Menu::initButtons() {
	newButt.assign_Sprite(&gsprites.buttSprite1);
	newButt.INITlabel(sf::Text("Start New Game", gsprites.font, 16),
			sf::Color(0, 255, 0), 'b');

	savedButt.assign_Sprite(&gsprites.buttSprite1);
	savedButt.INITlabel(sf::Text("Load Saved Game", gsprites.font, 16),
			sf::Color(0, 255, 0), 'b');

	saveGameButt.assign_Sprite(&gsprites.buttSprite1);
	saveGameButt.INITlabel(sf::Text("Save This Game", gsprites.font, 16),
			sf::Color(0, 255, 0), 'b');

	return;
}
