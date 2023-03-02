#pragma once
// ��� ����
// �� 4005: DXGI �� �׷��� �������̽����� ��ũ�� �����Ͽ� ���� ��µǴ� ���
#pragma warning(disable : 4005)



// ���� ������ �ʴ� ������ Windows ������� ����
#define WIN32_LEAN_AND_MEAN
// GDI+�� ����Ϸ��� ������� �����;� �Ѵ�.
// �� <ole2.h>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

//! Windows ��� ����
#include <windows.h>

//������ �ܼ�â
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

//! ���̺귯�� ��ũ
#pragma comment (lib, "msimg32.lib")


// SDKDDKVer.�� ���α׷����� ������ OS�� ���� Window�������
//�ڵ忡 ���Ե� �Լ�, ��� ���� �����ϴµ� ����� �ȴ�.
#include <SDKDDKVer.h>


//! C ��Ÿ�� ��� ����
#include <stdio.h>
#include <stdlib.h> //standard library
#include <memory.h>
#include <tchar.h> //���ڼ����ٲ��ִ� 
#include <time.h>
//C++ cassert���� �� ������
#include <assert.h>

/*
MBCS (Multi Byte Character Set)

- ��Ƽ ����Ʈ
�� ������ ����ϴ� ������ ���ڿ�
�� ��Ƽ ����Ʈ �ڵ�� ����� �ƽ�Ű �ڵ忡 ���ԵǴ� ���ڴ� 1����Ʈ,
���Ե��� �ʴ� ���ڴ� 2����Ʈ ó���� �Ѵ�.

WBCS (Wide Byte Character Set)

- ���� �ڵ�
�� ��� ���ڸ� 2����Ʈ�� ó���Ѵ�.

VS������ ���ڿ� ǥ��

- �츮�� ������ �ϴ� VS���� ��쿡�� MBCS/WBCS�� ��� ���� ����� ���� ��ø� ����� �Ѵ�.

�����ڵ�: ���ڿ��� "" ���ΰ� L�� ���δ� 
��Ƽ ����Ʈ: ���ڿ��� "" ���θ� ��

�����ڵ� < - > ��Ƽ����Ʈ �̽��� ���ؼ��� ���ڿ� ǥ������� �� ������ ��� �ϱ� ������
�߰� ��ũ�� ���� _T�� ����Ѵ�.

*/


//! C++ ��Ÿ�� ��� ����
#include <iostream>
/*
chorono
c+ 11���׼� �߰��� �ð����� ���̺귯��(STL)
�� ���� C ��Ÿ�ӿ��� �����ϴ� tinme �Լ����� �پ���/ Ȯ��� ��� ���
- ����:
�� ���е��� ���� (���� �и� �� ����)
	�� time �Լ��� �� ������ ���� ���� ����
- OS�� ���������� �����Ѵ�.

*/
#include <chrono>
#include <random> //�޸���Ʈ������ 1937���̿��� random
#include <vector> //�����迭
#include <map> //�����Ʈ���� ����� Ű�� ������ ���� �ڷ���
#include <unordered_map>
#include <string>
#include <bitset>
#include <cassert>
/*
unordered_map: Hash �ڷᱸ��
�� �Ϲ��� ��Ȳ������ map���� �˻� �ӵ��� �� ������.
�� �ߺ��� �����͸� ������� �ʴ´�
�� ��, ���� �����Ͱ� ���� �� (Key) �ؽ� �浹�� �߻��� ���� ����

*/
#include <unordered_map> 
#include <string> //���ڿ�
// ���߿� ������ �ּ���
//#include <cassert>

using namespace std;
//=====================
//! ����� ���� �������
//=====================
#include "CommonMacroFunction.h"
#include "randomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "TempSoundManager.h"

//========
//! �̱���
//========
//�޸𸮿� �ø���
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define TEMPSOUNDMANAGER TempSoundManager::getSingleton()
/*
//! D2D/D3D ��� ����
#include <D2D1.h>
#include <d2d1helper.h>
#include <d3dx9.h>
#include <D3DX11.h>
#include <d3d11shader.h>
#include <dinput.h>

//lib = ���̺귯��
//���̺귯�� ��ũ
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

ID2D1Factory*					_ID2DFactory = nullptr;
ID2D1HwndRenderTarget*			_ID2DRendertarget = nullptr;
*/


//=============================
// # ��ũ�� # (������ â �ʱ�ȭ)
//=============================

// !��üȭ��
//#define FULL_SCREEN


#ifdef FULL_SCREEN

#define WIN_NAME		(LPSTR)(TEXT("Window API"))
#define WINSTART_X		0
#define WINSTART_Y		0
//GetSystemMetrics(): ���ڷ� ���޵Ǵ� �ý��� ���� ������ ��ȯ�Ѵ�.
	// �� SM_CXSCREEN: ���� ȭ�� ���� �ػ� X�� ��ȯ
#define WINSIZE_X		GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y		GetSystemMetrics(SM_CYSCREEN)
// WS_POPUPWINDOW: �˾� ������ ����
// WS_MAXIMIZE: ������ ������ �ִ�ȭ
#define WINSTYLE		WS_POPUPWINDOW | WS_MAXIMIZE

//WS_CAPTION: Ÿ��Ʋ �ٸ� ������ ���� �ɼ�
//WS_STSMENU: ���� ǥ���ٿ� ��Ʈ�� �޴� ���� â�� ����� �ɼ� (_ �� X)
#define WINSTYLE		WS_CAPTION | WS_SYSMENU
#else
#define WIN_NAME		(LPSTR)(TEXT("Sonic Mania"))
#define WINSTART_X		400
#define WINSTART_Y		100
#define WINSIZE_X		1280
#define WINSIZE_Y		720
//WS_CAPTION: Ÿ��Ʋ �ٸ� ������ ���� �ɼ�p
//WS_STSMENU: ���� ǥ���ٿ� ��Ʈ�� �޴� ���� â�� ����� �ɼ� (_ �� X)
#define WINSTYLE		WS_CAPTION | WS_SYSMENU
#endif


//=================
// # ��ũ��  �Լ� # 
//=================

//p ������ ��
#define SAFE_DELETE(p)				{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)		{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)				{if(p) {(p)->release(); (p) = nullptr;}}

//==============
// # ���� ���� # 
//==============
// extern Ű����� �ٸ� ��� or cpp���� ������ �����ϱ� ���� ����Ѵ�.
// �� ���� ������ Ű���带 �����ص� �⺻���� extern ȭ �Ǵ� ��찡 �ִ�. (VS ����)
extern HINSTANCE		_hInstance;
extern HWND				_hWnd;
//X ��ǥ�� Y��ǥ�� ����� ��ǥ�� ������ �� ���
//POINT : XY��ǥ
extern POINT			_ptMouse;


