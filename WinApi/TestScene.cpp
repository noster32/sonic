#include "Stdafx.h"
#include "TestScene.h"

HRESULT TestScene::init(void)
{

	IMAGEMANAGER->addRotateImage("�׽�Ʈ", "Resources/Images/Object/Tank.bmp", 150, 150, 70, 60, .5f, .5f, true, RGB(255, 0, 255));

	//IMAGEMANAGER->addRotateFrameImage("�׽�Ʈ3", "Resources/Images/Enemy/Motobug.bmp", 200, 200, 410, 116, 10, 4, .5f, .5f, true, RGB(255, 0, 255));
	testdt = 0;
 
	return S_OK;
}

void TestScene::release(void)
{
}

void TestScene::update(void)
{

	testdt++;
	if (testdt > 360) testdt = 0;

	//IMAGEMANAGER->findImage("�׽�Ʈ3")->setFrameY(0);
	//IMAGEMANAGER->findImage("�׽�Ʈ3")->setFrameX(0);

	

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		positionX++;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		positionX--;
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		positionY++;
	if (KEYMANAGER->isStayKeyDown(VK_UP))
		positionY--;
	//IMAGEMANAGER->rotateFrameUpdate("�׽�Ʈ3", testdt, positionX, positionY);
	IMAGEMANAGER->rotateUpdate("�׽�Ʈ", testdt, positionX, positionY);
}

void TestScene::render(void)
{
	

	IMAGEMANAGER->rotateRender("�׽�Ʈ", getMemDC(), 0, 0);
	//IMAGEMANAGER->rotateFrameRender("�׽�Ʈ3", getMemDC());
}
