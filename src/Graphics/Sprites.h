/**
 * @file /CS4430GameAPI/src/Graphics/Sprites.h
 * @author Neek
 * @date Nov 16, 2017
 * @brief .
 *
 * @details .
 */

#ifndef GRAPHICS_SPRITES_H_
#define GRAPHICS_SPRITES_H_

#include <SFML/Graphics.hpp>

class Sprites {

public:
	// Font
	sf::Font font;

	// Text
	sf::Text msg;
	sf::Text msg_Turn;
	sf::Text msg_Whites;
	sf::Text msg_Blacks;
	sf::Text msg_WELCOME;
	sf::Text msg_GAMEOVER;
	sf::Text msg_WHITEWINS;
	sf::Text msg_BLACKWINS;
	sf::Text* p_FXmsg = &msg_WELCOME;

	// White
	sf::Sprite wh_chSprite;
	sf::Image wh_chImg;
	sf::Texture wh_chTex;
	sf::Sprite wh_kSprite;
	sf::Image wh_kingImg;
	sf::Texture wh_kingTex;

	// Black
	sf::Sprite bk_chSprite;
	sf::Image bk_chImg;
	sf::Texture bk_chTex;
	sf::Sprite bk_kSprite;
	sf::Image bk_kingImg;
	sf::Texture bk_kingTex;

	// Board
	sf::Sprite boardSprite;
	sf::Texture boardTex;

	// Buttons
	sf::Sprite buttSprite1;
	sf::Image buttImg1;
	sf::Texture buttTex1;

	Sprites(float checkerBoardPosX, float checkerBoardPosY);
	void initText(void);
};

#endif /* GRAPHICS_SPRITES_H_ */
