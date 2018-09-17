#include "stdafx.h"
#include "imageManager.h"


imageManager::imageManager()
{
}


imageManager::~imageManager()
{
}
HRESULT imageManager::init(void)
{
	return S_OK;
}
void imageManager::release(void)
{
	
}

//빈 비트맵
image* imageManager::addImage(string strKey, int width, int height)
{
	image* img = findImage(strKey);

	//만약 이미지가 있으면 그냥 그이미지 사용
	if (img)return img;

	img = new image;


	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);

		return NULL;
	}


	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//파일 이미지
image* imageManager::addImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	if (img)return img;

	img = new image;
	if (FAILED(img->init(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	_mImageList.insert(make_pair(strKey, img));

	return img;

}
image* imageManager::addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);
	
	if (img)return img;

	img = new image;
	if (FAILED(img->init(fileName,x,y, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//프레임 이미지
image* imageManager::addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);
	
	if (img)return img;

	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	_mImageList.insert(make_pair(strKey, img));

	return img;
}
image* imageManager::addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);
	
	if (img)return img;

	img = new image;
	if (FAILED(img->init(fileName, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//키값으로 이미지 찾아오는 함수
image* imageManager::findImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	//키값을 찾았으면
	if (key != _mImageList.end())
	{
		return key->second;
	}
	return NULL;
}

//이미지 지워주는 함수
BOOL imageManager::deleteImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);
	
	if (key != _mImageList.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);

		return true;
	}
	return false;

}

//이미지 전체적으로 지워주는 함수
BOOL imageManager::deleteAll(void)
{
	mapImageIter iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	_mImageList.clear();
	return TRUE;
}
void  imageManager::render(string strKey, HDC hdc)
{
	image* img = findImage(strKey);
	if (img)img->render(hdc);
}
void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);
	if (img)img->render(hdc, destX, destY);
}
void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourheight)
{
	image* img = findImage(strKey);

	if (img)img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourheight);

}