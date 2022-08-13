#include "pch.h"
#include "CEventMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CObject.h"


CEventMgr::CEventMgr()
	: m_vecEvent{}
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::Update()
{
	/************************************
	*		Dead 오브젝트 모두 delete		*
	*************************************/
	// Event Manager 자체가 CCore::Update()의 가장마지막 시점에 호출되므로,
	//  이 시점에서 Object를 delete하게 되면, 바로 지워지지 않고, 
	//   1 프레임을 추가로 dead 상태로 존재하게 된다.
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
		m_vecDead[i] = nullptr;
	}
	m_vecDead.clear();

	/************************************************
	*		이번 프레임에 쌓인 모든 이벤트 처리		*
	*************************************************/
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Execute(m_vecEvent[i]);
	}

	// 이벤트 버퍼 비우기
	m_vecEvent.clear();
}

void CEventMgr::Execute(const tEvent& _eve)
{
	switch (_eve.eEvent)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : 추가될 Object Address (CObject*)
		// wParam : 추가될 Group Type (enum)

		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
	break;
	
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam : 삭제될 Object Address (CObject*)
		// wParam : 미사용

		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
	break;
	
	case EVENT_TYPE::SCENE_CHANGE:
	{

	}
	break;

	default: break;
	}

}
