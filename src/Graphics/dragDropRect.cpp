#include "Graphics/dragDropRect.h"

dragDropRect::dragDropRect(int PosX, int PosY, sf::Sprite* p_Sprite) :
		dragDrop(PosX, PosY, p_Sprite) {

}

dragDropRect::~dragDropRect() {
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
