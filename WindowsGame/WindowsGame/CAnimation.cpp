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
	// finish ���¶��, �ƹ��͵� ���� �ʴ´�.
	if (m_bFinish)
		return;

	m_fAccTime += fDT;
	if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
	{
		++m_iCurFrm;
		
		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = -1;		// ���� ����
			m_bFinish = true;	// finish ���·� ON
			m_fAccTime = 0.f;

			return; // vector�� ������ index + 1 ���� ���� ������
		}

		// (*����) �ܼ��� 0.f�� ������ ���� �ƴ϶�, �ʰ��� ��ŭ �ǵ��� �־�� �Ѵ�.
		// -> �ȱ׷���, ���� ����� ������ �߻��Ѵ�. (����)
		m_fAccTime = (m_fAccTime - m_vecFrm[m_iCurFrm].fDuration);
		//m_fAccTime = 0.f;
	}
}

void CAnimation::Render(HDC _dc)
{
	// finish ���¶��, �ƹ��͵� ���� �ʴ´�.
	if (m_bFinish)
		return;

	// animator -> pOwner�� ���ؼ� ���� Object�� �����´�.
	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();

	// ���� frame�� info (����ü)
	tAnimFrm curFrmInfo = m_vecFrm[m_iCurFrm];

	// offset ��ŭ �߰� ��ġ �̵�
	vPos += curFrmInfo.vOffset;

	// (*) Camera�� renderPos�� �׸����� ����
	vPos = CCamera::GetInst()->GetRenderPos(vPos);
	
	TransparentBlt(_dc
		, int(vPos.x - (float)(curFrmInfo.vSlice.x / 2.f))
		, int(vPos.y - (float)(curFrmInfo.vSlice.y / 2.f))
		, int(curFrmInfo.vSlice.x)
		, int(curFrmInfo.vSlice.y)
		, m_pTex->GetDC() // ���� texture (animation->create �� ��, ����� ������ ��)
		, int(curFrmInfo.vLT.x)
		, int(curFrmInfo.vLT.y)
		, int(curFrmInfo.vSlice.x)
		, int(curFrmInfo.vSlice.y)
		, RGB(255, 0, 255)); // Magenta ���� ���͸�
}

void CAnimation::Create(const wstring& _strName, CTexture* _pTex
	, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	// sprite�� �������� �����϶��� �̷��� �ڸ��� ����
	tAnimFrm frm = {};
	for (UINT i = 0; i < _iFrameCount; ++i)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT + (_vStep * (int)i);

		m_vecFrm.push_back(frm);
	}
}
