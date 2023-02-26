#pragma once
#include "GameNode.h"
class TestScene : public GameNode
{
private:
	float testdt;
	int positionX = 100;
	int positionY = 100;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	TestScene() {}
	~TestScene() {}
};

