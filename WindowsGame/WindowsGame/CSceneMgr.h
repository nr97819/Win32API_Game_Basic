#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr)
private:
	// ���� ������ Scene���� ���� �迭 (Scene* ���·� ��´�)
	CScene*			m_arrScene[(UINT)SCENE_TYPE::END];
	CScene*			m_pCurScene; // ���� Scene

public:
	void Init();
};

