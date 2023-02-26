#pragma once

class GImage
{
public:
	const float M_PI = 3.14159265358979323846f;
	const float M_SPEED = 10.0f;
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE=0,LOAD_FILE,	//���ҽ��� �ε�, ���Ϸ� �ε�
		LOAD_EMPTY, LOAD_END		//�� ��Ʈ�� �ε�
	};
	
	typedef struct tagImage
	{
		DWORD		resID;			//���ҽ� ID
		HDC			hMemDc;			//�޸� DC
		HBITMAP		hBit;			//��Ʈ��
		HBITMAP		hOBit;			//�õ� ��Ʈ��
		float		x;				//�̹��� x��ǥ(����Ʈ)
		float		y;				//�̹��� y��ǥ(ž)
		int			width;			//�̹��� ����ũ��
		int			height;			//�̹��� ����ũ��
		int			currentFrameX;	//���� ������ X ��ǥ
		int			currentFrameY;	//���� ������ Y ��ǥ
		int			maxFrameX;		//�ִ� ������ X ��ǥ
		int			maxFrameY;		//�ִ� ������ Y ��ǥ
		int			frameWidth;		//1 ������ ����
		int			frameHeight;	//1 ������ ����
		POINT		vertices[4];	// ������ 3��
		float		fAnchorX;
		float		fAnchorY;
		float		fAngle;
		BYTE		loadType;		//�̹��� �ε� Ÿ��

		tagImage()
		{
			resID = 0;
			hMemDc = nullptr;
			hBit = nullptr;
			hOBit = nullptr;
			x = y = 0;
			width = 0;
			height = 0;
			currentFrameX=0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			vertices[0].x = 0;
			vertices[0].y = 0;
			vertices[1].x = 0;
			vertices[1].y = 0;
			vertices[2].x = 0;
			vertices[2].y = 0;
			vertices[3].x = 0;
			vertices[3].y = 0;
			fAnchorX = 0;
			fAnchorY = 0;
			fAngle = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//�̹��� ����
	char*			 _fileName;		//�̹��� �̸�
	bool			_isTrans;		//����
	COLORREF		_transColor;	//���� ���� RGB (RGB(255,0,255))

	BLENDFUNCTION _blendFunc;		//���� ���� ���
	LPIMAGE_INFO _blendImage;		//���� ���� �̹���
	
public:
	//WinAPI �ڷ����� ȥ�յ� ����
	//�� �Լ� �����ε� ��Ģ ����
	HRESULT init(int width, int height);
	HRESULT init(const DWORD resID, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	//������ �̹��� ���Ϸ� �ʱ�ȭ
	HRESULT init(const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0)); //�����̹���
	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	//�̹��� ȸ��
	HRESULT init(const char* fileName, float x, float y, int width, int height, float _anchorX, float _anchorY, bool isTrans, COLORREF transColor);
	HRESULT init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, float _anchorX, float _anchorY, bool isTrans, COLORREF transColor);

	HRESULT initForAlphaBlend(void);

	void setTransColor(bool isTrans, COLORREF transColor);
	
	void release(void);
	
	void rotateUpdate(float _dt, int destX, int destY);
	void rotateFrameUpdate(float _dt, int destX, int destY);

	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);

	//Ŭ����
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void alphaRender(HDC hdc, BYTE alpha); //��� ���ĺ���
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha); //���ϴ� ��ġ�� ���ĺ���
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha); //��ų ����Ʈ��


	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	void rotateRender(HDC hdc, int destX, int destY);
	void rotateFrameRender(HDC hdc);

	void scaleRender(HDC hdc, int dstX, int dstY, int dstWidth, int dstHeight, int srcX, int srcY, int srcWidth, int srcHeight);

	//===============
	//# �ζ��� �Լ� #
	//===============
	inline HDC getMemDC(void) { return _imageInfo->hMemDc; }
	// �̹��� x��ǥ
	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }
	// �̹��� y��ǥ
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	// �̹��� ������ǥ
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = x - (_imageInfo->height / 2);
	}

	// �̹��� ����, ���� ũ��
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }
	
	// �ٿ�� �ڽ�(�浹�� ��Ʈ)
	inline RECT boundingBox(void)
	{
		RECT rc =
		{
			(int) _imageInfo->x,
			(int) _imageInfo->y,
			(int) _imageInfo->x + _imageInfo->width,
			(int) _imageInfo->y + _imageInfo->height,
		};

		return rc;
	}

	// ������ X
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	// ������ Y
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	// �̹��� 1 ������ ����, ����
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	// �ִ� ������ X,Y����
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

private:
	void Rotate(float _angle, int destX, int destY);
	void frameRotate(float _angle, int destX, int destY);

	void renderInfo(HDC hdc);
public:
	GImage();
	~GImage() {}

};

