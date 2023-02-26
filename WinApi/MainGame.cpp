#include "Stdafx.h"
#include "MainGame.h"
#include "resource.h"


HRESULT MainGame::init(void)
{
	//��带 �ȿ��� �ٷ� ����
	GameNode::init(TRUE);

	_testScene = new TestScene;
	_testScene->init();

	_debugScene = new debugScene;
	_debugScene->init();

	//�ٽ�
	_currentScene = _debugScene;

	// <!-!>
	assert(_currentScene != nullptr);

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	SAFE_DELETE(_debugScene)
	SAFE_DELETE(_testScene)
}

void MainGame::update(void)
{
	GameNode::update();

	_currentScene->update();
	
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	_currentScene->render();
	this->getBackBuffer()->render(getHDC());
}




