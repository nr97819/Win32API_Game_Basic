#pragma once


class CScene;
class CEventMgr;

class CSceneMgr
{
	SINGLE(CSceneMgr)
private:
	// ���� ������ Scene���� ���� �迭 (Scene* ���·� ��´�)
	CScene*			m_arrScene[(UINT)SCENE_TYPE::END];
	CScene*			m_pCurScene; // ���� Scene

public:
	void Init();
	void Update();
	void Render(HDC _dc);

public:
	CScene* GetCurScene() { return m_pCurScene; }

	// �ƹ����� ȣ���� ������ ���� �ƴ϶�,
	// Event �Ŵ����� ���ؼ��� ȣ���ؾ� �Ǿ����� �ϹǷ� - private ���� (friend class�� ���� Ȯ��)
private:
	void ChangeScene(SCENE_TYPE _eNext);

	friend class CEventMgr;
};

