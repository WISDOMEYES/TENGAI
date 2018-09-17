#pragma once
#include"gameNode.h"
#include "player.h"
#include"boss.h"
#define PI 3.141592653f


class mainGame : public gameNode
{
private:
	
	player* _player;

	boss* _boss;

	image* background;		//배경 전환용
	image* UI;				//UI

	bool isButtonDown;		//시작시 버튼 눌렸냐
	int Pnumber;			//캐릭터 번호, 선택시 이 번호대로 이닛 생성
	int Bnumber;			//보스 번호, 선택시 이 번호대로 이닛 생성
	bool prolog;			//이거 켜져야 게임시작
	bool check;				//탭눌러서 충돌처리할때


public:

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	
	mainGame();
	~mainGame();
	
};

