#include "Stdafx.h"
#include "KeyManager.h"


KeyManager::KeyManager()
{
}

KeyManager::~KeyManager()
{
}


HRESULT KeyManager::init(void)
{
	//Ű���� ���� �������� ���� ���·� �ʱ�ȭ
	for (int i = 0; i < KEY_MAX; i++)
	{
		this->setKeyDown(i, false);
		this->setKeyUp(i, false);
	}

	return S_OK;
}

bool KeyManager::isOnceKeyDown(int key)
{
	/*
	GetAsyncKeyState
	- � Ű�� �ԷµȰ��� üũ or ���α׷����� Ű�� �Է¹ް� ������ ����ϴ� API ���� �Լ�
	- �޼��� ť�� �ִ� Ű�� ������ Ȯ���Ѵ�(�����´�).
	- Ű�� ���� ������ üũ�ϱ� ���� &(And) ������ ���
	*/

	//AND ����: & ������
	//�� ��Ʈ ������ AND ������ �����Ѵ�.
	//�� �� �� 1�� ���� ����� 1�̰�, �ƴ϶�� 0�̴�.
	if (GetAsyncKeyState(key) & 0x80000)
	{
		if (!this->getKeyDown()[key])
		{
			this->setKeyDown(key, true);
			return true;
		}
	}
	else this->setKeyDown(key, false);

	return false;
}

bool KeyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x80000)
	{
		this->setKeyUp(key, true);
	}
	else
	{
		if (this->getKeyUp()[key])
		{
			this->setKeyUp(key, false);
			return true;
		}
	}
	return false;
}

bool KeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}

bool KeyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}
