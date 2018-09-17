#include "stdafx.h"
#include "mainGame.h"

//�����ڶ� �Ҹ��ڴ� ���� �ʴ´�..//
mainGame::mainGame()
{

}
//�����ڶ� �Ҹ��ڴ� ���� �ʴ´�..//
mainGame::~mainGame()
{

}
HRESULT mainGame::init(void)
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("��Ÿ�� ȭ��", "other/start_background.bmp", WINSIZEX, WINSIZEY, true, RGB(128, 128, 255));

	IMAGEMANAGER->addImage("��ġ��", "other/start_ichigo.bmp", 381, 764, true, RGB(128, 128, 255));
	IMAGEMANAGER->addImage("����", "other/start_luffy.bmp", 398, 726, true, RGB(128, 128, 255));
	IMAGEMANAGER->addImage("������", "other/start_naruto.bmp", 359, 754, true, RGB(128, 128, 255));

	IMAGEMANAGER->addImage("��ġ�� ���ý�", "other/select_ichigo.bmp", 394, 777, true, RGB(128, 128, 255));
	IMAGEMANAGER->addImage("���� ���ý�", "other/select_luffy.bmp", 413, 742, true, RGB(128, 128, 255));
	IMAGEMANAGER->addImage("������ ���ý�", "other/select_naruto.bmp", 373, 769, true, RGB(128, 128, 255));

	isButtonDown = false;
	Pnumber = 0;
	check = false;
	prolog = false;

	IMAGEMANAGER->addImage("���ӿ���", "other/gameover.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
	
	IMAGEMANAGER->addImage("����Ŭ����", "other/gameclear.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));

	UI = new image;
	IMAGEMANAGER->addFrameImage("ĳ���ͻ���â","other/UI.bmp", 0, 0, 332, 110, 3, 1, true, RGB(128, 128, 255));
	IMAGEMANAGER->addImage("����â���", "other/bUI.bmp", 110, 110, true, RGB(128, 128, 255));


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
			UI = IMAGEMANAGER->findImage("ĳ���ͻ���â");
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
	//�ǵ��� ����
	//==================================================//
	PatBlt(getMemDc(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================================================//

	if (!prolog)
	{
		IMAGEMANAGER->render("��Ÿ�� ȭ��", getMemDc());
		if (isButtonDown)
		{
			switch (Pnumber)
			{
			case 0:
				IMAGEMANAGER->render("��ġ�� ���ý�", getMemDc(), 14, 14);
				break;
			case 1:
				IMAGEMANAGER->render("���� ���ý�", getMemDc(), WINSIZEX / 3 + 42, 22);
				break;
			case 2:
				IMAGEMANAGER->render("������ ���ý�", getMemDc(), WINSIZEX / 3 * 2 + 93, 13);
				break;
			}
		}

		IMAGEMANAGER->render("��ġ��", getMemDc(), 20, 20);
		IMAGEMANAGER->render("������", getMemDc(), WINSIZEX / 3 * 2 + 100, 20);
		IMAGEMANAGER->render("����", getMemDc(), WINSIZEX / 3 + 50, 30);
	}


	if (prolog)
	{
		_boss->update();
		_player->update();
		_boss->render(check);
		_player->render(check);

		IMAGEMANAGER->render("����â���", getMemDc(),0,0);
		UI->frameRender(getMemDc(), 0, 0, UI->getFrameX(), 0);
		
		if (_player->gameover())
		{
			IMAGEMANAGER->render("���ӿ���", getMemDc());
		}
		else if (_boss->gameclear())
		{
			IMAGEMANAGER->render("����Ŭ����", getMemDc());
		}
	}

	//�굵 �ǵ��� ����
	//==================================================//
	this->getBackBuffer()->render(getHDC(), 0, 0);
	//==================================================//
	//���� �ǵ��� ���� ����Ѵ�~~~//
}
