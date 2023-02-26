#pragma once

//POINT
inline POINT PointMake(int x, int y)
{
	POINT pt = { x,y };
	return pt;
}

//�� �׸���
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	//C++������ C��Ÿ�Ͽ� ���� NULL�� ���������� ���� ��ȣ�Զ����� �ڷ��� ������ �ʿ� ����. ���� ��� bool�� BOOL.
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

//RECT �����
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x,y,x + width,y + height };
	return rc;
}

//�簢�� �׸��� (���ʱ� �Լ� ���)
inline void DrawRectMake(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

// RECT �߽��� �����
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y- height / 2, x + width / 2, y + height / 2 };
	return rc;
}

//�簢�� �׸��� ( ���ʱ� �Լ� ���) - ������� �� �� �ҷ����� �� �Ϸ��� ����
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, width, height);
}

//Ÿ�� �׸���(�ϸ��� �Լ� ���)
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//Ÿ�� ������ �߽����� �׸��� (�ϸ��� �Լ� ���)
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

