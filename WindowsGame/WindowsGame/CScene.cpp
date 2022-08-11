#include "pch.h"
#include "CScene.h"

#include "CObject.h"

CScene::CScene()
{

}

CScene::~CScene() // �� ���⼭ �ϰ� delete�ϴ��� ���� �˰� �Ѿ�� !!
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j) // iterator ��� �� �� ���� �˰� �Ѿ�� !!
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
		for (size_t j = 0; j < m_arrObj[i].size(); ++j) // iterator ��� �� �� ���� �˰� �Ѿ�� !!
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
		for (size_t j = 0; j < m_arrObj[i].size(); ++j) // iterator ��� �� �� ���� �˰� �Ѿ�� !!
		{
			if (nullptr != m_arrObj[i][j])
			{
				m_arrObj[i][j]->FinalUpdate(); // ��� object�� finalupdate �״�� ȣ���Ŵ
			}
		}
	}
}

void CScene::Render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j) // iterator ��� �� �� ���� �˰� �Ѿ�� !!
		{
			if (nullptr != m_arrObj[i][j])
			{
				m_arrObj[i][j]->Render(_dc);
			}
		}
	}
}
