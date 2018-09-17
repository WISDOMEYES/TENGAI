#include "stdafx.h"
#include "spaceShip.h"


spaceShip::spaceShip()
{
}


spaceShip::~spaceShip()
{
}

HRESULT spaceShip::init(void)
{
	_ship = IMAGEMANAGER->addImage("플레이어", "rocket.bmp", 52, 64, true, RGB(255, 0, 255));
	_ship->setX(WINSIZEX / 2);
	_ship->setY(WINSIZEY / 2 + 200);

	_missile = new missile;
	_missile->init(30, 400);

	_thaad = new thaadMissile;
	_thaad->init(30, 500);

	return S_OK;
}

void spaceShip::release(void)
{
	SAFE_DELETE(_missile);
	SAFE_DELETE(_thaad);
}

void spaceShip::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _ship->getX() > 0)
	{
		_ship->setX(_ship->getX() - 5);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _ship->getX() + _ship->getWidth() < WINSIZEX)
	{
		_ship->setX(_ship->getX() + 5);
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && _ship->getY() > 0)
	{
		_ship->setY(_ship->getY() - 5);
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _ship->getY() + _ship->getHeight() < WINSIZEY)
	{
		_ship->setY(_ship->getY() + 5);
	}
	if (KEYMANAGER->isonceKeyDown(VK_SPACE))
	{
		_missile->fire(_ship->getX() + _ship->getWidth() / 2, _ship->getY() - 30);
	}
	if (KEYMANAGER->isonceKeyDown('X'))
	{
		_thaad->fire(_ship->getX() + _ship->getWidth() / 2, _ship->getY() - 30);
	}


	_missile->update();
	_thaad->update();

}

void spaceShip::render(void)
{
	IMAGEMANAGER->findImage("플레이어")->render(getMemDc());

	_missile->render();
	_thaad->render();

}
