#pragma once

struct tEvent
{
	EVENT_TYPE	eEvent;
	DWORD		lParam; // 이벤트 관련 추가 정보들을 담는다.
	DWORD		wParam; // 이벤트 관련 추가 정보들을 담는다.
};

class CEventMgr
{
	SINGLE(CEventMgr)
private:
	vector<tEvent> m_vecEvent;

public:
	void Update();

};

