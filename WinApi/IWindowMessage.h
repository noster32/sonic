#pragma once
#include <Windows.h>
/*
	������ ���� �Լ�
	�� �Լ��� �����ΰ� ���� ����ΰ� =0���� ������ �����Լ��� ���Ѵ�.
	�� �θ� Ŭ�������� ���� �����Լ��� �����ϸ� �ڽ� Ŭ���������� �ݵ�� �������� �Լ��� ����� ������ �־�� �Ѵ�.
	

	�� �߻� Ŭ����(Abstract Clsaa)
	- ���� ���� �Լ��� 1�� �̻� �ִ� Ŭ������ ���Ѵ�.

	�� Ư¡
	1. ��ü�� ������ �� ����. (��, ������ ������ ���� �� �ִ�.)
		�� �߻� Ŭ������ ������ ��ü(Ŭ����)�� �ν��Ͻ��� ���� �� ����.
		�� �߻� Ŭ������ �ڽ� Ŭ������ ���� �ν��Ͻ��� ������ �� �ִ�.

	2. ��� ���� or �Ϲ� ��� �Լ��� ���Ե� ���ο� ������� ���� �����Լ��� 1�� �̻� ������ �ִٸ� �߻� Ŭ������ ���ǿ� �ش�ȴ�.

	ex)
	//C++
	class IWindowMessage abstract
	{

	};

	//C#
	abstract class ITessllation
	{

	};


	�� �������̽�(Interface)
	- OCP (���� ����� ��Ģ)
		�� �ڽ��� Ȯ�忡�� ���� �ְ� �ֺ��� ��ȭ�� ���ؼ��� ���� �־�� �Ѵ�.
	- ���� �����Լ��� �̷���� Ŭ������ �������̽���� �Ѵ�.
	- �������̽��� ������ ���� Ŭ�������� �ݵ�� �����ؾ� �� �Լ��� �����ִ� Ŭ������� �� �� �ִ�.
	- C++ ���� �������̽���� ������ ������ ������� �������� �ʴ´�.
	- ǥ���: �Ľ�Į(I)
	�� �������̽�(���� �����Լ� ����) -> (���) �߻� Ŭ���� (�⺻ ��� ����) -> (���) �Ϲ� Ŭ����(���� �����Լ� ������)

	�� Ư¡
	- ��� ���� �� �Լ��� ������ �� ����. (���� �Լ� ����)
	- �Ӽ��� �����ϴ� �����ڸ� ����� �� ����. 
		�� ex. const
	- �⺻ Ŭ������ ��ӹ��� �� ����.
	- ���� ���� �Լ��� ���� ���Ѿ� �Ѵ�.
	- ������ / �Ҹ��� / �����ڸ� ������ �� ����.
	- public �Ӽ��� ������ �־�� �Ѵ�.

	//-> ��������.
	�� ����
	�ߺ����� ���� / �������� ����

	�� ����

	�� ���� �Ҹ���(��)
*/

/*
__interface IGameClass
{
	void idle();
	void attack();
};

class CharacterChoices abstract : public IGameClass
{
private:
	//! Do Something
public:
	//! Do Something
};

//�Ļ�
class Warrior : public CharacterChoices
{
private:

public:
		virtual void idle();
};

//�Ļ�
class Wizard : public CharacterChoices
{
private:

public:
	virtual void idle();
};
*/

class IWindowMessage
{
public:
	/*
	// ���� ���� �Լ� ����� ��
	virtual void IFunctionA() = 0;
	virtual void IFunctionB() = 0;
	virtual void IFunctionC() = NULL;
	virtual void IFunctionD() PURE; //��������� ��Ģ������ PURE ��ũ�δ� GameNode�� ���� �� �� ����.
	virtual void IFunctionE() abstract;
	*/
	IWindowMessage();
	~IWindowMessage();
};

