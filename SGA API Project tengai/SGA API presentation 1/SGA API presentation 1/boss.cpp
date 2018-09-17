#include "stdafx.h"
#include "boss.h"
#include"player.h"



boss::boss()
{
}


boss::~boss()
{
}

HRESULT boss::init(void)
{
	bgcheck = true;
	_background = new image;
	_num = 1;

	enemy = new image;
	x = WINSIZEX - 200;
	y = WINSIZEY / 2;

	initcheck = true;
	movedelay = 0;
	index = count = 0;

	endaction = false;
	maxaction = 0;
	maxstack = 0;
	stack = 0;

	delay = 0;
	hitok = false;

	bossheart = new image;
	bossheart = IMAGEMANAGER->addImage("보스하트", "bossimage/boss_heart.bmp", WINSIZEX - 370, 20, 339, 30, true, RGB(255, 0, 255));
	ratioheart = 339;

	isclear = false;
	return S_OK;
}

void boss::release(void)
{
}

void boss::update(void)
{
	makeBackground(_num);

	//보스 이미지 등 초기화
	if (initcheck)
	{
		switch (_num)
		{
		case 1:
			IMAGEMANAGER->addFrameImage("오른쪽/왼쪽", "bossimage/boss_1/boss_1RL.bmp", x, y, 510, 126, 5, 2, true, RGB(0, 0, 0));
			IMAGEMANAGER->addFrameImage("위/아래", "bossimage/boss_1/boss_1UD.bmp", x, y, 286, 198, 5, 2, true, RGB(0, 0, 0));
			bossrc = RectMakeCenter(x, y, 102, 99);
			maxstack = 2;
			maxaction = 4;
			bossheartmax = 300;
			ratio = 1.13;
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		}
		initcheck = false;
	}

	//보스 행동패턴 하나하나

	if (!endaction)
	{
		endaction = true;
		rand = RND->getFromIntTo(1, maxaction);
	}

	switch (_num)
	{
	case 1:
		boss1action(rand);
		break;
	case 2:
		boss2action(rand);
		break;
	case 3:
		boss3action(rand);
		break;
	case 4:
		boss4action(rand);
		break;
	case 5:
		boss5action(rand);
		break;
	}

	if (delay >= 100)
	{
		delay = 100;
		hitok = true;
	}

	delay++;

	collision();
}

void boss::render(bool check)
{
	_background->render(getMemDc());

	enemy->frameRender(getMemDc(), bossrc.left, bossrc.top, enemy->getFrameX(), enemy->getFrameY());

	bossheart->render(getMemDc(), WINSIZEX - 370, 20, 0, 0, ratioheart, 30);

	if (check)
	{
		Rectangle(getMemDc(), bossrc.left, bossrc.top, bossrc.right, bossrc.bottom);
	}
}

//입력값에 따라 배경 변경
void boss::makeBackground(int bgnum)
{
	if (bgcheck)
	{
		switch (bgnum)
		{
		case 1:
			_background = IMAGEMANAGER->addImage("보스 1 배경화면", "bossimage/boss_1/background_1.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
			bgcheck = false;
			break;
		case 2:
			_background = IMAGEMANAGER->addImage("보스 2 배경화면", "bossimage/boss_2/background_2.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
			bgcheck = false;
			break;
		case 3:
			_background = IMAGEMANAGER->addImage("보스 3 배경화면", "bossimage/boss_3/background_3.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
			bgcheck = false;
			break;
		case 4:
			_background = IMAGEMANAGER->addImage("보스 4 배경화면", "bossimage/boss_4/background_4.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
			bgcheck = false;
			break;
		case 5:
			_background = IMAGEMANAGER->addImage("보스 5 배경화면", "bossimage/boss_5/background_5.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
			bgcheck = false;
			break;
		}
	}
}

void boss::boss1action(int random)
{
	if (!isclear)
	{

		if (random == 1 || random == 2)
		{
			enemy = IMAGEMANAGER->findImage("오른쪽/왼쪽");
		}
		else
		{
			enemy = IMAGEMANAGER->findImage("위/아래");
		}
		if (random == 2 || random == 4)
		{
			enemy->setFrameY(1);
		}
		else
		{
			enemy->setFrameY(0);
		}
		count++;
		if (count % 10 == 0)
		{
			if (random == 1 || random == 2)
			{
				enemy->setFrameX(index);
			}
			else
			{
				enemy->setFrameX(enemy->getMaxFrameX() - index);
			}
			if (index >= enemy->getMaxFrameX())
			{
				endaction = false;
				count = index = 0;
			}
			else { index++; }
		}
		switch (random)
		{
		case 1:
			if (bossrc.right <= WINSIZEX)
			{
				bossrc.left += 5;
				bossrc.right += 5;
			}
			break;
		case 2:
			if (bossrc.left >= 0)
			{
				bossrc.left -= 5;
				bossrc.right -= 5;
			}
			break;
		case 3:
			if (bossrc.top >= 120)
			{
				bossrc.top -= 5;
				bossrc.bottom -= 5;
			}
			break;
		case 4:
			if (bossrc.bottom <= WINSIZEY)
			{
				bossrc.top += 5;
				bossrc.bottom += 5;
			}
			break;
		}
	}
}

void boss::boss2action(int random)
{
}

void boss::boss3action(int random)
{
}

void boss::boss4action(int random)
{
}

void boss::boss5action(int random)
{
}

void boss::hit(int damage)
{
	bossheartmax -= damage;
	ratioheart = bossheartmax*ratio;
	if (ratioheart <= 0)
	{
		isclear = true;
	}
}

void boss::collision()
{
	RECT rc;
	if (IntersectRect(&rc, &bossrc, &_player->getplayerrect()))
	{
		if (hitok)
		{
			_player->hit();
			delay = 0;
			hitok = false;
		}
	}
}
