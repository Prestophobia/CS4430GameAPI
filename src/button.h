#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

#include "Font.h"

class button {
public:
	static sf::RenderWindow* pWndw;
	static const int& r_mseX;
	static const int& r_mseY;
	sf::Text label;
	char labelPos = 0; // l,r,c,t,b

	int posX;
	int posY;
	bool sel;
	bool mo;
	char type; // 's'=select, 't'=toggle, 'm'=momentary contact

	//** functions

	// pure virtual
	virtual bool hit(void) = 0;
	virtual void draw(void) = 0;
	virtual void set_label(const sf::Text Label) = 0; // label position assigned

	// logic
	bool mseOver(void);
	bool hit_dn(void);
	void hit_up(void);

	// INIT
	void INITlabel(const sf::Text Label, sf::Color txtColor,
			char LabelPos);

	// constructors
	button(void);
	button(char Type, int PosX, int PosY);

	// destructor
	virtual ~button(void);
};

#endif // BUTTON_H
