#include "Stdafx.h"
#include "GImage.h"

GImage::GImage() : _imageInfo(nullptr),
				   _fileName(nullptr),
				   _isTrans(false),
				   _transColor(RGB(0,0,0)),
				   _blendImage(nullptr)
{
	//!Do Nothing
}

HRESULT GImage::init(int width, int height)
{
	//재초기화 방지용 / 이미지 정보에 값이 들어 있다면 해제부터 하겠다.
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDc = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc,width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = nullptr;
	_isTrans = false;
	_transColor = RGB(0, 0, 0);

	//리소스 얻어오는 데 실패
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT GImage::init(const DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = resID;
	_imageInfo->hMemDc = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance,MAKEINTRESOURCE(_imageInfo->resID));
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = nullptr;
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻어오는 데 실패
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT GImage::init(const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDc = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// 예외처리
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	//_s가 붙으면 추가형. 인자를 추가해 조금 더 안전하게 쓰겠다.
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻어오는 데 실패
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT GImage::init(const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDc = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	// 예외처리
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻어오는 데 실패
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT GImage::init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDc = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	// 예외처리
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻어오는 데 실패
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT GImage::init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDc = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	// 예외처리
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻어오는 데 실패
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT GImage::init(const char* fileName, float x, float y, int width, int height, float _anchorX, float _anchorY, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용 / 이미지 정보에 값이 들어 있다면 해제부터 하겠다.
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDc = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->fAnchorX = _anchorX;
	_imageInfo->fAnchorY = _anchorY;


	// Upper-Left
	_imageInfo->vertices[0].x = (LONG)(x - (_anchorX * width));
	_imageInfo->vertices[0].y = (LONG)(y - (_anchorY * height));

	// Upper-Right
	_imageInfo->vertices[1].x = (LONG)(x + (width - (_anchorX * width)));
	_imageInfo->vertices[1].y = (LONG)(y - (_anchorY * height));

	// Lower-Right
	_imageInfo->vertices[2].x = (LONG)(x + (width - (_anchorX * width)));
	_imageInfo->vertices[2].y = (LONG)(y + (height - (_anchorY * height)));
	
	// 예외처리
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻어오는 데 실패
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT GImage::init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, float _anchorX, float _anchorY, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDc = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;
	_imageInfo->fAnchorX = _anchorX;
	_imageInfo->fAnchorY = _anchorY;


	// Upper-Left
	_imageInfo->vertices[0].x = (LONG)(x - (_anchorX * (width / maxFrameX)));
	_imageInfo->vertices[0].y = (LONG)(y - (_anchorY * (height / maxFrameY)));

	// Upper-Right
	_imageInfo->vertices[1].x = (LONG)(x + ((width / maxFrameX) - (_anchorX * (width / maxFrameX))));
	_imageInfo->vertices[1].y = (LONG)(y - (_anchorY * (height / maxFrameY)));

	// Lower-Right
	_imageInfo->vertices[2].x = (LONG)(x + ((width / maxFrameX) - (_anchorX * (width / maxFrameX))));
	_imageInfo->vertices[2].y = (LONG)(y + ((height / maxFrameY) - (_anchorY * (height / maxFrameY))));


	// 예외처리
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻어오는 데 실패
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT GImage::initForAlphaBlend(void)
{
	HDC hdc = GetDC(_hWnd);

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER; //혼합 연산. 비트맵(픽셀)에 알파값을 넣겠다.

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->resID = 0;
	_blendImage->hMemDc = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDc, _blendImage->hBit);
	_blendImage->width = WINSIZE_X;
	_blendImage->height = WINSIZE_X;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void GImage::setTransColor(bool isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}

//외부
void GImage::release(void)
{
	if (_imageInfo)
	{
		//이미지 삭제
		SelectObject(_imageInfo->hMemDc, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDc);

		//포인터 삭제
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		//투명컬러키 초기화
		_isTrans = false;
		_transColor = RGB(0, 0, 0);
	}

	if (_blendImage)
	{
		//이미지 삭제
		SelectObject(_blendImage->hMemDc, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDc);

		//포인터 삭제
		SAFE_DELETE(_blendImage);
	}

}

void GImage::rotateUpdate(float _dt, int destX, int destY)
{
	//_imageInfo->fAngle += M_SPEED * _dt;
	_imageInfo->fAngle = _dt;
	if (_imageInfo->fAngle >= 360.0f) _imageInfo->fAngle = 0.0f;

	Rotate(_imageInfo->fAngle, destX, destY);
}

void GImage::rotateFrameUpdate(float _dt, int destX, int destY)
{
	_imageInfo->fAngle = _dt;
	if (_imageInfo->fAngle >= 360.0f) _imageInfo->fAngle = 0.0f;

	frameRotate(_imageInfo->fAngle, destX, destY);
}

//0,0
void GImage::render(HDC hdc)
{
	if (_isTrans)
	{
		//GdiTransparentBlt(): 비트맵을 불러올 때 특정 색상을 제외하고 복사
		GdiTransparentBlt
		(
			hdc,				//복사할 장소의 DC(화면에 보여지는 DC)
			0,					//복사될 좌표 시작(x)
			0,					//복사될 좌표 시작(y)
			_imageInfo->width,	//복사될 이미지 가로크기
			_imageInfo->height,	//복사될 이미지 세로크기
			_imageInfo->hMemDc, //복사될 대상 메모리 DC
			0,0,				//복사 시작 시점
			_imageInfo->width,	//복사 영역 가로크기
			_imageInfo->height,	//복사 영역 세로크기
			_transColor			//복사할 때 제외할 색상
		);
	}
	else
	{
		//BitBlt(): DC 간의 영역끼리 서로 고속복사를 해준다.
		//SRCCOPY: 소스 영역을 대상 영역에 복사한다.
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDc, 0, 0, SRCCOPY);
	}
}

// destX, destY
void GImage::render(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{
		//GdiTransparentBlt(): 비트맵을 불러올 때 특정 색상을 제외하고 복사
		GdiTransparentBlt
		(
			hdc,				//복사할 장소의 DC(화면에 보여지는 DC)
			destX,				//복사될 좌표 시작(x)
			destY,				//복사될 좌표 시작(y)
			_imageInfo->width,	//복사될 이미지 가로크기
			_imageInfo->height,	//복사될 이미지 세로크기
			_imageInfo->hMemDc, //복사될 대상 메모리 DC
			0, 0,				//복사 시작 시점
			_imageInfo->width,	//복사 영역 가로크기
			_imageInfo->height,	//복사 영역 세로크기
			_transColor			//복사할 때 제외할5 색상
		);
	}
	else
	{
		//BitBlt(): DC 간의 영역끼리 서로 고속복사를 해준다.
		//SRCCOPY: 소스 영역을 대상 영역에 복사한다.
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDc, 0, 0, SRCCOPY);
	}
}

//이미지 클리핑
//ㄴ 원본 이미지 지정 좌표로부터 가로, 세로 크기를 잘라 내가 원하는 좌표에 출력
void GImage::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans)
	{
		GdiTransparentBlt
		(
			hdc,				//복사할 장소의 DC(화면에 보여지는 DC)
			destX,				//복사될 좌표 시작(x)
			destY,				//복사될 좌표 시작(y)
			sourWidth,			//복사될 이미지 가로크기
			sourHeight,			//복사될 이미지 세로크기
			_imageInfo->hMemDc, //복사될 대상 메모리 DC
			sourX, sourY,		//복사 시작 시점
			sourWidth,			//복사 영역 가로크기
			sourHeight,			//복사 영역 세로크기
			_transColor			//복사할 때 제외할 색상
		);
	}
	else
	{
		//BitBlt(): DC 간의 영역끼리 서로 고속복사를 해준다.
		//SRCCOPY: 소스 영역을 대상 영역에 복사한다.
		BitBlt(hdc, destX, destY, sourWidth, sourHeight, _imageInfo->hMemDc, sourX, sourY, SRCCOPY);
	}
}

