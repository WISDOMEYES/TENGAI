#pragma once
#include "gameNode.h"
#include "bullet.h"

class player;

class boss : public gameNode
{
private:

	player* _player;

	image* _background;			//���� ���ȭ�� ����
	bool bgcheck;				//��� �� ���� �����ϰ� �ϴ� ����ġ

	image* bossheart;			//���� ü�¹�
	int bossheartmax;			//���� �ִ�ü��
	int ratioheart;				//���� ü�º��� �Ǳ��̴°�
	float ratio;				//���� ü�¿� ���� ����

	int _num;					//ȣ���� ���� ��ȣ
	bool initcheck;				//���� �ʱ�ȭ �ѹ���
	RECT bossrc;				//���� ��Ʈ

	image* enemy;				//���� ��������Ʈ �̹���
	int index, count;			//��������Ʈ �����϶�
	int x, y;					//���� ��ǥ
	int rand;					//���� ����
	int movedelay;				//���� �󸶳� ��������
	int maxaction;				//������ ������ ����
	bool endaction;				//���� �ൿ ������

	int maxstack;				//���� �ִ�ġ
	int stack;					//��������̴� �ʴ� �����̶� ���� �ٲ���ߵ�

	int delay;					//���� ������ ��������
	bool hitok;					//���� ���� ����ġ

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

	//�޸� ��ȣ ����
	void setplayerMemoryAdressLink(player* hero) { _player = hero; }
};

