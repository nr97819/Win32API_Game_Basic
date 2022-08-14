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
				// Dead 상태가 아닌 오브젝트만 Update()
				if (!m_arrObj[i][j]->IsDead())
				{
					m_arrObj[i][j]->Update();
				}
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

				// Dead 상태인 오브젝트도 FinalUpdate는 적용시키는 이유 ?
				// [이유 1] Dead 상태여도, 보유하고 있는 Component의 최종 좌표는 잡아줘야 하므로, ...
				// (FinalUpdate에서 좌표가 새로고침 되므로,)
				// [이유 2] 삭제된 객체와 충돌하던 Alive 객체에게, 충돌한 객체가 delete되어 없어졌다는 사실을
				// 이 시점에 알려줘야 하기 때문 (RED가 계속해서 점등된 상태인 것 해결)
			}
		}
	}
}

void CScene::Render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		vector<CObject*>::iterator iter = m_arrObj[i].begin();

		for (; iter != m_arrObj[i].end();) // erase()를 하기 위해 iterator 반복문을 사용
		{
			// Dead 상태가 아닌 오브젝트만 Render()
			if (!(*iter)->IsDead())
			{
				(*iter)->Render(_dc);
				
				// erase()한 경우 ++iter을 하면 iter 값이 2번 건너뛰게 되므로, 여기서만 ++iter
				// (erase하면 다음 원소를 자동으로 넘어가게 되므로)
				++iter;
			}
			else 
			{
				// (*WARNING) REMEMBER* that -> erase() func returns next iterator
				iter = m_arrObj[i].erase(iter);
			}
		}
	}
}
