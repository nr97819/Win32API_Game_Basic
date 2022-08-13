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
	*		Dead ������Ʈ ��� delete		*
	*************************************/
	// Event Manager ��ü�� CCore::Update()�� ���帶���� ������ ȣ��ǹǷ�,
	//  �� �������� Object�� delete�ϰ� �Ǹ�, �ٷ� �������� �ʰ�, 
	//   1 �������� �߰��� dead ���·� �����ϰ� �ȴ�.
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
		m_vecDead[i] = nullptr;
	}
	m_vecDead.clear();

	/************************************************
	*		�̹� �����ӿ� ���� ��� �̺�Ʈ ó��		*
	*************************************************/
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Execute(m_vecEvent[i]);
	}

	// �̺�Ʈ ���� ����
	m_vecEvent.clear();
}

void CEventMgr::Execute(const tEvent& _eve)
{
	switch (_eve.eEvent)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : �߰��� Object Address (CObject*)
		// wParam : �߰��� Group Type (enum)

		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
	break;
	
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam : ������ Object Address (CObject*)
		// wParam : �̻��

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
