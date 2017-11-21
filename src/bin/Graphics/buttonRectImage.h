#ifndef BUTTONRECTIMAGE_H
#define BUTTONRECTIMAGE_H

#include "bin/Graphics/buttonRect.h"

class buttonRectImage: public buttonRect {
public:
	sf::Sprite* pSprite;

	// functions
	virtual void draw(sf::RenderWindow *pWndw);
	void assign_Sprite(sf::Sprite* p_Sprite);

	buttonRectImage(char Type, int PosX, int PosY, sf::Sprite* p_Sprite);
	~buttonRectImage();
};

#endif // BUTTONRECTIMAGE_H
