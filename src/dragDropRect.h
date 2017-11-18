#ifndef DRAGDROPRECT_H
#define DRAGDROPRECT_H

#include "dragDrop.h"

class dragDropRect: public dragDrop {
public:
	int szX = 0;
	int szY = 0;

	// functions
	bool hit(int mseX, int mseY); // pure virtual in base - called by grab()
	void snap(void); // pure virtual in base
	bool hitAnchor(int idx); // pure virtual in base - called by release()
	void assign_Size(sf::Sprite* p_Sprite = NULL);

	dragDropRect(int PosX, int PosY, sf::Sprite* p_Sprite);
	~dragDropRect();
};

#endif // DRAGDROPRECT_H
