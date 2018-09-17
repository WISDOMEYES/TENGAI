#include "stdafx.h"
#include "mainGame.h"

//생성자랑 소멸자는 쓰지 않는당..//
mainGame::mainGame()
{

}
//생성자랑 소멸자는 쓰지 않는당..//
mainGame::~mainGame()
{

}
HRESULT mainGame::init(void)
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("스타팅 화면", "other/start_background.bmp", WINSIZEX, WINSIZEY, true, RGB(128, 128, 255));

	IMAGEMANAGER->addImage("이치고", "other/start_ichigo.bmp", 381, 764, true, RGB(128, 128, 255));
	IMAGEMANAGER->addImage("루피", "other/start_luffy.bmp", 398, 726, true, RGB(128, 128, 255));
	IMAGEMANAGER->addImage("나루토", "other/start_naruto.bmp", 359, 754, true, RGB(128, 128, 255));

	IMAGEMANAGER->addImage("이치고 선택시", "other/select_ichigo.bmp", 394, 777, true, RGB(128, 128, 255));
	IMAGEMANAGER->addImage("루피 선택시", "other/select_luffy.bmp", 413, 742, true, RGB(128, 128, 255));
	IMAGEMANAGER->addImage("나루토 선택시", "other/select_naruto.bmp", 373, 769, true, RGB(128, 128, 255));

	isButtonDown = false;
	Pnumber = 0;
	check = false;
	prolog = false;

	IMAGEMANAGER->addImage("게임오버", "other/gameover.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
	
	IMAGEMANAGER->addImage("게임클리어", "other/gameclear.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));

	UI = new image;
	IMAGEMANAGER->addFrameImage("캐릭터상태창","other/UI.bmp", 0, 0, 332, 110, 3, 1, true, RGB(128, 128, 255));
	IMAGEMANAGER->addImage("상태창배경", "other/bUI.bmp", 110, 110, true, RGB(128, 128, 255));


	_player = new player;
	_boss = new boss;


	_player->setbossMemoryAdressLink(_boss);
	_boss->setplayerMemoryAdressLink(_player);
	return S_OK;
}
void mainGame::release(void)
{
	gameNode::release();
	SAFE_DELETE(_player);
	SAFE_DELETE(_boss);

}
void mainGame::update(void)
{
	gameNode::update();

	if (!prolog)
	{
		if (KEYMANAGER->isonceKeyDown(VK_LEFT))
		{
			if (!isButtonDown) {
				isButtonDown = true;
				Pnumber = 2;
			}
			Pnumber--;
			if (Pnumber < 0) { Pnumber = 2; }
		}

		if (KEYMANAGER->isonceKeyDown(VK_RIGHT))
		{
			if (!isButtonDown) {
				isButtonDown = true;
				Pnumber = 0;
			}
			Pnumber++;
			if (Pnumber > 2) { Pnumber = 0; }
		}

		if (KEYMANAGER->isonceKeyUp(VK_SPACE))
		{
			prolog = true;
			_boss->init();
			_player->init(Pnumber);
			UI = IMAGEMANAGER->findImage("캐릭터상태창");
			UI->setFrameX(Pnumber);
		}
	}

	if (KEYMANAGER->isonceKeyUp(VK_TAB))
	{
		if (check) { check = false; }
		else check = true;
	}
	
}
void mainGame::render(void)
{
	//건들지 말것
	//==================================================//
	PatBlt(getMemDc(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================================================//

	if (!prolog)
	{
		IMAGEMANAGER->render("스타팅 화면", getMemDc());
		if (isButtonDown)
		{
			switch (Pnumber)
			{
			case 0:
				IMAGEMANAGER->render("이치고 선택시", getMemDc(), 14, 14);
				break;
			case 1:
				IMAGEMANAGER->render("루피 선택시", getMemDc(), WINSIZEX / 3 + 42, 22);
				break;
			case 2:
				IMAGEMANAGER->render("나루토 선택시", getMemDc(), WINSIZEX / 3 * 2 + 93, 13);
				break;
			}
		}

		IMAGEMANAGER->render("이치고", getMemDc(), 20, 20);
		IMAGEMANAGER->render("나루토", getMemDc(), WINSIZEX / 3 * 2 + 100, 20);
		IMAGEMANAGER->render("루피", getMemDc(), WINSIZEX / 3 + 50, 30);
	}


	if (prolog)
	{
		_boss->update();
		_player->update();
		_boss->render(check);
		_player->render(check);

		IMAGEMANAGER->render("상태창배경", getMemDc(),0,0);
		UI->frameRender(getMemDc(), 0, 0, UI->getFrameX(), 0);
		
		if (_player->gameover())
		{
			IMAGEMANAGER->render("게임오버", getMemDc());
		}
		else if (_boss->gameclear())
		{
			IMAGEMANAGER->render("게임클리어", getMemDc());
		}
	}

	//얘도 건들지 말것
	//==================================================//
	this->getBackBuffer()->render(getHDC(), 0, 0);
	//==================================================//
	//위에 건들지 마라 경고한다~~~//
}
