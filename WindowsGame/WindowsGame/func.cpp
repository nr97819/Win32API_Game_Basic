#include "pch.h"
#include "func.h"

#include "CEventMgr.h"


void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evn = {};
	evn.eEvent = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj; // �߰� �� Object�� [�ּ�] ����
	evn.wParam = (DWORD_PTR)_eGroup; // �߰� �� Object�� [�׷� ��] ����
	// ���´� �ٸ�����, ���� ���� � ���·� ����ִ��� ���� �ƴϱ� ���� ����.
	// (���� ����, ����� �ڷ��� ĳ���� �ؼ� �������� �ȴ�.) -> (EventMgr���� ������ �� �°� ĳ����)

	CEventMgr::GetInst()->AddEvent(evn);
}

void DeleteObject(CObject* _pObj)
{
	tEvent evn = {};
	evn.eEvent = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj; // ���� �� Object�� [�ּ�] ����

	CEventMgr::GetInst()->AddEvent(evn);
}

void ChangeScene(SCENE_TYPE _eNext)
{
	tEvent evn = {};
	evn.eEvent = EVENT_TYPE::SCENE_CHANGE;
	evn.lParam = (DWORD_PTR)_eNext; // ������ Scene�� Ÿ���� lParam���� ����

	CEventMgr::GetInst()->AddEvent(evn);
}