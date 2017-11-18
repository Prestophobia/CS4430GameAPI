#include "Graphics/buttonRectImage.h"

buttonRectImage::buttonRectImage(char Type, int PosX, int PosY,
		sf::Sprite* p_Sprite) :
		buttonRect(Type, PosX, PosY, 10, 10), pSprite(p_Sprite) {
	if (pSprite) {
		const sf::Texture* pImg = pSprite->getTexture();
		if (pImg) {
			sf::Vector2u size = pImg->getSize();
			szX = size.x / 2;
			szY = size.y / 2;
		}
	}
}

buttonRectImage::~buttonRectImage() {
}

void buttonRectImage::assign_Sprite(sf::Sprite* p_Sprite) {
	pSprite = p_Sprite;
	const sf::Texture* pImg = pSprite->getTexture();
	if (pImg) {
		sf::Vector2u size = pImg->getSize();
		szX = size.x / 2;
		szY = size.y / 2;
	}
}

void buttonRectImage::draw(sf::RenderWindow *pWndw) {
	sf::IntRect srcRect;
	srcRect.top = sel ? szY + 1 : 0;
	srcRect.left = mo ? szX + 1 : 0;
	srcRect.height = szY;
	srcRect.width = szX;
	pSprite->setTextureRect(srcRect);
	pSprite->setPosition(static_cast<float>(posX), static_cast<float>(posY));

	if (pWndw) {
		pWndw->draw(*pSprite);
		pWndw->draw(label);
	}
	return;
}
