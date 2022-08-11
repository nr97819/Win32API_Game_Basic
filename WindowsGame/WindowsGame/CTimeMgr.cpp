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
	// 현재 카운트
	QueryPerformanceCounter(&m_llPrevCount);

	// 초당 카운트 횟수 (10,000,000)
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);

	// DeltaTime 값을 구한다. (1프레임 당 걸리는 시간)
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart)
		/ (double)m_llFrequency.QuadPart; // QuadPart에 실제 longlong값이 들어있다.

	// PrevCount를 최신 값으로 갱신
	m_llPrevCount = m_llCurCount;

	++m_iCallCount;
	// deltaTime을 누적시키면, 현재까지 흐른 총 흐른 시간이 된다.
	m_dAcc += m_dDT;
}

void CTimeMgr::Render()
{
	if (m_dAcc >= 1.)
	{
		// 초당 프레임 횟수 갱신
		m_iFPS = m_iCallCount;

		// Windows 창 bar에 출력
		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %lf", m_iFPS, m_dDT);
		
		// 창 상단에 출력
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);

		// 값들 0으로 다시 초기화
		m_dAcc = 0.;
		m_iCallCount = 0;
	}
	// m_FPS = 1. / m_dDT;
}
