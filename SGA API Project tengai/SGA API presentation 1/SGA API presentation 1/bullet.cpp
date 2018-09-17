#include "stdafx.h"
#include "bullet.h"


bullet::bullet()
{
}


bullet::~bullet()
{
}

HRESULT bullet::init(void)
{
	
	return S_OK;
}

void bullet::release(void)
{
}

void bullet::update(void)
{
}

void bullet::render(HDC _hdc)
{
}


//캐릭터 총알 : 이치고(블리치)
ichigobullet::ichigobullet()
{
}

ichigobullet::~ichigobullet()
{
}

   
HRESULT ichigobullet::init(float x, float y,int speed, int gauge, bool isleft)
{
		bulletbase ichigo;
		ichigo.rc = RectMakeCenter(x + 25, y, 50, 50+gauge);
		ichigo.speed = speed;
		ichigo.missile = new image;
		ichigo.missile->init("PlayerImage/ichigo/ichigo_sword.bmp", x+25, y, 100 , 100+gauge, 3, 2, true, RGB(84, 109, 142));
		ichigo.missile->setFrameX(0);
		ichigo.x = x + 25;
		ichigo.y = y;
		ichigo.count = 0;
		ichigo.index = 0;
		ichigo.isleft = isleft;
		ichigo.gauge = gauge;

		_Vichigobase.push_back(ichigo);
	
	return S_OK;
}

void ichigobullet::release(void)
{
}

void ichigobullet::update(void)
{
	for (_VIichigobase = _Vichigobase.begin(); _VIichigobase != _Vichigobase.end(); ++_VIichigobase)
	{
		_VIichigobase->count++;

		if (_VIichigobase->isleft)
		{
			_VIichigobase->missile->setFrameY(1);
			_VIichigobase->rc.left -= _VIichigobase->speed;
			_VIichigobase->rc.right -= _VIichigobase->speed;

		}
		else 
		{
			_VIichigobase->missile->setFrameY(0);
			_VIichigobase->rc.left += _VIichigobase->speed;
			_VIichigobase->rc.right += _VIichigobase->speed;
		}

		if (_VIichigobase->count % 20 == 0)
		{
			if (_VIichigobase->isleft)
			{
				_VIichigobase->missile->setFrameX(_VIichigobase->missile->getMaxFrameX()- _VIichigobase->index);
			}
			else
			{
			_VIichigobase->missile->setFrameX(_VIichigobase->index);
			}
			if (_VIichigobase->index >= 2)
			{
				_VIichigobase->index = 0;
			}
			else
			{
				_VIichigobase->index++;
			}
		}
	}
}

void ichigobullet::render(bool checkbox )
{
	for (_VIichigobase = _Vichigobase.begin(); _VIichigobase != _Vichigobase.end(); ++_VIichigobase)
	{
		_VIichigobase->missile->frameRender(getMemDc(),
			_VIichigobase->rc.left,
			_VIichigobase->rc.top,
			_VIichigobase->missile->getFrameX(), _VIichigobase->missile->getFrameY());
		if (checkbox)
		{
			Rectangle(getMemDc(), _VIichigobase->rc.left, _VIichigobase->rc.top,_VIichigobase->rc.right, _VIichigobase->rc.bottom);
		}
	}
}

void ichigobullet::removebullet(int arrnum)
{
	_Vichigobase[arrnum].missile->release();
	_Vichigobase.erase(_Vichigobase.begin() + arrnum);
}


//캐릭터 총알 : 나루토(나루토)
narutobullet::narutobullet()
{
}

narutobullet::~narutobullet()
{
}

HRESULT narutobullet::init(float x, float y, bool isleft)
{
	bulletbase naruto;
	naruto.rc = RectMakeCenter(x + 30, y, 40, 20);
	naruto.speed = 15;
	naruto.missile = new image;
	naruto.missile->init("PlayerImage/naruto/naruto_shuriken.bmp", x + 25, y, 140,28, 5, 1, true, RGB(0, 0, 0));
	naruto.missile->setFrameX(0);
	naruto.x = x + 25;
	naruto.y = y;
	naruto.count = 0;
	naruto.index = 0;
	naruto.isleft = isleft;

	_Vnarutobase.push_back(naruto);
	return S_OK;
}

void narutobullet::release(void)
{
}

