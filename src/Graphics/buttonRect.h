#ifndef BUTTONRECT_H
#define BUTTONRECT_H

#include <SFML/Graphics.hpp>

class buttonRect {
public:
	sf::Text label;
	char labelPos = 0; // l,r,c,t,b

	int posX;
	int posY;
	bool sel;
	bool mo;
	char type; // 's'=select, 't'=toggle, 'm'=momentary contact

	int szX;
	int szY;

	// functions
	bool hit(int mseX, int mseY);
	virtual void draw(sf::RenderWindow *pWndw) = 0;
	void set_label(const sf::Text Label);

	// logic
	bool mseOver(int mseX, int mseY);
	bool hit_dn(int mseX, int mseY);
	void hit_up(void);

	// INIT
	void INITlabel(const sf::Text Label, sf::Color txtColor, char LabelPos);

	// constructors
	buttonRect(char Type, int Posx, int PosY, int SzX, int SzY);
	virtual ~buttonRect();
};

#endif // BUTTONRECT_H
