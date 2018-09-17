#pragma once
#include"singletonBase.h"
#include<bitset>

using namespace std;

#define KEYMAX 256
class keyManager : public singletonBase<keyManager>
{
private : 
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;

public:
	HRESULT init(void);
	void release(void);

	//한번만 눌렀냐
	bool isonceKeyDown(int key);
	//눌렀다가 뗏냐
	bool isonceKeyUp(int key);
	//누르고 있냐
	bool isStayKeyDown(int key);
	//캡스락 넘버락 가튼거
	bool isToggleKey(int key);


	bitset<KEYMAX> getKeyUp() { return _keyUp; }
	bitset<KEYMAX> getKeyDown() { return _keyDown; }

	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }

	keyManager();
	~keyManager();
};

