#pragma once
#include "GameNode.h"
#include "Coin.h"
# define M_PI        3.14159265358979323846


struct sSonic
{
	RECT HitBox;
	float speed;
	float hSpeed;
	float jHeight;
	float accel;

	
	//Movement
	bool isMove;
	bool isMoveF;
	bool isMoveVF;
	bool isSkid;
	bool isLeft;
	bool isJump;
	bool isLookUp;
	bool isLookUpAnimLeft;
	bool isMoveAnimLeft;
	bool isCrouchAnimLeft;
	bool isCrouch;
	bool isBallMode;
	bool isSpinDash;
	bool isSpinDashRemain;
	bool isDropDash;
	bool isDamaged;
	
	//Status
	bool isNotControl;
	bool isAir;
	bool onEdge;
	bool onEdgeAfter;
};

struct Vector2D {
	float x, y;

	Vector2D() : x(0.0f), y(0.0f) { }
	Vector2D(float x, float y) : x(x), y(y) { }

	Vector2D operator + (const Vector2D& v2) const { return Vector2D(x + v2.x, y + v2.y); }
	Vector2D operator - (const Vector2D& v2) const { return Vector2D(x - v2.x, y - v2.y); }
	Vector2D operator * (const float f) const { return Vector2D(x * f, y * f); }

	void operator += (const Vector2D& v2) { x += v2.x; y += v2.y; }
};


class Sonic : public GameNode
{
private:
	
	GImage* _sonicImg;
	RECT _sonicDraw;
	Vector2D position;
	Vector2D velocity;

	vector<Coin> coins; 
	

	int _score;
	int _eatRing;

	int centerX;
	int centerY;
	
	int min1;
	int min2;
	int sec1;
	int sec2;
	int milliSec1;
	int milliSec2;

	int c1;
	int c2;
	int c3;

	bool is360;
	//Collision
	int _underLeftX;
	int _underRightX;
	int _upperLeftX;
	int _upperRightX;
	int _reverseUpY;
	int _reverseDownY;
	int _probeXL;
	int _probeX;
	int _probeY;

	//Hitbox
	int hitboxX;
	int hitboxY;

	//time
	int _count;

	//Anim
	int _idleFrame, _moveFrame, _jumpFrame, _skidFrame, _lookUpFrame, _crouchFrame,
		_ballModeFrame, _spinDashFrame, _dropDashFrame, _damagedFrame;
	int _repeatIdle1, _repeatIdle2, _repeatIdle3, _delayIdle, _delayLookUp;

	//Status
	int _afkCount;
	float _gravity;
	float _fallSpeed;
	float _sonicRotate;

	//Camera
	float cameraX;
	float cameraY;
	int ww;
	int wh;

	bool onPixelLeft;
	bool onPixelRight;
	bool onPixel;
	sSonic _sSonic;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void sonicKeybind(void);
	void sonicAnim(void);
	void sonicCollision(void);
	void sonicRotateCal(void);
	void debugLog(void);

	void gravity(void);
	void jump(void);

	float getCameraX() { return cameraX; }
	float getCameraY() { return cameraY; }

	float getSonicX() { return position.x; }
	float getSonicY() { return position.y; }

	void setEatCoin(int eatRing) { _eatRing = eatRing; }
	int getEatCoin() { return _eatRing; }

	RECT getHitbox() { return _sSonic.HitBox; }

	bool getIsHit() { return _sSonic.isDamaged; }


	Sonic() {}
	~Sonic() {}

private:
	void UpdateCamera();
	void force360rolling();
};

