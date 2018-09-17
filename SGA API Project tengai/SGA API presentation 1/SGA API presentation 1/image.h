#pragma once
class image
{
public:

	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,//���ҽ��ε�
		LOAD_FILE,	  //���Ϸε�	
		LOAD_EMPTY,	  //�� ��Ʈ�� ����
		LOAD_END
	};

	typedef struct tagImage
	{
		//DWORD�� ȣȯ�� �ƿ��Ұ�����. 4byte �� ���̻� �����ϵ� �ƴϴ�.
		//Long�� 32��Ʈ ������ ȣȯ�� ������4byte��.
		//int �� 64��Ʈ���� ȣȯ�� ������ 4byte��.
		//�翬�� ȣȯ�� �����ϸ� �Ҿ��ϱ� ������ ���� ȣȯ�� ���� �ʴ� DWORD�� �����.

		DWORD	resID;			//���ҽ� ID
		HDC		hMemDC;			//�޸� DC
		HBITMAP hBit;			//��Ʈ��(���ο� ��Ʈ�� �ڵ�)
		HBITMAP hOBit;			//�õ� ��Ʈ��(���� ��Ʈ�� �ڵ�)
		float	x;
		float	y;
		int		width;			//�̹��� ���� ũ��
		int		height;			//�̹��� ���� ũ��
		int		currentFrameX;	//������ �̹��� ��ȣ(����)
		int     currentFrameY;	//������ �̹��� ��ȣ(����)
		int		maxFrameX;		//�������� ����ȣ(����)
		int		maxFrameY;		//�������� ����ȣ(����)
		int		frameWidth;		//������ �̹��� ����� ����ũ��
		int		frameHeight;	//������ �̹��� ����� ����ũ��
		BYTE    loadType;		//�ε� Ÿ��

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
		//*LPIMAGE_INFO�� �̹����� �������� �Ҵ��� �� �ְ� ����. ���ٿ���
	}IMAGE_INFO, *LPIMAGE_INFO;
private:
	LPIMAGE_INFO _imageInfo;			//�̹�������
	CHAR*        _fileName;			//�̹����̸�
	BOOL		 _trans;				//������ ���ٲ���?
	COLORREF     _transColor;			//���� ���� RGB



public:

	image();
	~image();

	//�� ��Ʈ�� �ʱ�ȭ
	HRESULT init(int width, int height);
	
	//�̹��� ���� �ʱ�ȭ
	HRESULT init(const char* fileName, int width, int height, 
				BOOL trans = FALSE, COLORREF transColor = FALSE);
	HRESULT init(const char* fileName,float x, float y, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	HRESULT init(const char* fileName, float x, float y, int width, int height,
		int frameX, int frameY, BOOL trans, COLORREF transColor);

	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY,
		BOOL trans, COLORREF transColor);
	//����Ű ����
	void setTransColor(BOOL trans, COLORREF transColor);

	// ����
	void release();

						//�ѷ��� X	�ѷ��� Y		�ѷ��� X	    �ѷ���Y    sourX, Y�κ����� ũ��(����,����)
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);


	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	//====================================================
	//�̹��� ������ ���ϰ� �ϱ����� ����, ������
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

