#include "pch.h"
#include "CAnimator.h"


CAnimator::CAnimator()
	: m_pOwner(nullptr)
{
}

CAnimator::~CAnimator()
{
	// map�� �����ϴ� animation (second ����)���� �����ϰ� ��� delete ���ִ� �����Լ� �̿�
	Safe_Delete_Map(m_mapAnim);
}

void CAnimator::CreateAnimation()
{
}

void CAnimator::FindAnimation()
{
}

void CAnimator::Play()
{
}
