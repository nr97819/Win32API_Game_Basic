#include "pch.h"
#include "CTimeMgr.h"

#include <wchar.h>
#include "CCore.h"

CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llFrequency{}
	, m_dDT(0.)
	, m_FPS(0.)
	, m_dAcc(0.)
	, m_iCallCount(0)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::Init()
{
	// ���� ī��Ʈ
	QueryPerformanceCounter(&m_llPrevCount);

	// �ʴ� ī��Ʈ Ƚ�� (10,000,000)
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);

	// DeltaTime ���� ���Ѵ�. (1������ �� �ɸ��� �ð�)
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart)
		/ (double)m_llFrequency.QuadPart; // QuadPart�� ���� longlong���� ����ִ�.

	// PrevCount�� �ֽ� ������ ����
	m_llPrevCount = m_llCurCount;

	++m_iCallCount;
	// deltaTime�� ������Ű��, ������� �帥 �� �帥 �ð��� �ȴ�.
	m_dAcc += m_dDT;
}

void CTimeMgr::Render()
{
	if (m_dAcc >= 1.)
	{
		// �ʴ� ������ Ƚ�� ����
		m_iFPS = m_iCallCount;

		// Windows â bar�� ���
		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %lf", m_iFPS, m_dDT);
		
		// â ��ܿ� ���
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);

		// ���� 0���� �ٽ� �ʱ�ȭ
		m_dAcc = 0.;
		m_iCallCount = 0;
	}
	// m_FPS = 1. / m_dDT;
}
