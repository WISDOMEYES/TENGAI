#include "stdafx.h"
#include "image.h"



//참고사항
/*
	1.BMP
	제약이 많지만 무손실 무압축 이므로 속도가 가장 빠름
	2.JPG
	손실 압축이므로 원래 가진 이미지의 손실이 일어나는 대신 어떠한 알고리즘에 의해 압축이 
	되어 용량이 작다.
	3.PNG
	위녀석들과 달리 alpha 채널값이 없다.(투명)

*/
image::image()
	:_imageInfo(NULL),
	_fileName(NULL),
	_trans(false),
	_transColor(RGB(0,0,0))
{
	
    
}


image::~image()
{
}
//빈 비트맵 초기화
HRESULT image::init(int width, int height)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈를 먼저 해줄것
	if (_imageInfo != NULL)release();

	//DC가져오기 (현재 윈도우에 대한 화면 DC를 임시로 받아온다)

	HDC hdc = GetDC(_hWnd);

	/*
	CreateCompatibleDC
	->비트맵을 출력하기 위해 메모리 DC를 만들어 주는 함수
	->화면 DC와 메모리 DC호환
	CreateCompatibleBitmap
	->원본 DC와 호환되는 비트맵을 생성해 주는 함수
	SelectObject
	->기본의 비트맵 핸들을 반환하고, 새로운 비트맵을 메모리 DC가 선택하고
	메모리 DC에 비트맵이 그려짐, 화면 DC가 아니므로 모니터에 출력 X
	*/

	//이미지 정보 생성하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;



	//파일 이름
	_fileName = NULL;
	//투명키 컬러 셋팅
	_trans = FALSE;
	_transColor = RGB(0, 0, 0);
	//리소스를 얻어오는데 실패 했을때
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}
	//DC해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;

}
//이미지 파일 초기화
HRESULT image::init(const char* fileName, int width, int height,
	BOOL trans /*= FALSE*/, COLORREF transColor /*= FALSE*/)
{
	if (fileName == NULL)return E_FAIL;
	if (_imageInfo != NULL)release();
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;

	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;


	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);
	_trans = trans;
	_transColor = transColor;


	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}
HRESULT image::init(const char* fileName, float x, float y, int width, int height,
	BOOL trans, COLORREF transColor)
{
	//파일 이름이 없으면 실패
	if (fileName == NULL)return E_FAIL;
	//이미지 정보가 뭔가 이따면 해제해라
	if (_imageInfo != NULL)release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;

	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;


	//파일 길이를 알아온다(파일 경로)
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);
	_trans = trans;
	_transColor = transColor;



	//초기화가 안되어 있으면
	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}
	ReleaseDC(_hWnd, hdc);
	return S_OK;

}
HRESULT image::init(const char* fileName, float x, float y, int width, int height,
	int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	if (fileName == NULL)return E_FAIL;
	//이미지 정보가 뭔가 이따면 해제해라
	if (_imageInfo != NULL)release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;


	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x-(width/2);
	_imageInfo->y = y-(height/2);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	//파일 길이를 알아온다(파일 경로)
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);
	_trans = trans;
	_transColor = transColor;



	//초기화가 안되어 있으면
	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT image::init(const char* fileName, int width, int height, int frameX, int frameY,
	BOOL trans, COLORREF transColor)
{
	if (fileName == NULL)return E_FAIL;
	//이미지 정보가 뭔가 이따면 해제해라
	if (_imageInfo != NULL)release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;


	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	//파일 길이를 알아온다(파일 경로)
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);
	_trans = trans;
	_transColor = transColor;



	//초기화가 안되어 있으면
	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

//투명키 셋팅
void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

// 삭제
void image::release()
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);


		_trans = false;
		_transColor = RGB(0, 0, 0);
	}
}


