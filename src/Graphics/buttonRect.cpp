#include "buttonRect.h"

buttonRect::buttonRect(char Type, int PosX, int PosY, int SzX, int SzY) :
		szX(SzX), szY(SzY) {
	posX = PosX;
	posY = PosY;
	sel = mo = false;
	type = 's'; // default is selection type
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

bool buttonRect::mseOver(int mseX, int mseY) {
	switch (type) {
	case 's':
		if (!sel && hit(mseX, mseY))
			mo = true;
		else
			mo = false;
		break;
	case 't':
		if (hit(mseX, mseY))
			mo = true;
		else
			mo = false;
		break;
	case 'm':
		if (hit(mseX, mseY))
			mo = true;
		else
			mo = sel = false;
		break;
	}
	return mo;
}

bool buttonRect::hit_dn(int mseX, int mseY) {
	switch (type) {
	case 's':
		if (!sel && hit(mseX, mseY)) {
			sel = true;
			mo = false;
		}
		break;
	case 't':
		if (hit(mseX, mseY))
			sel = !sel;
		break;
	case 'm':
		if (hit(mseX, mseY))
			sel = true;
		break;
	}
	return hit(mseX, mseY);
} // end of hit_dn()

void buttonRect::hit_up(void) {
	if (type == 'm')
		sel = false;
	return;
}

void buttonRect::INITlabel(const sf::Text Label, sf::Color txtColor,
		char LabelPos) {
	labelPos = LabelPos;

	label.setFillColor(txtColor);
	set_label(Label);

	return;
} // end of INITlabel()
