#include "Stdafx.h"
#include "MainGame.h"

// =================
// # ���� ���� #
// =================
HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0,0 };
//TCHAR* pszSting = _T("Windows API");

// =================
// # �Լ� ���漱�� #
// =================
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

MainGame* _mg;

/*
int WINAPI _tWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    TCHAR* lpszCmdParam,
    int       nCmdShow)
{

}
*/

//������ ���� �Լ�
int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR    lpszCmdParam,
    int       nCmdShow)
{
    _mg = new MainGame();
    //�ش�Ǵ� �ν��Ͻ��� ���������� ��´�.
    _hInstance = hInstance;

    //������ â ����ü ���� �� �ʱ�ȭ
    WNDCLASS wndClass;

    wndClass.cbClsExtra = 0; //Ŭ���� ���� �޸�
    wndClass.cbWndExtra = 0; //������ ���� �޸�
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //��׶���. GetStockObject() �����Ҵ� �����ϰ� Ȯ���� �Լ�.
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW); //���콺Ŀ�� ������
    wndClass.hIcon = LoadIcon(NULL, IDC_APPSTARTING); //������
    wndClass.hInstance = hInstance; //�����츦 ������ ���α׷��� �ĺ��� ����
    wndClass.lpfnWndProc = (WNDPROC)WndProc; //������ ���ν���. ���ܹ߻��� ó���ϱ� ���� (WNDPROC)�� ���.
    wndClass.lpszClassName = WIN_NAME; //�𷡽� �̸�(������ Ŭ���� �ĺ��� ����)
    wndClass.lpszMenuName = NULL; //�޴� �̸�
    wndClass.style = CS_HREDRAW | CS_VREDRAW; //������ ��Ÿ��(������ �ٽñ׸��� ����)

    //HRESULT hr;
    //hr = RegisterClass(&wndClass);
    //�ڵ带 �о���̴� �����Ϸ��� ���������� assert�� ������ ������
    //assert(SUCCEEDED(hr));


    // ������ Ŭ���� ���
    RegisterClass(&wndClass);

#ifdef FULL_SCREEN

    DEVMODE dm;

    ZeroMemory(&dm, sizeof(DEVMODE));
    dm.dmSize = sizeof(DEVMODE);
    dm.dmBitsPerPel = 32;
    dm.dmPelsWidth = 1980;
    dm.dmPelsHeight = 1020;
    dm.dmDisplayFrequency = 60;             //����� 60Hz

    //�츮�� ������ �÷���(�ɼ�) �� ����
    dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

    //ȭ���� ����Ǹ� ���� �ػ󵵷� ����(�ڵ�����)
    if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
    {
        ChangeDisplaySettings(&dm, 0);
    }

    // ȭ�鿡 ������ ������ â ����
    _hWnd = CreateWindow
    (
        WIN_NAME, //������ Ŭ���� �ĺ���
        WIN_NAME, //������ Ÿ��Ʋ �� �̸�
        WINSTYLE, //������ ��Ÿ��
        WINSTART_X, //������ ȭ�� x��ǥ
        WINSTART_Y, //������ ȭ�� y��ǥ
        WINSIZE_X, //������ ȭ�� ����ũ��
        WINSIZE_Y, //������ ȭ�� ����ũ��
        NULL, //�θ� ������ ��������.
        (HMENU)NULL, //�޴� �ڵ�
        hInstance, //�ν��Ͻ� ����
        NULL //�������� �ڽ� �����츦 �����ϸ� �����ϰ� �ƴ϶�� NULL. - �ʿ信 ���� ��������� ������ NULL
    );

    // Ŭ���̾�Ʈ ������ ����� ��Ȯ�� ��´�.
    setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

#else

    // ȭ�鿡 ������ ������ â ����
    _hWnd = CreateWindow
    (
        WIN_NAME, //������ Ŭ���� �ĺ���
        WIN_NAME, //������ Ÿ��Ʋ �� �̸�
        WINSTYLE, //������ ��Ÿ��
        WINSTART_X, //������ ȭ�� x��ǥ
        WINSTART_Y, //������ ȭ�� y��ǥ
        WINSIZE_X, //������ ȭ�� ����ũ��
        WINSIZE_Y, //������ ȭ�� ����ũ��
        NULL, //�θ� ������ ��������.
        (HMENU)NULL, //�޴� �ڵ�
        hInstance, //�ν��Ͻ� ����
        NULL //�������� �ڽ� �����츦 �����ϸ� �����ϰ� �ƴ϶�� NULL. - �ʿ信 ���� ��������� ������ NULL
    );

    // Ŭ���̾�Ʈ ������ ����� ��Ȯ�� ��´�.
    setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

#endif

    // ȭ�鿡 ������â �����ֱ�
    ShowWindow(_hWnd, nCmdShow);

    //���� ���� Ŭ���� �ʱ�ȭ ���� �� ����
    if (FAILED(_mg->init()))
    {
        return 0;
    }

    //MSG: �ü������ �߻��ϴ� �޼��� ������ �����ϱ� ���� ����ü.
    MSG message;

    // 2. �޽��� ����
    /*
    //���ӿ�
    while (true)
    {
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)
        {
            if(message.message == WM_QUIT) break;

            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }
    */
    //PM_REMOVE: ���� 1�� 16������ �ٲ� ���� ��. -> �ӵ��� �ø��� ����.
    //�Ϲ� ���α׷���
    while (GetMessage(&message, 0, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    _mg->release();
    //������ Ŭ���� ��� ����
    UnregisterClass(WIN_NAME, hInstance);
    return message.wParam;
}

//������ ���ν���
LRESULT CALLBACK WndProc(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam)
{
    return _mg->MainProc(hWnd, IMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
    RECT rc = { 0,0,width,height };

    //���� ������ ũ�� ����
    //AdjustWindowRect() : ��� ��ü, ����� ������ ��Ÿ��, �޴� ����
    AdjustWindowRect(&rc, WINSTYLE, false);

    //���� ��Ʈ�� ������ ������ ������ ����
    SetWindowPos(_hWnd, NULL, x, y,
        (rc.right - rc.left),
        (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);
    //ZORDER : ��ü���� �������� �� ���̾� ���� ������ ���� ���(������). ���ӿ��� ���� ���δ�.
    //�츮 ȭ���� ���� �տ� ���ڴ�. (����)
}