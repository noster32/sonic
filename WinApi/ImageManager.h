#pragma once
#include "SingletonBase.h"
#include "GImage.h"

/*
STL �� �ٽ�
- Ű, ���� ���� ����
�� ù��° first
�� �ι�° second

- ���� �߰��ϴ� ����� insert�� ����ϰ� Ű�� ������ ���ÿ� �߰��ؾ� �ϴ� pair�̳� make_pair�� ����Ѵ�.
*/

class ImageManager:public SingletonBase<ImageManager>
{
private:
	typedef map<string, GImage*> mapImageList;
	typedef map<string, GImage*>::iterator mapImageIter;

private:
	mapImageList _mImageList;

public :
	HRESULT init(void);
	void release(void);
	
	GImage* addImage(string strKey,int width, int height);
	GImage* addImage(string strKey,const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GImage* addImage(string strKey,const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GImage* addFrameImage(string strKey,const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GImage* addFrameImage(string strKey,const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GImage* addRotateImage(string strKey, const char* fileName, float x, float y, int width, int height, float _anchorX, float _anchorY, bool isTrans, COLORREF transColor);
	GImage* addRotateFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, float _anchorX, float _anchorY, bool isTrans, COLORREF transColor);
	GImage* findImage(string strKey);
	bool deleteImage(string strKey);
	bool deleteAll();

	void rotateUpdate(string strKey, float _dt, int destX, int destY);
	void rotateFrameUpdate(string strKey, float _dt, int destX, int destY);

	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	void rotateRender(string strKey, HDC hdc, int destX, int destY);
	void rotateFrameRender(string strKey, HDC hdc);

	ImageManager() {}
	~ImageManager() {}
};

