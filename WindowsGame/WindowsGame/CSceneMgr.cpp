#include "pch.h"
#include "CSceneMgr.h"

#include "CScene_Start.h"
#include "CScene_Tool.h"

#include "CEventMgr.h"


CSceneMgr::CSceneMgr()
	: m_arrScene{}
	, m_pCurScene(nullptr)
{
}

CSceneMgr::~CSceneMgr()
{
	// Scene ���� ���� (�θ� ��ü virtual Ű���� �Ҹ��� �ʼ�)
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
			m_arrScene[i] = nullptr;
		}
	}
}

void CSceneMgr::Init()
{
	// ��� Scene ����
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start();
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool();
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Tool Scene");


	//m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Stage_01();
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Stage_02();

	// ���� Scene ����
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_pCurScene->Enter(); // Scene�� ����
}

void CSceneMgr::Update()
{
	// ���� Scene�� Update
	m_pCurScene->Update();

	// �ʿ��� �۾��� ������ ���ִ� update (������Ʈ ������ update)
	m_pCurScene->FinalUpdate();
}

void CSceneMgr::Render(HDC _dc)
{
	// ���� Scene�� Render
	m_pCurScene->Render(_dc); // memDC�� �޾Ƽ� ����
}

void CSceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	// ���� Scene Ż��
	m_pCurScene->Exit();

	m_pCurScene = m_arrScene[(UINT)_eNext];

	// �� Scene ����
	m_pCurScene->Enter();
}
