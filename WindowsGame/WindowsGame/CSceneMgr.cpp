#include "pch.h"
#include "CSceneMgr.h"

#include "CScene_Start.h"

CSceneMgr::CSceneMgr()
	: m_arrScene{}
	, m_pCurScene(nullptr)
{

}

CSceneMgr::~CSceneMgr()
{
	// Scene 전부 삭제 (부모 객체 virtual 키워드 소멸자 필수)
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
	// 모든 Scene 생성
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start();
	//m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool();
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Stage_01();
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Stage_02();

	// 현재 Scene 지정
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
}