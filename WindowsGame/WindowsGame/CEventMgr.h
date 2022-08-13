#pragma once

struct tEvent
{
	EVENT_TYPE		eEvent;
	DWORD_PTR		lParam; // �̺�Ʈ ���� �߰� �������� ��´�.
	DWORD_PTR		wParam; // �̺�Ʈ ���� �߰� �������� ��´�.
	// DWORD_PTR : x32, x64 ȯ�濡 ���� ������ �ּ� 4����Ʈ 8����Ʈ �����ش�. (#��ó��)
};

class CEventMgr
{
	SINGLE(CEventMgr)
private:
	// ���� event���� ��� vector
	vector<tEvent> m_vecEvent;

	// dead ���°� �� Object���� ��� �� vector
	vector<CObject*> m_vecDead;

public:
	void Update();

private:
	void Execute(const tEvent& _eve);

public:
	void AddEvent(const tEvent& _eve) { m_vecEvent.push_back(_eve); }

};

