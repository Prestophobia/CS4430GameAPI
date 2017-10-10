#ifndef DRAGDROP_H
#define DRAGDROP_H

#include <SFML/Graphics.hpp>
#include <vector>

class dragDrop {
public:
	// static vars
	static sf::RenderWindow* pWndw;
//	static int* p_mseX;
//	static int* p_mseY;
	const static int& r_mseX;
	const static int& r_mseY;
	static float snap_speed;

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

	// functions
	virtual bool hit(void) = 0; // depends on shape ( rect, circle, ? )
	virtual bool hitAnchor(int idx) = 0;
	virtual void snap(void) = 0; // carries out snap-to motion in frame logic. Shape dependent.

	void draw(void);
	bool grab(void); // call on LBUTT down - calls hit()
	void release(void); // call on LBUTT up - calls hitAnchor()
	void release(int* p_IdxList, int listSz); // for use when given a sub-list of anchors from a larger array of anchors
	void drag(void); // call in frame logic

	// for INIT of anchors
	void set_anchors(std::pair<int, int>* p_AnchorArr, int arrSize,
			int homeIdx);

	dragDrop(int PosX, int PosY, sf::Sprite* p_Sprite);
	virtual ~dragDrop();
};

#endif // DRAGDROP_H
