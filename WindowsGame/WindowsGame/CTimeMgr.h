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

	double			m_dDT; // ������ ��(��) �ɸ� �ð�
	double			m_FPS; // (1 / m_dDT)
	double			m_dAcc; // 1�� üũ�� ���� ���� �ð�
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