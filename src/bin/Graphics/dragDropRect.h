#ifndef DRAGDROPRECT_H
#define DRAGDROPRECT_H

#include <SFML/Graphics.hpp>
#include <vector>

class dragDropRect {
public:
//	float snap_speed;

// member vars
	sf::Sprite* pSprite;
	int posX;
	int posY;
	int grabX;
	int grabY;
	bool held; // true during drag operation
	bool docked; // true when ddObj is anchored

	std::pair<int, int>* p_anchorPos; // array of allowed destination points in drag op.
	int Nanchors; // # of pairs in array pointed to by p_anchorPos
	int homeIdx; // index to home location among anchor array elements

	int szX = 0;
	int szY = 0;

	// functions
	bool hit(int mseX, int mseY); // pure virtual in base - called by grab()
	void snap(void); // pure virtual in base
	bool hitAnchor(int idx); // pure virtual in base - called by release()
	void assign_Size(sf::Sprite* p_Sprite = NULL);

	void draw(sf::RenderWindow *pWndw);
	bool grab(int mseX, int mseY); // call on LBUTT down - calls hit()
	void release(void); // call on LBUTT up - calls hitAnchor()
	void release(int* p_IdxList, int listSz); // for use when given a sub-list of anchors from a larger array of anchors
	void drag(int mseX, int mseY); // call in frame logic

	// for INIT of anchors
	void set_anchors(std::pair<int, int>* p_AnchorArr, int arrSize,
			int homeIdx);

	dragDropRect(int PosX, int PosY, sf::Sprite* p_Sprite);
};

#endif // DRAGDROPRECT_H