void image::render(HDC hdc)
{
	if (_trans)
	{
	GdiTransparentBlt(hdc,
		_imageInfo->x,
		_imageInfo->y,
		_imageInfo->width,
		_imageInfo->height,
		_imageInfo->hMemDC,
		0, 0,
		_imageInfo->width,
		_imageInfo->height,
		_transColor);

	}
	else
	{
		BitBlt(hdc, _imageInfo->x, _imageInfo->y,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}
//렌더(내가 지정한 위치에 이미지를 출력)
void image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,					//복사될 영역의 DC		==backDC
			destX,								//복사될 좌표X(left)		==backDC의 영역의 좌표
			destY,								//복사될 좌표X(top)		==backDC의 영역의 좌표
			_imageInfo->width,					//복사될 크기의 width		==backDC의 영역의 좌표로 부터 가로크기
			_imageInfo->height,					//복사될 크기의 height   ==backDC의 영역의 좌표로 부터 세로크기
			_imageInfo->hMemDC,					//복사할 DC				==이미지DC
			0,0,								//복사할 x,y				==이미지 DC의 좌표
			_imageInfo->width,					//복사할 width			==이미지DC의 가로크기
			_imageInfo->height,					//복사할 height			==이미지DC의 세로크기
			_transColor);						//복사에서 제외할 색상	==이미지DC에서의 픽셀값
	}
	else
	{
		//백버퍼에 있는 것을 앞으로  고속복사 해준다~
		BitBlt(hdc, destX, destY,
			_imageInfo->width, _imageInfo->height, _imageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}
void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,					//복사될 영역의 DC		==backDC
			destX,								//복사될 좌표X(left)		==backDC의 영역의 좌표
			destY,								//복사될 좌표X(top)		==backDC의 영역의 좌표
			sourWidth,							//복사될 크기의 width		==backDC의 영역의 좌표로 부터 가로크기
			sourHeight,							//복사될 크기의 height   ==backDC의 영역의 좌표로 부터 세로크기
			_imageInfo->hMemDC,					//복사할 DC				==이미지DC
			sourX, sourY,						//복사할 x,y				==이미지 DC의 좌표
			sourWidth,							//복사할 width			==이미지DC의 가로크기
			sourHeight,							//복사할 height			==이미지DC의 세로크기
			_transColor);						//복사에서 제외할 색상	==이미지DC에서의 픽셀값
	}
	else
	{//백버퍼에 있는 것을 앞으로 고속복사 해준다.
		BitBlt(hdc, destX, destY,
			sourWidth, sourHeight, _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}
void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,									//복사될 장소의 DC
			destX,												//복사될 좌표 시작점X
			destY,												//복사될 좌표 시작점Y
			_imageInfo->frameWidth,								//복사될 이미지 가로크기
			_imageInfo->frameHeight,							//복사될 이미지 세로크기
			_imageInfo->hMemDC,									//복사대상 DC
			_imageInfo->currentFrameX*_imageInfo->frameWidth,
			_imageInfo->currentFrameY* _imageInfo->frameHeight,
			_imageInfo->frameWidth,								//복사될 가로크기
			_imageInfo->frameHeight,							//복사될 세로크기
			_transColor);										//날려줄 컬러
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX* _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}
void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(hdc,									//복사될 장소의 DC
			destX,												//복사될 좌표 시작점X
			destY,												//복사될 좌표 시작점Y
			_imageInfo->frameWidth,								//복사될 이미지 가로크기
			_imageInfo->frameHeight,							//복사될 이미지 세로크기
			_imageInfo->hMemDC,									//복사대상 DC
			_imageInfo->currentFrameX*_imageInfo->frameWidth,
			_imageInfo->currentFrameY* _imageInfo->frameHeight,
			_imageInfo->frameWidth,								//복사될 가로크기
			_imageInfo->frameHeight,							//복사될 세로크기
			_transColor);										//날려줄 컬러
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX* _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}
//이미지 1장으로 하는 루푸렌더
void image::loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	//오프셋 영역 받아올 변수
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려주는 영역
	RECT rcDest;

	//화면에 그려주는 영역 지정
	int drawAreaX = drawArea->left;						//Left
	int drawAreaY = drawArea->top;						//Top
	int drawAreaW = drawArea->right - drawArea->left;	//Width
	int drawAreaH = drawArea->bottom - drawArea->top;	//Height

														//Y Axis
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		sourHeight = rcSour.bottom - rcSour.top;

		//그려지는 영역의 높이값보다 ?? 크면
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//뿌려주는 영역 
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//X Axis
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left,				//뿌릴 X
				rcDest.top,					//뿌릴 Y
				rcSour.left, rcSour.top,	//뿌려올 X, Y
				rcSour.right - rcSour.left,	//뿌려올 이미지 가로크기
				rcSour.bottom - rcSour.top);//뿌려올 이미지 세로크기
		}
	}
}