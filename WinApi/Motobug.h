#pragma once
#include "GameNode.h"
#include "Sonic.h"
class Motobug : public GameNode
{
private:
	GImage* _Motobug;

	RECT _motobugHitBox;

	Sonic* _sonic;

	float positionX;
	float positionY;

	float cx;
	float cy;
public:



	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Motobug() {}
	~Motobug() {}
};

