#include "button.h"

// static vars INIT
sf::RenderWindow* button::pWndw = NULL;

button::button(void) {
	posX = 0;
	posY = 0;
	sel = false;
	mo = false;
	type = 's'; // default is selection type
}

button::button(char Type, int PosX, int PosY) :
		posX(PosX), posY(PosY), type(Type) {
	sel = mo = false;
}

button::~button(void) {
}

bool button::mseOver(void) {
	switch (type) {
	case 's':
		if (!sel && hit())
			mo = true;
		else
			mo = false;
		break;
	case 't':
		if (hit())
			mo = true;
		else
			mo = false;
		break;
	case 'm':
		if (hit())
			mo = true;
		else
			mo = sel = false;
		break;
	}
	return mo;
}

bool button::hit_dn(void) {
	switch (type) {
	case 's':
		if (!sel && hit()) {
			sel = true;
			mo = false;
		}
		break;
	case 't':
		if (hit())
			sel = !sel;
		break;
	case 'm':
		if (hit())
			sel = true;
		break;
	}
	return hit();
} // end of hit_dn()

void button::hit_up(void) {
	if (type == 'm')
		sel = false;
	return;
}

void button::INITlabel(const sf::Text Label, sf::Color txtColor,
		char LabelPos) {
	labelPos = LabelPos;

	label.setFillColor(txtColor);
	set_label(Label);

	return;
} // end of INITlabel()