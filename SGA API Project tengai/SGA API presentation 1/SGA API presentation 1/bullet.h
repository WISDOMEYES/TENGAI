#pragma once
#include "gameNode.h"
#include<vector>

struct bulletbase
{
	image* missile;
	RECT rc;
	float x, y;
	int speed;
	int count;
	int index;
	bool isleft;
	int _range;
	int gauge;
};

class bullet : public gameNode
{
private:
	bulletbase _base;
public:
	bullet();
	~bullet();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC _hdc);
};



class ichigobullet : public gameNode
{
private:
	vector<bulletbase> _Vichigobase;
	vector<bulletbase>::iterator _VIichigobase;
	
public:
	ichigobullet();
	~ichigobullet();

	virtual HRESULT init(float x, float y, int speed,int gauge, bool isleft);
	virtual void release(void);
	virtual void update(void);
	virtual void render(bool checkbox);

	void removebullet(int arrnum);

	vector<bulletbase>getVBullet(void) { return _Vichigobase; }
	vector<bulletbase>::iterator getVIBullet(void) { return _VIichigobase; }
};

class narutobullet : public gameNode
{
private:
	vector<bulletbase> _Vnarutobase;
	vector<bulletbase>::iterator _VInarutobase;

public:
	narutobullet();
	~narutobullet();

	virtual HRESULT init(float x, float y, bool isleft);
	virtual void release(void);
	virtual void update(void);
	virtual void render(bool checkbox);

	void removebullet(int arrnum);

	vector<bulletbase>getVBullet(void) { return _Vnarutobase; }
	vector<bulletbase>::iterator getVIBullet(void) { return _VInarutobase; }
};

class luffybullet : public gameNode
{
private:
	vector<bulletbase> _Vluffybase;
	vector<bulletbase>::iterator _VIluffybase;


public:
	luffybullet();
	~luffybullet();

	virtual HRESULT init(float x, float y, bool isleft,int range);
	virtual void release(void);
	virtual void update(void);
	virtual void render(bool checkbox);

	void removebullet(int arrnum);

	vector<bulletbase>getVBullet(void) { return _Vluffybase; }
	vector<bulletbase>::iterator getVIBullet(void) { return _VIluffybase; }
};
