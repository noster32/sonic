#include "Stdafx.h"
#include "Motobug.h"

HRESULT Motobug::init(void)
{
	_Motobug = IMAGEMANAGER->addFrameImage("Motobug", "Resources/Images/Enemy/Motobug.bmp", 410, 116, 10, 4, true, RGB(255, 0, 255));

	positionX = 1500;
	positionY = 1500;
	_sonic = new Sonic;
	_sonic->init();
	return S_OK;
}

void Motobug::release(void)
{
	SAFE_DELETE(_Motobug)
	SAFE_DELETE(_sonic)
}

void Motobug::update(void)
{
	_sonic->update();
	_motobugHitBox = RectMakeCenter(positionX, positionY, 41, 29);

	cx = _sonic->getCameraX();
	cy = _sonic->getCameraY();
}

void Motobug::render(void)
{
	IMAGEMANAGER->frameRender("Motobug", getMemDC(), positionX - cx, positionY - cy);
}
