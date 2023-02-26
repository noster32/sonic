#pragma once
#include "GameNode.h"
#include "Sonic.h"
#include "Coin.h"

class debugScene : public GameNode
{
private:
	Sonic* _sonic;
	GImage* _world;
	GImage* _worldUp;
	GImage* _worldDown;
	GImage* _coin;
	int _count;
	float cx;
	float cy;
	float loopSpeed1;
	float loopSpeed2;
	int ww;
	int wh;

	int eatRing;


	vector<Coin> coins;

	void createCoin(void);

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	 
	void coinSpread(void);


	debugScene() {}
	~debugScene() {}
};

