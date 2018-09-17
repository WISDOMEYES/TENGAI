#pragma once
class image
{
public:

	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,//리소스로딩
		LOAD_FILE,	  //파일로딩	
		LOAD_EMPTY,	  //빈 비트맵 파일
		LOAD_END
	};

	typedef struct tagImage
	{
		//DWORD는 호환이 아예불가능함. 4byte 딱 그이상 그이하도 아니당.
		//Long은 32비트 까지는 호환이 가능한4byte임.
		//int 는 64비트까지 호환이 가능한 4byte임.
		//당연히 호환히 가능하면 불안하기 때문에 컴은 호환을 하지 않는 DWORD를 사랑함.

		DWORD	resID;			//리소스 ID
		HDC		hMemDC;			//메모리 DC
		HBITMAP hBit;			//비트맵(새로운 비트맵 핸들)
		HBITMAP hOBit;			//올드 비트맵(기존 비트맵 핸들)
		float	x;
		float	y;
		int		width;			//이미지 가로 크기
		int		height;			//이미지 세로 크기
		int		currentFrameX;	//프레임 이미지 번호(가로)
		int     currentFrameY;	//프레임 이미지 번호(세로)
		int		maxFrameX;		//프레임의 끝번호(가로)
		int		maxFrameY;		//프레임의 끝번호(세로)
		int		frameWidth;		//프레임 이미지 한장당 가로크기
		int		frameHeight;	//프레임 이미지 한장당 세로크기
		BYTE    loadType;		//로드 타입

		tagImage()
		{
			resID			=0;
			hMemDC			=NULL;
			hBit			=NULL;
			hOBit			=NULL;
			x				=0;
			y				=0;
			width			=0;
			height			=0;
			currentFrameX	=0;
			currentFrameY	= 0;
			maxFrameX		= 0;
			maxFrameY		= 0;
			frameWidth		= 0;		
			frameHeight		= 0;
			loadType =	LOAD_RESOURCE;
		}
		//*LPIMAGE_INFO는 이미지를 여러곳에 할당할 수 있게 위함. 접근용의
	}IMAGE_INFO, *LPIMAGE_INFO;
private:
	LPIMAGE_INFO _imageInfo;			//이미지정보
	CHAR*        _fileName;			//이미지이름
	BOOL		 _trans;				//배경색을 없앨꺼냐?
	COLORREF     _transColor;			//배경색 없앨 RGB



public:

	image();
	~image();

	//빈 비트맵 초기화
	HRESULT init(int width, int height);
	
	//이미지 파일 초기화
	HRESULT init(const char* fileName, int width, int height, 
				BOOL trans = FALSE, COLORREF transColor = FALSE);
	HRESULT init(const char* fileName,float x, float y, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	HRESULT init(const char* fileName, float x, float y, int width, int height,
		int frameX, int frameY, BOOL trans, COLORREF transColor);

	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY,
		BOOL trans, COLORREF transColor);
	//투명키 셋팅
	void setTransColor(BOOL trans, COLORREF transColor);

	// 삭제
	void release();

						//뿌려줄 X	뿌려줄 Y		뿌려올 X	    뿌려올Y    sourX, Y로부터의 크기(가로,세로)
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);


	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	//====================================================
	//이미지 조작을 편하게 하기위한 접근, 설정자
	//====================================================
	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX(void) { return _imageInfo->x; }

	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY(void) { return _imageInfo->y; }

	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}
	inline float getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ? _imageInfo->x + (_imageInfo->width / 2) :
			_imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	inline float getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ? _imageInfo->y + (_imageInfo->height / 2) :
			_imageInfo->y + (_imageInfo->frameHeight / 2);
	}
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	inline int getWidth(void) { return _imageInfo->width;}
	inline int getHeight(void) { return _imageInfo->height; }

	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }

	inline int getFrameWidth(void) { return _imageInfo->frameWidth;}
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }
};

