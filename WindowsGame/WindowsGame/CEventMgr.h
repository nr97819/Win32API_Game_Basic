#pragma once

struct tEvent
{
	EVENT_TYPE	eEvent;
	DWORD		lParam; // �̺�Ʈ ���� �߰� �������� ��´�.
	DWORD		wParam; // �̺�Ʈ ���� �߰� �������� ��´�.
};

class CEventMgr
{
	SINGLE(CEventMgr)
private:
	vector<tEvent> m_vecEvent;

public:
	void Update();

};

