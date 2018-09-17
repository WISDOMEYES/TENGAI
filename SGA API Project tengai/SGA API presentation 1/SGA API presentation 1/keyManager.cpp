#include "stdafx.h"
#include "keyManager.h"


keyManager::keyManager()
{
}


keyManager::~keyManager()
{
}
HRESULT keyManager::init(void)
{//눌러지는 키 종류 만큼
	for (int i = 0; i < KEYMAX; i++)
	{
		this->getKeyUp().set(i, false);
		this->getKeyDown().set(i, false);
	}

	return S_OK;
}
void keyManager::release(void)
{

}


bool keyManager::isonceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->getKeyDown()[key])
		{
			this->setKeyDown(key, true);
			return true;
		}
	}
	else this->setKeyDown(key, false);


	return false;
}
bool keyManager::isonceKeyUp(int key) 
{
	if (GetAsyncKeyState(key) & 0x8000) this->setKeyUp(key, true);
	else
	{
		if (this->getKeyUp()[key])
		{
			this->setKeyUp(key, false);
			return true;
		}
	}

	return false;
}
bool keyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}
bool keyManager::isToggleKey(int key) 
{
	if (GetAsyncKeyState(key) & 0x0001) return true;
	return false;
}