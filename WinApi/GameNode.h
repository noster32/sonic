#pragma once
#include "GImage.h"

#pragma region 객체지향 4대 ㅌ측징 및 5대 설계 원칙
/*
	▶ 객체지향 프로그래밍 (OOP)

	- 코드의 재사용성이 높고 코드 관리가 용이하다.

	- 신뢰성이 높은 프로그래밍 작성을 가능하게 한다.
	ㄴ 일반화 프로그래밍

	▶ 객체지향 4대 특징

	1. 캡술화
	ㄴ 객체의 속성을 보호한다.

	2. 상속
	ㄴ 객체지향에서의 상속이란 하위로 내려 갈수록 좀더 구체화 되는것을 의미한다.
	ㄴ 재사용성 향상 / 확장성 증가 / 유지보수 효율 Up

	3. 다형성
	ㄴ 하나의 객체가 여러 형태로 변화하는 것을 의미
	
	4. 추상화
	ㄴ 공통적인 부분과 특정 특성을 분리 및 추출해 재조합 하거나 재구성 하는 행위
		ㄴ 다형성 + 상속은 모두 추상화에 속한다.

	▶ 객체지향 5대 설계 원칙 SOLID

	1. SRT (단일 책임의 원칙)
	ㄴ 결합도를 낮추고 응집도를 높여라

	- 결합도
	ㄴ 모듈(클래스)간의 상호 의존 정도를 나타내는 지표
	ㄴ 결합도가 낮아지면 상호 의존성이 줄어서 재사용 및 유지보수 편리

	- 응집도
	ㄴ 하나의 모듈 내부에 존재하는 구성 요소들의 기능적 관련성
	ㄴ 응집도가 높은 모듈은 하나의 책임에 집중할 수 있고 독립서이 높아져 재사용과
	유지보수가 편리하다.

	2. OCP (개방 폐쇄의 원칙)
	ㄴ 자신의 확장에는 열려 있고, 추상의 변화에는 남겨 있어야 한다는 여칙

	ㄴ 상위 클래스 또는 인터페이스를 중간에 두어 자신의 변화에 대헤서는 폐쇠하고
	인터페이스는 외부의 변화에 확장성을 개방한다,

	3. LSP (리스코브 치환의 법칙)
	ㄴ 하위 타입은 언제나 자신의 기반이 되는 상위 타입으로 교체될 수 있어야 한다.
	
	ex> 상위: 운송수단, 자동차 / 하위: 아반떼 그랜져, 제네시스, ....


	4. ISP (인터페이스 분리의 법직)
	ㄴ 클라이언트는 자신이 사용하지 않는 함수(메서드)에 의존 관계를 맺으면 안된다.
	ㄴ 인터페이스로 각 기능을 분리하여 사용하는 함수(메서드)에만 의존 관계를 형성한다.
	ㄴ 현재 만들어 지고 있는 프로젝트의 설계 방식에 따라 SRP or ISP 을 선택한다.



	5. DIP (의존관계 역전의 법칙)
	ㄴ 자신보다 변하기 쉬운 것에 대해 의존하지 말아야 한다.

	//HRESULT: 함숙 성공적으로 실해오디었는지 체크
	//ㄴ 32qlxm 냐훋ㅇ wjdtn (음수가 아닌 값들은 성공을 의미하며 음수값들 실패를 의미

*/
#pragma endregion

//다른클래스에서 게임노드를 상속 받을때 백버퍼가 자동으로 들어감
static GImage* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZE_X, WINSIZE_Y);

class GameNode
{
private:
	HDC _hdc;
	bool _managerInit;



public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	GImage* getBackBuffer(void) { return _backBuffer; }

	//메모리 DC 얻기
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	//HDC 얻기(화면 DC)
	HDC getHDC() { return _hdc; }
	

	// 메인 프로시저
	//LRESULT : 콜백의 반환형으로 많이 사용된다.
	// ㄴ 메세지 처리를 마친 후 OS에게 신호를 주기 위한 값
	// ㄴ 스위치 문에서 각 메세지에 대한 처리값을 -1 0 1로 나눠서 운영체제에 작업을 해야하는지 알려준다.
	// ㄴ 0을 반환하면 모든 메세지가 처리되었다는 의미
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	GameNode() {}
	virtual ~GameNode() {}
	/*
	G.N		M.G
	A <----> B

	B의 소멸자가 작동시 A의 소멸자 확인 A의 소멸자 호출 그리고 끝


	가상 소멸자 A일경우
	B의 소멸자가 작동시 A의 소멸자 확인 소멸자 B호출 소멸자 A호출

	가상소멸자일경우 자식부터 시작해서 부모 소멸
	*/
};

