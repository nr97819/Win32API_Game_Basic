#include "pch.h"
#include "CAnimator.h"

#include "CAnimation.h"


CAnimator::CAnimator()
	: m_mapAnim{}
	, m_pCurAnim(nullptr)
	, m_pOwner(nullptr)
	, m_bRepeat(false)
{
}

CAnimator::~CAnimator()
{
	// map이 보유하던 animation (second 원소)들을 안전하게 모두 delete 해주는 전역함수 이용
	Safe_Delete_Map(m_mapAnim);
}

void CAnimator::Update()
{
	
}

void CAnimator::FinalUpdate()
{
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->Update();

		if (true == m_bRepeat &&		// C++ 코드의 최적화를 생각해서 bool 체크를 앞에 배치
			m_pCurAnim->IsFinish())
		{
			m_pCurAnim->SetFrame(0);	// 해당 index로 프레임 설정
		}
	}
}

void CAnimator::Render(HDC _dc)
{
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->Render(_dc);
	}
}

void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pTex
							, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	CAnimation* pAnim = FindAnimation(_strName);
	assert(nullptr == pAnim); // 중복 이름을 입력했다면, assert로 예외 처리

	// 새  animation 생성
	pAnim = new CAnimation();

	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;	// animation도 자신의 animator(실행자)를 알아야 한다.
	pAnim->Create(_strName, _pTex, _vLT, _vSliceSize, _vStep, _fDuration, _iFrameCount);

	m_mapAnim.insert(make_pair(_strName, pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);

	// 같은 이름을 가진 animation이 없다면 nullptr 반환
	if (iter == m_mapAnim.end())
		return nullptr;

	// 이미 존재한다면, 해당 iter 반환
	return iter->second;
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim = FindAnimation(_strName);
	
	m_bRepeat = _bRepeat;
}