void GImage::alphaRender(HDC hdc, BYTE alpha)
{
	if (!_blendImage) initForAlphaBlend();
	
	//적용하려는 대상 객체 = 인자로 넘겨줄 alpha 넘겨주겠다.
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		//1. 출력해야 될 DC에 그려져 있는 내용을 블랜드 이미지에 그려준다.
		BitBlt
		(
			_blendImage->hMemDc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			0, 0,
			SRCCOPY
		);

		//2. 원본 이미지의 배경을 없앤 후 블랜드 이미지에 그린다.
		GdiTransparentBlt
		(
			_blendImage->hMemDc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor
		);

		//3. 블렌드 이미지를 화면에 그린다.
		AlphaBlend
		(
			hdc,
			0,0,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDc,
			0,0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);
	}
	else
	{
		AlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDc, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void GImage::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	if (!_blendImage) initForAlphaBlend();

	//적용하려는 대상 객체 = 인자로 넘겨줄 alpha 넘겨주겠다.
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		//1. 출력해야 될 DC에 그려져 있는 내용을 블랜드 이미지에 그려준다.
		BitBlt
		(
			_blendImage->hMemDc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			destX, destY,
			SRCCOPY
		);

		//2. 원본 이미지의 배경을 없앤 후 블랜드 이미지에 그린다.
		GdiTransparentBlt
		(
			_blendImage->hMemDc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDc,
			0,0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor
		);

		//3. 블렌드 이미지를 화면에 그린다.
		AlphaBlend
		(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDc, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

//당장은 쓸데가 없다.
void GImage::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
}

void GImage::frameRender(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{
		GdiTransparentBlt
		(
			hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDc,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDc,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void GImage::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//이미지 예외처리
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isTrans)
	{
		GdiTransparentBlt
		(
			hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDc,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDc,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void GImage::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//offset 값이 음수일 경우 보정
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//그려지는 영역 세팅
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	// 그려지는 DC 영역(화면크기)
	RECT rcDest;

	//그려야 할 전체 영역 세팅
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 루프영역
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//소스 영역의 높이 계산
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//소스 영역이 그리는 화면을 넘어 갔다면(화면밖으로 나갔다.)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그림의 값만큼 바텀값을 올려준다.
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//그려지는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//가로 루프영역
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//소스 영역의 높이 계산
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//소스 영역이 그리는 화면을 넘어 갔다면(화면밖으로 나갔다.)
			if (x + sourWidth > drawAreaW)
			{
				//넘어간 그림의 값만큼 바텀값을 올려준다.
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//그려지는 영역
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight);
		} //End for
	}
}

void GImage::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
}

void GImage::rotateRender(HDC hdc, int destX, int destY)
{
	//renderInfo(hdc);

	if (_isTrans)
	{
		LPPOINT ver = _imageInfo->vertices;
		int x = min(min(ver[0].x, ver[1].x), min(ver[2].x, ver[3].x));
		int y = min(min(ver[0].y, ver[1].y), min(ver[2].y, ver[3].y));
		int width = max(abs(ver[2].x - ver[1].x), abs(ver[3].x - ver[0].x));
		int height = max(abs(ver[2].y - ver[1].y), abs(ver[3].y - ver[0].y));

		RECT rect;
		rect.left = 0;
		rect.top = 0;
		rect.right = width;
		rect.bottom = height;

		HBRUSH transBrush = (HBRUSH)CreateSolidBrush(_transColor);

		POINT newVer[3];
		newVer[0].x = ver[0].x - x;
		newVer[0].y = ver[0].y - y;
		newVer[1].x = ver[1].x - x;
		newVer[1].y = ver[1].y - y;
		newVer[2].x = ver[2].x - x;
		newVer[2].y = ver[2].y - y;

		HDC winDC = GetDC(_hWnd);
		HDC tempHdc = CreateCompatibleDC(winDC);
		HBITMAP tempBitmap = CreateCompatibleBitmap(winDC, width, height);
		SelectObject(tempHdc, tempBitmap);
		FillRect(tempHdc, &rect, transBrush);
		PlgBlt(tempHdc, newVer, _imageInfo->hMemDc, 0, 0, _imageInfo->width, _imageInfo->height, NULL, 0, 0);
		GdiTransparentBlt(hdc, x, y, width, height, tempHdc, 0, 0, width, height, _transColor);

		DeleteDC(tempHdc);
		DeleteObject(tempBitmap);
		DeleteObject(transBrush);
		ReleaseDC(_hWnd, winDC);
	}
	else
	{
		PlgBlt(hdc, _imageInfo->vertices, _imageInfo->hMemDc, 0, 0, _imageInfo->width, _imageInfo->height, NULL, 0, 0);
	}
}

void GImage::rotateFrameRender(HDC hdc)
{
		//renderInfo(hdc);

	if (_isTrans)
	{
		LPPOINT ver = _imageInfo->vertices;
		int x = min(min(ver[0].x, ver[1].x), min(ver[2].x, ver[3].x));
		int y = min(min(ver[0].y, ver[1].y), min(ver[2].y, ver[3].y));
		int width = max(abs(ver[2].x - ver[1].x), abs(ver[3].x - ver[0].x));
		int height = max(abs(ver[2].y - ver[1].y), abs(ver[3].y - ver[0].y));

		RECT rect;
		rect.left = 0;
		rect.top = 0;
		rect.right = width;
		rect.bottom = height;

		HBRUSH transBrush = (HBRUSH)CreateSolidBrush(_transColor);

		POINT newVer[3];
		newVer[0].x = ver[0].x - x;
		newVer[0].y = ver[0].y - y;
		newVer[1].x = ver[1].x - x;
		newVer[1].y = ver[1].y - y;
		newVer[2].x = ver[2].x - x;
		newVer[2].y = ver[2].y - y;

		//새로운 비트맵 제작
		HDC winDC = GetDC(_hWnd);
		HDC tempHdc = CreateCompatibleDC(winDC);


		HBITMAP tempBitmap = CreateCompatibleBitmap(winDC, width, height);
		SelectObject(tempHdc, tempBitmap);
		
		//투명색 채우기
		FillRect(tempHdc, &rect, transBrush);

		//회전한 이미지
		PlgBlt(tempHdc, newVer, _imageInfo->hMemDc,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);

		//복사해서 넣기
		GdiTransparentBlt(hdc, x, y, width, height, tempHdc, 0, 0, width, height, _transColor);

		DeleteDC(tempHdc);
		DeleteObject(tempBitmap);
		DeleteObject(transBrush);
		ReleaseDC(_hWnd, winDC);
	}
	else
	{
		PlgBlt(hdc, _imageInfo->vertices, _imageInfo->hMemDc,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameWidth, NULL, 0, 0);
	}
}		

void GImage::scaleRender(HDC hdc, int dstX, int dstY, int dstWidth, int dstHeight, int srcX, int srcY, int srcWidth, int srcHeight)
{
	TransparentBlt(hdc, dstX, dstY, dstWidth, dstHeight,
		_imageInfo->hMemDc, srcX, srcY, min(srcWidth, _imageInfo->width), min(srcHeight, _imageInfo->height),
		_isTrans ? _transColor : RGB(255, 0, 255));
}


void GImage::Rotate(float _angle, int destX, int destY)
{
	//라디안 변환
	float theta = _angle * M_PI / 180.0f;

	float s = sinf(theta);
	float c = cosf(theta);

	float ver1x = (-_imageInfo->width * _imageInfo->fAnchorX);
	float ver1y = (-_imageInfo->height * _imageInfo->fAnchorY);

	float ver2x = (_imageInfo->width * (1.0f - _imageInfo->fAnchorX));
	float ver2y = (-_imageInfo->height * _imageInfo->fAnchorY);

	float ver3x = (-_imageInfo->width * _imageInfo->fAnchorX);
	float ver3y = (_imageInfo->height * (1.0f - _imageInfo->fAnchorY));

	float ver4x = (_imageInfo->width * (1.0f - _imageInfo->fAnchorX));
	float ver4y = (_imageInfo->height * (1.0f - _imageInfo->fAnchorY));



	//Upper-Left
	_imageInfo->vertices[0].x = (LONG)((ver1x * c - ver1y * s) + _imageInfo->x + destX);
	_imageInfo->vertices[0].y = (LONG)((ver1x * s + ver1y * c) + _imageInfo->y + destY);

	//Upper-Right
	_imageInfo->vertices[1].x = (LONG)((ver2x * c - ver2y * s) + _imageInfo->x + destX);
	_imageInfo->vertices[1].y = (LONG)((ver2x * s + ver2y * c) + _imageInfo->y + destY);

	_imageInfo->vertices[2].x = (LONG)((ver3x * c - ver3y * s) + _imageInfo->x + destX);
	_imageInfo->vertices[2].y = (LONG)((ver3x * s + ver3y * c) + _imageInfo->y + destY);

	_imageInfo->vertices[3].x = (LONG)((ver4x * c - ver4y * s) + _imageInfo->x + destX);
	_imageInfo->vertices[3].y = (LONG)((ver4x * s + ver4y * c) + _imageInfo->y + destY);
}

void GImage::frameRotate(float _angle, int destX, int destY)
{
	//라디안 변환
	float theta = _angle * M_PI / 180.0f;

	float s = sinf(theta);
	float c = cosf(theta);

	float ver1x = (-_imageInfo->frameWidth * _imageInfo->fAnchorX);
	float ver1y = (-_imageInfo->frameHeight * _imageInfo->fAnchorY);

	float ver2x = (_imageInfo->frameWidth * (1.0f - _imageInfo->fAnchorX));
	float ver2y = (-_imageInfo->frameHeight * _imageInfo->fAnchorY);

	float ver3x = (-_imageInfo->frameWidth * _imageInfo->fAnchorX);
	float ver3y = (_imageInfo->frameHeight * (1.0f - _imageInfo->fAnchorY));

	float ver4x = (_imageInfo->frameWidth * (1.0f - _imageInfo->fAnchorX));
	float ver4y = (_imageInfo->frameHeight * (1.0f - _imageInfo->fAnchorY));


	//Upper-Left
	_imageInfo->vertices[0].x = (LONG)((ver1x * c - ver1y * s) + _imageInfo->x + destX);
	_imageInfo->vertices[0].y = (LONG)((ver1x * s + ver1y * c) + _imageInfo->y + destY);

	//Upper-Right
	_imageInfo->vertices[1].x = (LONG)((ver2x * c - ver2y * s) + _imageInfo->x + destX);
	_imageInfo->vertices[1].y = (LONG)((ver2x * s + ver2y * c) + _imageInfo->y + destY);

	_imageInfo->vertices[2].x = (LONG)((ver3x * c - ver3y * s) + _imageInfo->x + destX);
	_imageInfo->vertices[2].y = (LONG)((ver3x * s + ver3y * c) + _imageInfo->y + destY);

	_imageInfo->vertices[3].x = (LONG)((ver4x * c - ver4y * s) + _imageInfo->x + destX);
	_imageInfo->vertices[3].y = (LONG)((ver4x * s + ver4y * c) + _imageInfo->y + destY);
}

void GImage::renderInfo(HDC hdc)
{
	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
	int radius = 5;
	Ellipse(hdc, _imageInfo->x - radius, _imageInfo->y - radius, _imageInfo->x + radius, _imageInfo->y + radius);
	DeleteObject(SelectObject(hdc, oldBrush));

	// 각종 정보
	char info[256];
	sprintf_s(info, "Position : (%f, %f)", _imageInfo->x, _imageInfo->y);
	TextOutA(hdc, 0, 0, info, strlen(info));

	sprintf_s(info, "Anchor Point : (%f, %f)", _imageInfo->fAnchorX, _imageInfo->fAnchorY);
	TextOutA(hdc, 0, 20, info, strlen(info));

	sprintf_s(info, "Angle : %f", _imageInfo->fAngle);
	TextOutA(hdc, 0, 40, info, strlen(info));
}	