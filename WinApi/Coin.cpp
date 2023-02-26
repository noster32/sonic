#include "Stdafx.h"
#include "Coin.h"

void Coin::update()
{
	int probeX, probeXL, probeY = 0;
	bool bottomCollide = false;
	bool leftCollide = false;
	bool rightCollide = false;


	if (!lost) return;

	probeX = x + 8;
	probeXL = x - 8;
	probeY = y + 8;
	bottomCollide, leftCollide, rightCollide = false;

	HDC world = IMAGEMANAGER->findImage("debugMap")->getMemDC();

	COLORREF color = GetPixel(world, x, y + 8);

	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);

	if (color != RGB(255, 0, 255))
	{
		bottomCollide = true;
		y -= 3;
	}

	color = GetPixel(world, x - 8, y);

	if (color != RGB(255, 0, 255))
	{
		rightCollide = true;
		x -= 3;
	}

	color = GetPixel(world, x+ 8, y);

	if (color != RGB(255, 0, 255))
	{
		leftCollide = true;
		x += 3;
	}
	

	if (bounce < 3) {
		if (leftCollide || rightCollide)
			vx *= -1;

		if (bottomCollide)
		{
			vy *= -0.8;
			bounce++;
		}
	}
	x += vx;
	y -= vy;

	vy -= 0.5f;

	if (y > 2048)
		remove = true;
}
