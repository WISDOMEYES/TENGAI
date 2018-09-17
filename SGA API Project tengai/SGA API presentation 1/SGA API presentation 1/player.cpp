#include "stdafx.h"
#include "player.h"
#include"boss.h"

player::player()
{
}


player::~player()
{
}

HRESULT player::init(int num)
{
	charnum = num;
	x = 100;
	y = WINSIZEY / 2;
	rc = RectMakeCenter(x, y, 30, 30);
	speed = 8;
	delay = 0;
	maxheart = 3;
	situation = idle;
	count = index = 0;
	iskeydown = false;
	fire = swich = isleft = false;
	character = new image;

	heart = new image;
	heart = IMAGEMANAGER->addImage("플레이어하트", "PlayerImage/playerheart.bmp", 54, 48, true, RGB(255, 255, 255));

	isover = false;

	switch (num)
	{
	case 0:

		IMAGEMANAGER->addFrameImage("가만히 있을때", "PlayerImage/ichigo/ichigo_idle.bmp", x, y, 288, 112, 4, 2, true, RGB(128, 128, 255));
		IMAGEMANAGER->addFrameImage("움직일때", "PlayerImage/ichigo/ichigo_move.bmp", x, y, 672, 112, 8, 2, true, RGB(128, 128, 255));
		IMAGEMANAGER->addFrameImage("공격할때", "PlayerImage/ichigo/ichigo_attack.bmp", x, y, 510, 112, 6, 2, true, RGB(128, 128, 255));

		_ichigo = new ichigobullet;

		break;

	case 1:
		IMAGEMANAGER->addFrameImage("가만히 있을때", "PlayerImage/luffy/luffy_idle.bmp", x, y, 330, 103, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("움직일때", "PlayerImage/luffy/luffy_move.bmp", x, y, 277, 106, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("공격할때", "PlayerImage/luffy/luffy_attack.bmp", x, y, 800, 119, 10, 2, true, RGB(255, 0, 255));

		_luffy = new luffybullet;

		break;

	case 2:
		IMAGEMANAGER->addFrameImage("가만히 있을때", "PlayerImage/naruto/naruto_idle.bmp", x, y, 270, 122, 6, 2, true, RGB(0, 128, 0));
		IMAGEMANAGER->addFrameImage("움직일때", "PlayerImage/naruto/naruto_move.bmp", x, y, 277, 106, 6, 2, true, RGB(0, 128, 0));
		IMAGEMANAGER->addFrameImage("공격할때", "PlayerImage/naruto/naruto_attack.bmp", x, y, 290, 120, 5, 2, true, RGB(0, 128, 0));

		_naruto = new narutobullet;

		break;

	}

	return S_OK;
}

void player::release(void)
{
	SAFE_DELETE(_ichigo);
}

void player::update()
{
	if (!isover)
	{
		if (!iskeydown || situation == idle)
		{
			character = IMAGEMANAGER->findImage("가만히 있을때");
			if (isleft) { character->setFrameY(1); }
			else { character->setFrameY(0); }
		}
		if (situation == go)
		{
			character = IMAGEMANAGER->findImage("움직일때");
			iskeydown = true;
		}
		if (situation == attack)
		{
			character = IMAGEMANAGER->findImage("공격할때");
			if (isleft) { character->setFrameY(1); }
			else { character->setFrameY(0); }

			iskeydown = true;
		}

		if (!lock)
		{
			if (KEYMANAGER->isStayKeyDown(VK_LEFT) && rc.left > 0)
			{
				character->setFrameY(1);
				rc.left -= speed;
				rc.right -= speed;
				situation = go;
				isleft = true;
			}
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && rc.right < WINSIZEX)
			{
				character->setFrameY(0);
				rc.left += speed;
				rc.right += speed;
				situation = go;
				isleft = false;
			}

			if (KEYMANAGER->isStayKeyDown(VK_UP) && rc.top > 120)
			{
				rc.top -= speed;
				rc.bottom -= speed;
				situation = go;
			}

			if (KEYMANAGER->isStayKeyDown(VK_DOWN) && rc.bottom < WINSIZEY)
			{
				rc.top += speed;
				rc.bottom += speed;
				situation = go;
			}

			if (KEYMANAGER->isonceKeyUp(VK_LEFT) || KEYMANAGER->isonceKeyUp(VK_RIGHT) ||
				KEYMANAGER->isonceKeyUp(VK_UP) || KEYMANAGER->isonceKeyUp(VK_DOWN))
			{
				iskeydown = false;
				situation = idle;
				index = 0;
			}
		}//이동은 bool lock의 제한을 받음

		if (KEYMANAGER->isonceKeyDown(VK_SPACE))
		{
			if (charnum == 2)
			{
				if (delay >= 20)
				{
					delay = 20;
					swich = true;
				}
				if (swich)
				{

					_naruto->init(rc.left, rc.top + 15, isleft);
					situation = attack;
					lock = true;
					fire = true;
					index = 0;
					count = 0;
					delay = 0;
					swich = false;
				}
			}
		}

		if (KEYMANAGER->isStayKeyDown(VK_SPACE))
		{
			if (charnum == 0)
			{
				gauge += 0.5f;
				if (gauge > 150) { gauge = 150; }
				if (delay >= 50)
				{
					delay = 50;
					swich = true;
				}
			}

			else if (charnum == 1)
			{
				lock = true;
				rndarm = RND->getFromIntTo(0, 10);
				situation = attack;
				if (delay >= 7)
				{
					fire = true;
					_luffy->init(rc.right, rc.top + 15 + rndarm * 2, isleft,500);
					delay = 0;
				}
			}
		}

		if (KEYMANAGER->isonceKeyUp(VK_SPACE))
		{
			if (charnum == 0)
			{
				if (swich)
				{
					_ichigo->init(rc.left, rc.top + 15, speed + 2 + gauge / 5, gauge, isleft);
					swich = false;
					delay = 0;
					situation = attack;
					lock = true;
				}
				fire = true;
				gauge = 0;
				iskeydown = false;
			}
			else if (charnum == 1)
			{
				index = 6;
			}
		}

		delay++;
		count++;

		if (count % 7 == 0)
		{
			if (isleft)
			{
				if (charnum == 1)
				{
					character->setFrameX(index);
				}
				else
				{
					character->setFrameX(character->getMaxFrameX() - index);
				}
			}
			else
			{
				if (charnum == 1)
				{
					character->setFrameX(character->getMaxFrameX() - index);
				}
				else
				{
					character->setFrameX(index);
				}
			}

			if (situation == attack&&charnum == 1 && index == 5)
			{
				index = 2;
			}

			if (index >= character->getMaxFrameX())
			{
				if (situation == attack)
				{
					lock = false;
					index = 0;
					count = 0;
					situation = idle;
				}
				else
				{
					index = 0;
				}
			}
			else { index++; }
		}

		collision();
	}
}

void player::render(bool check)
{

	if (fire)
	{
		if (charnum == 0)
		{
			_ichigo->update();
			_ichigo->render(check);
		}
		else if (charnum == 1)
		{
			_luffy->update();
			_luffy->render(check);
		}
		else if (charnum == 2)
		{
			_naruto->update();
			_naruto->render(check);
		}
	}

	character->frameRender(getMemDc(), rc.left - 15, rc.top - 10, character->getFrameX(), character->getFrameY());


	for (int i = 0; i < maxheart; i++)
	{
		heart->render(getMemDc(), 120 + i * 60, 10);
	}
	if (check)
	{
		RECT a = _boss->getbossrect();
		Rectangle(getMemDc(), a.left, a.top, a.right, a.bottom);
		Rectangle(getMemDc(), rc.left, rc.top, rc.right, rc.bottom);
	}
}

int player::playerlocationx(int right)
{
	if (right < rc.right)
	{
		return 0;
	}
	else if (right > rc.left)
	{
		return 1;
	}
}

int player::playerlocationy(int top)
{
	if (top > rc.top)
	{
		return 0;
	}
	else if (top < rc.bottom)
	{
		return 1;
	}
}

void player::hit()
{
	maxheart--;
	if (maxheart == 0)
	{
		isover = true;
	}
}


void player::collision()
{
	switch (charnum)
	{
	case 0:
		for (int i = 0; i < _ichigo->getVBullet().size(); i++)
		{
			RECT oncerc;
			if (IntersectRect(&oncerc, &_ichigo->getVBullet()[i].rc, &_boss->getbossrect()))
			{
				_boss->hit(2 + (_ichigo->getVBullet()[i].gauge) / 5);
				_ichigo->removebullet(i);
			}
		}
		break;
	case 1:
		for (int i = 0; i < _luffy->getVBullet().size(); i++)
		{
			RECT oncerc;
			if (IntersectRect(&oncerc, &_luffy->getVBullet()[i].rc, &_boss->getbossrect()))
			{
				_boss->hit(7);
				_luffy->removebullet(i);
			}
			else if (_luffy->getVBullet()[i]._range <= 0)
			{
				_luffy->removebullet(i);
			}
		}
		break;
	case 2:
		for (int i = 0; i < _naruto->getVBullet().size(); i++)
		{
			RECT oncerc;
			if (IntersectRect(&oncerc, &_naruto->getVBullet()[i].rc, &_boss->getbossrect()))
			{
				_boss->hit(5);
				_naruto->removebullet(i);
			}
		}
		break;
	}
}
