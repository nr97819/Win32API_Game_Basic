#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr)
private:
	// 여러 종류의 Scene들을 담을 배열 (Scene* 형태로 담는다)
	CScene*			m_arrScene[(UINT)SCENE_TYPE::END];
	CScene*			m_pCurScene; // 현재 Scene

public:
	void Init();
	void Update();
	void Render(HDC _dc);
};

