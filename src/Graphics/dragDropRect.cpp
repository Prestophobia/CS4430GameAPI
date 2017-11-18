#include "Graphics/dragDropRect.h"

dragDropRect::dragDropRect(int PosX, int PosY, sf::Sprite* p_Sprite) :
		posX(PosX), posY(PosY), pSprite(p_Sprite) {
	grabX = grabY = 0;
	held = false;
	docked = true;

	// call INITanchors() to assign values for the following
	p_anchorPos = NULL; // these values will result in "free" dragging behavior
	Nanchors = 0;
	homeIdx = 0;
}

void dragDropRect::assign_Size(sf::Sprite* p_Sprite) {
	if (p_Sprite)
		pSprite = p_Sprite; // may have been assigned on construction

	const sf::Texture* pImg = pSprite->getTexture();
	if (pImg) {
		sf::Vector2u size = pImg->getSize();
		szX = size.x;
		szY = size.y;

		if (p_anchorPos && homeIdx < Nanchors && homeIdx >= 0) {
			posX = p_anchorPos[homeIdx].first - szX / 2;
			posY = p_anchorPos[homeIdx].second - szY / 2;
			docked = true;
		}
	}
}

bool dragDropRect::hit(int mseX, int mseY) // pure virtual in base
		{
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

void dragDropRect::snap(void) // pure virtual in base
		{
	if (!held && !docked) {
		// instant transport for initial testing
		posX = p_anchorPos[homeIdx].first - szX / 2;
		posY = p_anchorPos[homeIdx].second - szY / 2;
		docked = true;
	}
}

bool dragDropRect::hitAnchor(int idx) // pure virtual in base
		{
	if (p_anchorPos[idx].first < posX)
		return false;
	if (p_anchorPos[idx].first > posX + szX)
		return false;
	if (p_anchorPos[idx].second < posY)
		return false;
	if (p_anchorPos[idx].second > posY + szY)
		return false;

	return true;
}

void dragDropRect::set_anchors(std::pair<int, int>* p_AnchorArr, int arrSize,
		int HomeIdx) {
	p_anchorPos = p_AnchorArr;
	Nanchors = arrSize;
	homeIdx = HomeIdx;
}

void dragDropRect::draw(sf::RenderWindow *pWndw) {
	pSprite->setPosition(static_cast<float>(posX), static_cast<float>(posY));

	if (pWndw)
		pWndw->draw(*pSprite);

	return;
}

bool dragDropRect::grab(int mseX, int mseY) // call on LBUTT down
		{
	if (hit(mseX, mseY)) {
		held = true;
		docked = false; // snap() will act - NEW
		grabX = mseX - posX;
		grabY = mseY - posY;
	}
	return held;
}

void dragDropRect::release(void) // call on LBUTT up
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
void dragDropRect::release(int* p_IdxList, int listSz) {
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

void dragDropRect::drag(int mseX, int mseY) {
	if (held) {
		posX = mseX - grabX;
		posY = mseY - grabY;
	}
}
