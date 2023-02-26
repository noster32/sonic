#include "Stdafx.h"
#include "GameNode.h"


HRESULT GameNode::init(void)
{

	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		SetTimer(_hWnd, 1, 10, NULL);

		KEYMANAGER->init();
		RND->init();
		IMAGEMANAGER->init();
	}


	return S_OK;
}

void GameNode::release(void)
{
	if (_managerInit)
	{

		KillTimer(_hWnd, 1);

		
		KEYMANAGER->releaseSingleton();
		RND->releaseSingleton();
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);

}

void GameNode::update(void)
{
	//���۸� ó���� Ÿ�̸Ӱ� ���� ������ �⺻ �Լ� ���
	//���� ��ħ 
	InvalidateRect(_hWnd, NULL, false);
}




void GameNode::render(void)
{
	//��� �޴� �ʿ��� �׷��ֱ�
}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;         //�ڵ�DC
	PAINTSTRUCT ps;            //����Ʈ ����ü



    switch (iMessage)
    {
	case WM_TIMER:
		this->update();
		break;

    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
		this->render();
		EndPaint(hWnd, &ps);
        break;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
     case WM_DESTROY:               
         PostQuitMessage(0);
         return 0;
    }

    return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}