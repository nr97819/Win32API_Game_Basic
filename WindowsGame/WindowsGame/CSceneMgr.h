#pragma once


class CScene;
class CEventMgr;

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

public:
	CScene* GetCurScene() { return m_pCurScene; }

	// 아무때나 호출이 가능한 것이 아니라,
	// Event 매니저를 통해서만 호출해야 되어져야 하므로 - private 설정 (friend class도 설정 확인)
private:
	void ChangeScene(SCENE_TYPE _eNext);

	friend class CEventMgr;
};

