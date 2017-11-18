#include "buttonRect.h"

buttonRect::buttonRect(char Type, int PosX, int PosY, int SzX, int SzY) :
		button(Type, PosX, PosY), szX(SzX), szY(SzY) {
}

buttonRect::~buttonRect() {
}

bool buttonRect::hit(int mseX, int mseY) {
	if (mseX < posX)
		return false;
	if (mseX > posX + szX)
		return false;
	if (mseY < posY)
		return false;
	if (mseY > posY + szY)
		return false;

	return true;
}

void buttonRect::set_label(const sf::Text Label) {
	label = Label;
	float fposX = static_cast<float>(posX); // fix this!
	float fposY = static_cast<float>(posY);
	float fszX = static_cast<float>(szX);
	float fszY = static_cast<float>(szY);

	sf::FloatRect sR = label.getGlobalBounds();
	float len = sR.width;
	float hgt = sR.height;

	switch (labelPos) {
	case 'c': // centered
		label.setPosition((2.0f * fposX + fszX - len) / 2.0f,
				(2.0f * fposY + fszY - hgt) / 2.0f - 1.5f);
		break;
	case 'l': // left side
		label.setPosition(fposX - len - 3.0f,
				(2.0f * fposY + fszY - hgt) / 2.0f - 1.5f);
		break;
	case 'r': // right side
		label.setPosition(fposX + fszX + 3.0f,
				(2.0f * fposY + fszY - hgt) / 2.0f - 1.5f);
		break;
	case 't': // on top
		label.setPosition((2.0f * fposX + fszX - len) / 2.0f,
				fposY - hgt - 3.0f);
		break;
	case 'b': // below
		label.setPosition((2.0f * fposX + fszX - len) / 2.0f,
				fposY + fszY - 1.0f);
		break;
	default:
		break;
	}

	return;
} // end of set_label()
