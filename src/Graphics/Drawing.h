/**
 * @file /CS4430GameAPI/src/Graphics/Drawing.h
 * @author Neek
 * @date Nov 16, 2017
 * @brief .
 *
 * @details .
 */

#ifndef GRAPHICS_DRAWING_H_
#define GRAPHICS_DRAWING_H_

#include <SFML/Graphics.hpp>

#include "Data/GameData.h"

#include "Database/Database.h"

#include "Graphics/Sprites.h"
#include "Graphics/Menu.h"
#include "Graphics/Animations.h"

class Drawing {

public:
	sf::RenderWindow *pWndw;

	Sprites &gsprites;
	Menu &gmenu;
	GameData &gdata;
	Animations &ganimators;
	Database &gdatabase;

	Drawing(sf::RenderWindow *pWndw, Animations &ganimators, Menu &gmenu);
	void gameDraw(sf::RenderWindow& rApp);
	void drawCheckers(sf::RenderWindow& rApp);

};

#endif /* GRAPHICS_DRAWING_H_ */
