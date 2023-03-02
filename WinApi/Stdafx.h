#pragma once
// 경고 무시
// ㄴ 4005: DXGI 등 그래픽 인터페이스에서 매크로 관련하여 많이 출력되는 경고
#pragma warning(disable : 4005)



// 거의 사용되지 않는 내용을 Windows 헤더에서 제외
#define WIN32_LEAN_AND_MEAN
// GDI+를 사용하려면 헤더파일 꺼내와야 한다.
// ㄴ <ole2.h>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

//! Windows 헤더 파일
#include <windows.h>

//디버깅용 콘솔창
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

//! 라이브러리 링크
#pragma comment (lib, "msimg32.lib")


// SDKDDKVer.는 프로그램에서 지원할 OS에 따라 Window헤더에서
//코드에 포함될 함수, 상수 등을 제어하는데 사용이 된다.
#include <SDKDDKVer.h>


//! C 런타임 헤더 파일
#include <stdio.h>
#include <stdlib.h> //standard library
#include <memory.h>
#include <tchar.h> //문자셋을바꿔주는 
#include <time.h>
//C++ cassert보다 더 가볍다
#include <assert.h>

/*
MBCS (Multi Byte Character Set)

- 멀티 바이트
ㄴ 기존에 사용하던 형태의 문자열
ㄴ 멀티 바이트 코드는 영어같은 아스키 코드에 포함되는 문자는 1바이트,
포함되지 않는 문자는 2바이트 처리를 한다.

WBCS (Wide Byte Character Set)

- 유니 코드
ㄴ 모든 문자를 2바이트로 처리한다.

VS에서의 문자열 표현

- 우리가 개발을 하는 VS같은 경우에는 MBCS/WBCS중 어느 것을 사용한 건지 명시를 해줘야 한다.

유니코드: 문자열을 "" 감싸고 L을 붙인다 
멀티 바이트: 문자열을 "" 감싸면 끝

유니코드 < - > 멀티바이트 이식을 위해서는 문자열 표현방식을 다 변경해 줘야 하기 때문에
중간 매크로 형인 _T를 사용한다.

*/


//! C++ 런타임 헤더 파일
#include <iostream>
/*
chorono
c+ 11ㅇ네서 추가된 시간관련 라이브러리(STL)
ㄴ 기존 C 런타임에서 제공하는 tinme 함수보다 다양한/ 확장된 기능 사용
- 장점:
ㄴ 정밀도가 높다 (나노 밀리 초 단위)
	ㄴ time 함수는 초 단위의 값만 축정 가능
- OS와 독립적으로 동작한다.

*/
#include <chrono>
#include <random> //메르센트위스터 1937을이용한 random
#include <vector> //동적배열
#include <map> //레드블랙트리에 기반한 키와 벨류를 가진 자료형
#include <unordered_map>
#include <string>
#include <bitset>
#include <cassert>
/*
unordered_map: Hash 자료구조
ㄴ 일반적 상황에서는 map보다 검색 속도가 더 빠르다.
ㄴ 중복된 데이터를 허용하지 않는다
ㄴ 단, 유사 데이터가 많을 시 (Key) 해시 충돌이 발생해 성능 저하

*/
#include <unordered_map> 
#include <string> //문자열
// 나중에 설명해 주세요
//#include <cassert>

using namespace std;
//=====================
//! 사용자 정의 헤더파일
//=====================
#include "CommonMacroFunction.h"
#include "randomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "TempSoundManager.h"

//========
//! 싱글톤
//========
//메모리에 올리기
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define TEMPSOUNDMANAGER TempSoundManager::getSingleton()
/*
//! D2D/D3D 헤더 파일
#include <D2D1.h>
#include <d2d1helper.h>
#include <d3dx9.h>
#include <D3DX11.h>
#include <d3d11shader.h>
#include <dinput.h>

//lib = 라이브러리
//라이브러리 링크
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
// # 매크로 # (윈도우 창 초기화)
//=============================

// !전체화면
//#define FULL_SCREEN


#ifdef FULL_SCREEN

#define WIN_NAME		(LPSTR)(TEXT("Window API"))
#define WINSTART_X		0
#define WINSTART_Y		0
//GetSystemMetrics(): 인자로 전달되는 시스템 설정 정보를 반환한다.
	// ㄴ SM_CXSCREEN: 현재 화면 기준 해상도 X축 반환
#define WINSIZE_X		GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y		GetSystemMetrics(SM_CYSCREEN)
// WS_POPUPWINDOW: 팝업 윈도우 생성
// WS_MAXIMIZE: 윈도우 사이즈 최대화
#define WINSTYLE		WS_POPUPWINDOW | WS_MAXIMIZE

//WS_CAPTION: 타이틀 바를 가지기 위한 옵션
//WS_STSMENU: 제목 표시줄에 컨트롤 메뉴 상자 창을 만드는 옵션 (_ ㅁ X)
#define WINSTYLE		WS_CAPTION | WS_SYSMENU
#else
#define WIN_NAME		(LPSTR)(TEXT("Sonic Mania"))
#define WINSTART_X		400
#define WINSTART_Y		100
#define WINSIZE_X		1280
#define WINSIZE_Y		720
//WS_CAPTION: 타이틀 바를 가지기 위한 옵션p
//WS_STSMENU: 제목 표시줄에 컨트롤 메뉴 상자 창을 만드는 옵션 (_ ㅁ X)
#define WINSTYLE		WS_CAPTION | WS_SYSMENU
#endif


//=================
// # 매크로  함수 # 
//=================

//p 포인터 값
#define SAFE_DELETE(p)				{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)		{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)				{if(p) {(p)->release(); (p) = nullptr;}}

//==============
// # 전역 변수 # 
//==============
// extern 키워드는 다른 헤더 or cpp에서 변수를 공유하기 위해 사용한다.
// ㄴ 전역 변수는 키워드를 생략해도 기본으로 extern 화 되는 경우가 있다. (VS 버전)
extern HINSTANCE		_hInstance;
extern HWND				_hWnd;
//X 좌표와 Y좌표를 평면의 좌표에 정의할 때 사용
//POINT : XY좌표
extern POINT			_ptMouse;


