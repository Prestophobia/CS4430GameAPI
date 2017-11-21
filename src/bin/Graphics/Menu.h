/**
 * @file /CS4430GameAPI/src/Graphics/Menu.h
 * @author Neek
 * @date Nov 16, 2017
 * @brief .
 *
 * @details .
 */

#ifndef GRAPHICS_MENU_H_
#define GRAPHICS_MENU_H_

#include "bin/Graphics/buttonRectImage.h"
#include "bin/Graphics/Sprites.h"

class Menu {
public:
	Sprites &gsprites;

	buttonRectImage newButt { 'm', 50, 100, NULL }; // start a new game
	buttonRectImage savedButt { 'm', 50, 170, NULL }; // save the current game
	buttonRectImage saveGameButt { 'm', 50, 240, NULL }; // start the saved game

	Menu(Sprites &gsprites);
	void initButtons();
};

#endif /* GRAPHICS_MENU_H_ */
