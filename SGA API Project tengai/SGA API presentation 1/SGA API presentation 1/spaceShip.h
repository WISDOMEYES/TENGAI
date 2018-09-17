#pragma once
#include "gameNode.h"
#include "bullets.h"

class spaceShip : public gameNode
{
private:
	image* _ship;

	missile* _missile;
	thaadMissile* _thaad;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	spaceShip();
	~spaceShip();
};

