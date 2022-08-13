#pragma once

struct tEvent
{
	EVENT_TYPE		eEvent;
	DWORD_PTR		lParam; // 이벤트 관련 추가 정보들을 담는다.
	DWORD_PTR		wParam; // 이벤트 관련 추가 정보들을 담는다.
	// DWORD_PTR : x32, x64 환경에 따라 포인터 주소 4바이트 8바이트 맞춰준다. (#전처리)
};

class CEventMgr
{
	SINGLE(CEventMgr)
private:
	// 쌓인 event들이 담길 vector
	vector<tEvent> m_vecEvent;

	// dead 상태가 된 Object들을 담아 둘 vector
	vector<CObject*> m_vecDead;

public:
	void Update();

private:
	void Execute(const tEvent& _eve);

public:
	void AddEvent(const tEvent& _eve) { m_vecEvent.push_back(_eve); }

};

