#include "dragDrop.h"

sf::RenderWindow* dragDrop::pWndw = NULL;
float dragDrop::snap_speed = 30.0f;

dragDrop::dragDrop(int PosX, int PosY, sf::Sprite* p_Sprite) :
		pSprite(p_Sprite), posX(PosX), posY(PosY) {
	grabX = grabY = 0;
	held = false;
	docked = true;

	// call INITanchors() to assign values for the following
	p_anchorPos = NULL; // these values will result in "free" dragging behavior
	Nanchors = 0;
	homeIdx = 0;
}

dragDrop::~dragDrop() {
}

void dragDrop::set_anchors(std::pair<int, int>* p_AnchorArr, int arrSize,
		int HomeIdx) {
	p_anchorPos = p_AnchorArr;
	Nanchors = arrSize;
	homeIdx = HomeIdx;
}

void dragDrop::draw(void) {
	pSprite->setPosition(static_cast<float>(posX), static_cast<float>(posY));

	if (pWndw)
		pWndw->draw(*pSprite);

	return;
}

bool dragDrop::grab(int mseX, int mseY) // call on LBUTT down
		{
	if (hit(mseX, mseY)) {
		held = true;
		docked = false; // snap() will act - NEW
		grabX = mseX - posX;
		grabY = mseY - posY;
	}
	return held;
}

void dragDrop::release(void) // call on LBUTT up
		{
	if (held) {
		held = false;
		if (p_anchorPos) {
			//    docked = false;// snap() will act
			for (int i = 0; i < Nanchors; ++i)
				if (i != homeIdx && hitAnchor(i)) {
					homeIdx = i; // new anchor position
					break;
				}
		}
	}
	return;
}

// overload
void dragDrop::release(int* p_IdxList, int listSz) {
	if (held) {
		held = false;
		if (p_anchorPos) {
			docked = false; // snap() will act
			for (int i = 0; i < listSz; ++i)
				if (hitAnchor(p_IdxList[i])) {
					homeIdx = p_IdxList[i]; // new anchor position
					break;
				}
		}
	}
	return;
}

void dragDrop::drag(int mseX, int mseY) {
	if (held) {
		posX = mseX - grabX;
		posY = mseY - grabY;
	}
}

