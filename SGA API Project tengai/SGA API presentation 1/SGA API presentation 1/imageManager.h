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

	//빈 비트맵
	image* addImage(string strKey, int width, int height);

	//파일 이미지
	image* addImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor);
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool trans, COLORREF transColor);

	//프레임 이미지
	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);

	//키값으로 이미지 찾아오는 함수
	image* findImage(string strKey);

	//이미지 지워주는 함수
	BOOL deleteImage(string strKey);

	//이미지 전체적으로 지워주는 함수
	BOOL deleteAll(void);
	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourheight);

	imageManager();
	~imageManager();
};

