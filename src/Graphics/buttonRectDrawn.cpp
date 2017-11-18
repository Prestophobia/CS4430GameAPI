#include "Graphics/buttonRectDrawn.h"

buttonRectDrawn::buttonRectDrawn() :
		buttonRect('s', 0, 0, 40, 20) {
	selColor = sf::Color(0, 255, 0); // green
	unSelColor = sf::Color(218, 218, 218); // 15% grey
	moColor = sf::Color(255, 255, 102); // yellow
	unMoColor = sf::Color(153, 153, 153); // grey
}

buttonRectDrawn::buttonRectDrawn(char Type, int PosX, int PosY, int SzX,
		int SzY) :
		buttonRect(Type, PosX, PosY, SzX, SzY) {
	selColor = sf::Color(0, 255, 0); // green
	unSelColor = sf::Color(218, 218, 218); // 15% grey
	moColor = sf::Color(255, 255, 102); // yellow
	unMoColor = sf::Color(153, 153, 153); // grey
}

buttonRectDrawn::~buttonRectDrawn(void) {
}

void buttonRectDrawn::set_colors(sf::Color unSel_color, sf::Color sel_color,
		sf::Color unMo_color, sf::Color mo_color) {
	selColor = sel_color;
	unSelColor = unSel_color;
	moColor = mo_color;
	unMoColor = unMo_color;
}

void buttonRectDrawn::draw(void) {
	sf::Color sColor = sel ? selColor : unSelColor;
	sf::Color mColor = mo ? moColor : unMoColor;

	sf::RectangleShape Rect = sf::RectangleShape(
			sf::Vector2f(static_cast<float>(szX), static_cast<float>(szY)));
	Rect.setPosition(static_cast<float>(posX), static_cast<float>(posY));
	Rect.setFillColor(sColor);
	Rect.setOutlineColor(mColor);

	pWndw->draw(Rect);
	pWndw->draw(label);

	return;
}
