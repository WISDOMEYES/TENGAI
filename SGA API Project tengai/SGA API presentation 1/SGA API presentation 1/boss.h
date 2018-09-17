#pragma once
#include "gameNode.h"
#include "bullet.h"

class player;

class boss : public gameNode
{
private:

	player* _player;

	image* _background;			//보스 배경화면 설정
	bool bgcheck;				//배경 한 번만 설정하게 하는 스위치

	image* bossheart;			//보스 체력바
	int bossheartmax;			//보스 최대체력
	int ratioheart;				//보스 체력비율 피까이는거
	float ratio;				//보스 체력에 따른 비율

	int _num;					//호출할 보스 번호
	bool initcheck;				//보스 초기화 한번만
	RECT bossrc;				//보스 렉트

	image* enemy;				//보스 스프라이트 이미지
	int index, count;			//스프라이트 움직일때
	int x, y;					//보스 좌표
	int rand;					//보스 패턴
	int movedelay;				//패턴 얼마나 실행할지
	int maxaction;				//보스간 패턴의 개수
	bool endaction;				//보스 행동 끝날때

	int maxstack;				//스택 최대치
	int stack;					//무브딜레이는 초당 설정이라 따로 바꿔줘야됨

	int delay;					//피해 입힐떄 무적간격
	bool hitok;					//피해 들어가는 스위치

	bool isclear;

public:
	boss();
	~boss();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(bool check);
	
	void makeBackground(int bgnum);

	void boss1action(int random);
	void boss2action(int random);
	void boss3action(int random);
	void boss4action(int random);
	void boss5action(int random);

	void hit(int damage);

	int gameclear() { return isclear; }

	void collision();

	inline RECT getbossrect(void) { return bossrc; }

	//메모리 상호 참조
	void setplayerMemoryAdressLink(player* hero) { _player = hero; }
};

