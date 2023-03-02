#pragma once

class Coin
{

private:
	int x, y;
	
	float vx, vy;
	int bounce;
	bool lost;
	bool remove;

public:
	Coin(int x, int y) : x(x), y(y), vx(0), vy(0), bounce(0), lost(false), remove(false) {}
	
	void update();
	bool isLost() const { return lost; }
	bool isRemove() const { return remove; }
	
	int getX() { return x; }
	int getY() { return y; }

	void setV(int x, int y) { vx = x; vy = y; }
	void renderVXVY(HDC hdc);
	void setLost() { lost = true; }
};

