#pragma once
#include "GameNode.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "debugScene.h"
#include "TestScene.h"

#define PI 3.1415926535f
// ���� -> ����
#define DEGREE_TO_RADIAN(_deg)		(M_PI * (_deg) / 180.f)

class MainGame : public GameNode
{
private:
	TestScene* _testScene;
	debugScene* _debugScene;

	//���縸 ��� �����ϴ¾��� ����
	GameNode* _currentScene;
public:
	
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//Bullet bullet(1.0f, 1.0f, 1.0f);
	MainGame() : _currentScene(nullptr) {}

	


	

};




