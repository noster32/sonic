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
	//버퍼링 처리와 타이머가 없기 때문에 기본 함수 사용
	//새로 고침 
	InvalidateRect(_hWnd, NULL, false);
}




void GameNode::render(void)
{
	//상속 받는 쪽에서 그려주기
}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;         //핸들DC
	PAINTSTRUCT ps;            //페인트 구조체



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