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
	// map�� �����ϴ� animation (second ����)���� �����ϰ� ��� delete ���ִ� �����Լ� �̿�
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

		if (true == m_bRepeat &&		// C++ �ڵ��� ����ȭ�� �����ؼ� bool üũ�� �տ� ��ġ
			m_pCurAnim->IsFinish())
		{
			m_pCurAnim->SetFrame(0);	// �ش� index�� ������ ����
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
	assert(nullptr == pAnim); // �ߺ� �̸��� �Է��ߴٸ�, assert�� ���� ó��

	// ��  animation ����
	pAnim = new CAnimation();

	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;	// animation�� �ڽ��� animator(������)�� �˾ƾ� �Ѵ�.
	pAnim->Create(_strName, _pTex, _vLT, _vSliceSize, _vStep, _fDuration, _iFrameCount);

	m_mapAnim.insert(make_pair(_strName, pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);

	// ���� �̸��� ���� animation�� ���ٸ� nullptr ��ȯ
	if (iter == m_mapAnim.end())
		return nullptr;

	// �̹� �����Ѵٸ�, �ش� iter ��ȯ
	return iter->second;
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim = FindAnimation(_strName);
	
	m_bRepeat = _bRepeat;
}
