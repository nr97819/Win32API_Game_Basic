#include "pch.h"
#include "CAnimator.h"


CAnimator::CAnimator()
	: m_pOwner(nullptr)
{
}

CAnimator::~CAnimator()
{
	// map이 보유하던 animation (second 원소)들을 안전하게 모두 delete 해주는 전역함수 이용
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
