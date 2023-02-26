#pragma once
#include "SingletonBase.h"

class RandomFunction : public SingletonBase<RandomFunction>
{
public:
	RandomFunction()
	{
		//API ���� �Լ�
		// GetTickCount() : API �Լ��� OS�� ���õ� ���� ��� �ð��� üũ
		// �� �и����� ������ üũ�� �����ϸ� �и����� ������ �ð����� ��ȯ�ϱ� ������ �Ը� ũ�� ���� ������ ����.
		srand(GetTickCount());
	}
	~RandomFunction() {}

	HRESULT init() { return S_OK; }

	inline int getInt(int num)
	{
		return rand() % num;
	}

	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}

	inline float getFloat(void) //float�� ������ �о ���� inlineȭ�� �� �Ǳ� �Ѵ�. ���ϼ��� ���� �����.
	{
		return (float)rand() / (float)RAND_MAX;
	}

	inline float getFloat(float num)
	{
		return (float)rand() / (float)RAND_MAX * num;
	}

	float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd * (toNum - fromNum) + fromNum);
	}

};