#include "pch.h"
#include "func.h"

#include "CEventMgr.h"


void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evn = {};
	evn.eEvent = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj; // �߰��� Object�� [�ּ�] ����
	evn.wParam = (DWORD_PTR)_eGroup; // �߰��� Object�� [�׷� ��] ����
	// ���´� �ٸ�����, ���� ���� � ���·� ����ִ��� ���� �ƴϱ� ���� ����.
	// (���� ����, ����� �ڷ��� ĳ���� �ؼ� �������� �ȴ�.) -> (EventMgr���� ������ �� �°� ĳ����)

	CEventMgr::GetInst()->AddEvent(evn);
}
