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

	image* character;		//ĳ���� �̹���
	int situation;			//ĳ���� �ൿ�� ���� �̹���
	int count, index;		//�̹��� �ѱ涧 ���°Ŷ� �̹��� ���
	bool iskeydown;			//Ű ���ȳ� �ȴ��ȳ�
	bool isleft;			//���⼳��
	bool lock;				//����.��ų ���� ��� ������ ����

	RECT rc;				//ĳ���� �浹��Ʈ
	
	bool fire;				//ó�� ��� ������ �Ѿ� ������Ʈ ���� �ȵ�����

	float gauge;			//���Ƽ� ���(��ġ�� ����?)
	int rndarm;				//�� ��ġ �������ιٲٱ�

	int delay;				//������ ������
	bool swich;				//������ ���� ���

	float x, y;				//ĳ���� ��ǥ
	int speed;				//ĳ���� �̵��ӵ�
	int charnum;			//ĳ���� ��ȣ

	image* heart;			//��Ʈ ��������Ʈ
	int maxheart;			//ĳ���� �ִ���Ʈ

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

	//�޸� ��ȣ ����
	void setbossMemoryAdressLink(boss* boss) { _boss = boss; }
};

