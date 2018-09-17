#pragma once
#include "gameNode.h"
#include "bullet.h"


class boss;

enum situation
{
	idle = 0,
	go,
	attack,
	hit
};

class player : public gameNode
{
private:

	image* character;		//캐릭터 이미지
	int situation;			//캐릭터 행동에 따른 이미지
	int count, index;		//이미지 넘길때 세는거랑 이미지 장수
	bool iskeydown;			//키 눌렸냐 안눌렸냐
	bool isleft;			//방향설정
	bool lock;				//공격.스킬 쓸떄 잠시 움직임 정지

	RECT rc;				//캐릭터 충돌렉트
	
	bool fire;				//처음 쏘기 전까지 총알 업데이트 렌더 안돌리게

	float gauge;			//기모아서 쏜다(이치고 전용?)
	int rndarm;				//팔 위치 랜덤으로바꾸기

	int delay;				//공격후 딜레이
	bool swich;				//딜레이 차면 쏘도록

	float x, y;				//캐릭터 좌표
	int speed;				//캐릭터 이동속도
	int charnum;			//캐릭터 번호

	image* heart;			//하트 스프라이트
	int maxheart;			//캐릭터 최대하트

	bool isover;

	ichigobullet* _ichigo;
	narutobullet* _naruto;
	luffybullet* _luffy;

	boss* _boss;

public:
	player();
	~player();
	
	virtual HRESULT init(int num);
	virtual void release(void);
	virtual void update(void);
	virtual void render(bool check);

	int playerlocationx(int right);
	int playerlocationy(int top);

	void hit();

	bool gameover() { return isover; }
	
	void collision();

	inline RECT getplayerrect(void) { return rc; }

	//메모리 상호 참조
	void setbossMemoryAdressLink(boss* boss) { _boss = boss; }
};

