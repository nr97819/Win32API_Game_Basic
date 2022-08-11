#pragma once

class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	// Frame Per a Secound (FPS)
	// = (1 / Delta Time)

	// Time Per a Frame (Delta Time)
	// = (1 / FPS)

	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llFrequency;

	double			m_dDT; // 프레임 당(간) 걸린 시간
	double			m_FPS; // (1 / m_dDT)
	double			m_dAcc; // 1초 체크를 위한 누적 시간
	UINT			m_iCallCount;
	UINT			m_iFPS;

public:
	void Init();
	void Update();
	void Render();

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};