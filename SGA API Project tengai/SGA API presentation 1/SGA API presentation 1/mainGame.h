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

	image* background;		//��� ��ȯ��
	image* UI;				//UI

	bool isButtonDown;		//���۽� ��ư ���ȳ�
	int Pnumber;			//ĳ���� ��ȣ, ���ý� �� ��ȣ��� �̴� ����
	int Bnumber;			//���� ��ȣ, ���ý� �� ��ȣ��� �̴� ����
	bool prolog;			//�̰� ������ ���ӽ���
	bool check;				//�Ǵ����� �浹ó���Ҷ�


public:

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	
	mainGame();
	~mainGame();
	
};

