#include "pch.h"
#include "func.h"

#include "CEventMgr.h"


void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evn = {};
	evn.eEvent = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj; // 추가 할 Object의 [주소] 전달
	evn.wParam = (DWORD_PTR)_eGroup; // 추가 할 Object의 [그룹 값] 전달
	// 형태는 다르지만, 무슨 값이 어떤 형태로 들어있는지 나는 아니까 문제 없다.
	// (읽을 때만, 제대로 자료형 캐스팅 해서 가져오면 된다.) -> (EventMgr에서 가져올 때 맞게 캐스팅)

	CEventMgr::GetInst()->AddEvent(evn);
}

void DeleteObject(CObject* _pObj)
{
	tEvent evn = {};
	evn.eEvent = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj; // 삭제 할 Object의 [주소] 전달

	CEventMgr::GetInst()->AddEvent(evn);
}

void ChangeScene(SCENE_TYPE _eNext)
{
	tEvent evn = {};
	evn.eEvent = EVENT_TYPE::SCENE_CHANGE;
	evn.lParam = (DWORD_PTR)_eNext; // 변경할 Scene의 타입을 lParam으로 전달

	CEventMgr::GetInst()->AddEvent(evn);
}