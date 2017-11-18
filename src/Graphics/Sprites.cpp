/**
 * @file /CS4430GameAPI/src/Graphics/Sprites.cpp
 * @author Neek
 * @date Nov 16, 2017
 * @brief .
 *
 * @details .
 */

#include "Graphics/Sprites.h"

Sprites::Sprites(float checkerBoardPosX, float checkerBoardPosY) {
	// Font
	font.loadFromFile("images/Enchanted Land.otf");

	// Buttons
	buttImg1.loadFromFile("images/buttonsImageAlt.png");
	buttImg1.createMaskFromColor(sf::Color(0, 0, 0));
	buttTex1.loadFromImage(buttImg1);
	buttSprite1.setTexture(buttTex1);

	// White
	wh_chImg.loadFromFile("images/white_checker.png");
	wh_chImg.createMaskFromColor(sf::Color(0, 0, 0));
	wh_chTex.loadFromImage(wh_chImg);
	wh_chSprite.setTexture(wh_chTex);

	wh_kingImg.loadFromFile("images/white_checker_King.png");
	wh_kingImg.createMaskFromColor(sf::Color(0, 0, 0));
	wh_kingTex.loadFromImage(wh_kingImg);
	wh_kSprite.setTexture(wh_kingTex);

	// Black
	bk_chImg.loadFromFile("images/black_checker.png");
	bk_chImg.createMaskFromColor(sf::Color(0, 0, 0));
	bk_chTex.loadFromImage(bk_chImg);
	bk_chSprite.setTexture(bk_chTex);

	bk_kingImg.loadFromFile("images/black_checker_King.png");
	bk_kingImg.createMaskFromColor(sf::Color(0, 0, 0));
	bk_kingTex.loadFromImage(bk_kingImg);
	bk_kSprite.setTexture(bk_kingTex);

	// Checker Board
	boardTex.loadFromFile("images/checker_board.jpg");
	boardSprite.setTexture(boardTex);
	boardSprite.setPosition(checkerBoardPosX, checkerBoardPosY);
}

void Sprites::initText(void) {
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
