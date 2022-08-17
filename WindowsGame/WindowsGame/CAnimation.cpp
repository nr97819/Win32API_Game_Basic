#include "pch.h"
#include "CAnimation.h"

#include "CTimeMgr.h"
#include "CCamera.h"

#include "CAnimator.h"
#include "CTexture.h"
#include "CObject.h"


CAnimation::CAnimation()
	: m_strName{}
	, m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_vecFrm{}
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Update()
{
	// finish 상태라면, 아무것도 하지 않는다.
	if (m_bFinish)
		return;

	m_fAccTime += fDT;
	if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
	{
		++m_iCurFrm;
		
		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = -1;		// 에러 유발
			m_bFinish = true;	// finish 상태로 ON
			m_fAccTime = 0.f;

			return; // vector의 마지막 index + 1 접근 에러 방지용
		}

		// (*주의) 단순히 0.f로 돌리는 것이 아니라, 초과한 만큼 되돌려 주어야 한다.
		// -> 안그러면, 툭툭 끊기는 현상이 발생한다. (버그)
		m_fAccTime = (m_fAccTime - m_vecFrm[m_iCurFrm].fDuration);
		//m_fAccTime = 0.f;
	}
}

void CAnimation::Render(HDC _dc)
{
	// finish 상태라면, 아무것도 하지 않는다.
	if (m_bFinish)
		return;

	// animator -> pOwner을 통해서 소유 Object를 가져온다.
	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();

	// 현재 frame의 info (구조체)
	tAnimFrm curFrmInfo = m_vecFrm[m_iCurFrm];

	// offset 만큼 추가 위치 이동
	vPos += curFrmInfo.vOffset;

	// (*) Camera의 renderPos에 그리도록 수정
	vPos = CCamera::GetInst()->GetRenderPos(vPos);
	
	TransparentBlt(_dc
		, int(vPos.x - (float)(curFrmInfo.vSlice.x / 2.f))
		, int(vPos.y - (float)(curFrmInfo.vSlice.y / 2.f))
		, int(curFrmInfo.vSlice.x)
		, int(curFrmInfo.vSlice.y)
		, m_pTex->GetDC() // 원본 texture (animation->create 할 때, 멤버로 저장해 둠)
		, int(curFrmInfo.vLT.x)
		, int(curFrmInfo.vLT.y)
		, int(curFrmInfo.vSlice.x)
		, int(curFrmInfo.vSlice.y)
		, RGB(255, 0, 255)); // Magenta 색상 필터링
}

void CAnimation::Create(const wstring& _strName, CTexture* _pTex
	, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	// sprite가 순차적인 형태일때만 이렇게 자르기 가능
	tAnimFrm frm = {};
	for (UINT i = 0; i < _iFrameCount; ++i)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT + (_vStep * (int)i);

		m_vecFrm.push_back(frm);
	}
}
