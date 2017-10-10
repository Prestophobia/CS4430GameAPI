#ifndef BUTTONRECT_H
#define BUTTONRECT_H

#include "button.h"

class buttonRect: public button {
public:
	int szX;
	int szY;

	// functions
	virtual bool hit(void);
	virtual void draw(void) = 0;
	void set_label(const sf::Text Label);

	// constructors
	buttonRect(char Type, int Posx, int PosY, int SzX, int SzY);
	~buttonRect();
};

#endif // BUTTONRECT_H
