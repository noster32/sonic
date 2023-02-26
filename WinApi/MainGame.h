#pragma once
#include "GameNode.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "debugScene.h"
#include "TestScene.h"

#define PI 3.1415926535f
// 각도 -> 라디안
#define DEGREE_TO_RADIAN(_deg)		(M_PI * (_deg) / 180.f)

class MainGame : public GameNode
{
private:
	TestScene* _testScene;
	debugScene* _debugScene;

	//현재만 사용 사용안하는씬은 제거
	GameNode* _currentScene;
public:
	
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//Bullet bullet(1.0f, 1.0f, 1.0f);
	MainGame() : _currentScene(nullptr) {}

	


	

};




