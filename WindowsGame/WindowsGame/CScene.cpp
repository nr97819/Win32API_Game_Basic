#include "pch.h"
#include "CScene.h"

#include "CObject.h"

CScene::CScene()
{

}

CScene::~CScene() // 왜 여기서 일괄 delete하는지 이유 알고 넘어가기 !!
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j) // iterator 사용 안 한 이유 알고 넘어가기 !!
		{
			if (nullptr != m_arrObj[i][j])
			{
				delete m_arrObj[i][j];
				m_arrObj[i][j] = nullptr;
			}
		}
	}
}

void CScene::Update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j) // iterator 사용 안 한 이유 알고 넘어가기 !!
		{
			if (nullptr != m_arrObj[i][j])
			{
				m_arrObj[i][j]->Update();
			}
		}
	}
}

void CScene::FinalUpdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j) // iterator 사용 안 한 이유 알고 넘어가기 !!
		{
			if (nullptr != m_arrObj[i][j])
			{
				m_arrObj[i][j]->FinalUpdate(); // 모든 object에 finalupdate 그대로 호출시킴
			}
		}
	}
}

void CScene::Render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j) // iterator 사용 안 한 이유 알고 넘어가기 !!
		{
			if (nullptr != m_arrObj[i][j])
			{
				m_arrObj[i][j]->Render(_dc);
			}
		}
	}
}