void narutobullet::update(void)
{
	for (_VInarutobase = _Vnarutobase.begin(); _VInarutobase != _Vnarutobase.end(); ++_VInarutobase)
	{
		_VInarutobase->count++;

		if (_VInarutobase->isleft)
		{
			_VInarutobase->rc.left -= _VInarutobase->speed;
			_VInarutobase->rc.right -= _VInarutobase->speed;
		}
		else
		{
			_VInarutobase->rc.left += _VInarutobase->speed;
			_VInarutobase->rc.right += _VInarutobase->speed;
		}

		if (_VInarutobase->count % 15 == 0)
		{
			if (_VInarutobase->isleft)
			{
				_VInarutobase->missile->setFrameX(_VInarutobase->missile->getMaxFrameX() - _VInarutobase->index);
			}
			else
			{
				_VInarutobase->missile->setFrameX(_VInarutobase->index);
			}
			if (_VInarutobase->index >= _VInarutobase->missile->getMaxFrameX())
			{
				_VInarutobase->index = 0;
			}
			else
			{
				_VInarutobase->index++;
			}
		}
	}
}

void narutobullet::render(bool checkbox)
{
	for (_VInarutobase = _Vnarutobase.begin(); _VInarutobase != _Vnarutobase.end(); ++_VInarutobase)
	{
		_VInarutobase->missile->frameRender(getMemDc(),
			_VInarutobase->rc.left,
			_VInarutobase->rc.top,
			_VInarutobase->missile->getFrameX(), 0);
		if (checkbox)
		{
			Rectangle(getMemDc(), _VInarutobase->rc.left, _VInarutobase->rc.top, _VInarutobase->rc.right, _VInarutobase->rc.bottom);
		}
	}
}

void narutobullet::removebullet(int arrnum)
{
	_Vnarutobase[arrnum].missile->release();
	_Vnarutobase.erase(_Vnarutobase.begin() + arrnum);
}


//캐릭터 총알 : 루피(원피스)
luffybullet::luffybullet()
{
}

luffybullet::~luffybullet()
{
}

HRESULT luffybullet::init(float x, float y,  bool isleft,int range)
{
	bulletbase luffy;
	luffy.rc = RectMakeCenter(x , y, 86, 10);
	luffy.speed = 12;
	luffy.missile = new image;
	luffy.missile->init("PlayerImage/luffy/luffy_arm.bmp", x + 25, y, 67, 30, 1, 2, true, RGB(225, 0, 225));
	luffy.missile->setFrameX(0);
	luffy.x = x + 25;
	luffy.y = y;
	luffy.index = 0;
	luffy.isleft = isleft;
	luffy._range = range;

	_Vluffybase.push_back(luffy);
	return S_OK;
}

void luffybullet::release(void)
{
}

void luffybullet::update(void)
{
	for (_VIluffybase = _Vluffybase.begin(); _VIluffybase != _Vluffybase.end(); ++_VIluffybase)
	{
		if (_VIluffybase->isleft)
		{
			_VIluffybase->missile->setFrameY(1);
			_VIluffybase->rc.left -= _VIluffybase->speed;
			_VIluffybase->rc.right -= _VIluffybase->speed;
		}
		else
		{
			_VIluffybase->missile->setFrameY(0);
			_VIluffybase->rc.left += _VIluffybase->speed;
			_VIluffybase->rc.right += _VIluffybase->speed;
		}
		_VIluffybase->_range-= _VIluffybase->speed;
	}
}

void luffybullet::render(bool checkbox)
{
	for (_VIluffybase = _Vluffybase.begin(); _VIluffybase != _Vluffybase.end(); ++_VIluffybase)
	{
		_VIluffybase->missile->frameRender(getMemDc(),
			_VIluffybase->rc.left,
			_VIluffybase->rc.top,
			_VIluffybase->missile->getFrameX(), _VIluffybase->missile->getFrameY());
		if (checkbox)
		{
			Rectangle(getMemDc(), _VIluffybase->rc.left, _VIluffybase->rc.top, _VIluffybase->rc.right, _VIluffybase->rc.bottom);
		}
	}
}

void luffybullet::removebullet(int arrnum)
{
	_Vluffybase[arrnum].missile->release();
	_Vluffybase.erase(_Vluffybase.begin() + arrnum);
}
