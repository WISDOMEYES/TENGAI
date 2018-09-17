#pragma once
#include"singletonBase.h"
#include"image.h"
#include<map>
class imageManager : public singletonBase<imageManager>
{
private : 
	typedef map<string, image*>mapImageList;
	typedef map<string, image*>::iterator mapImageIter;

private : 
	mapImageList _mImageList;
public:
	HRESULT init(void);
	void release(void);

	//�� ��Ʈ��
	image* addImage(string strKey, int width, int height);

	//���� �̹���
	image* addImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor);
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool trans, COLORREF transColor);

	//������ �̹���
	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);

	//Ű������ �̹��� ã�ƿ��� �Լ�
	image* findImage(string strKey);

	//�̹��� �����ִ� �Լ�
	BOOL deleteImage(string strKey);

	//�̹��� ��ü������ �����ִ� �Լ�
	BOOL deleteAll(void);
	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourheight);

	imageManager();
	~imageManager();
};

