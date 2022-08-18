#include "pch.h"
#include "CScene.h"

#include "CResMgr.h"

#include "CObject.h"
#include "CTile.h"
#include "CTexture.h"


CScene::CScene()
	: m_arrObj{}
	, m_strName{}
	, m_iTileX(0)
	, m_iTileY(0)
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

void CScene::DeletGroup(GROUP_TYPE _eTarget)
{
	// 그룹을 통채로 지우는 작업은 자주 있으므로, 전역 template 함수 만들어두었다.

	Safe_Delete_Vec<CObject*>(m_arrObj[(UINT)_eTarget]);

	// T에 해당하는 <CObject*>는 생략하고 함수처럼 작성해도 되지만,
	// 이렇게 명시적으로 T 까지 꺽새에 넣어주는 것이 권장된다.
	// (생략해도 컴파일러가 알아서 잡아준다.) (함수랑은 개념이 다르다는걸 기억하자.) (그냥 생략한 모습이 함수같은 것 뿐)
}

void CScene::DeleteAll()
{
	// 모든 Group, 즉, 모든 Object들이 삭제된다.

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeletGroup((GROUP_TYPE)i);
	}
}

void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
	CTexture* pTileTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\tile\\test.bmp");

	// 추후 쓰일 예정이므로, Scene에 count 값 기록해두기
	m_iTileX = _iXCount;
	m_iTileY = _iYCount;

	// (N x N) 형태로 타일들 생성
	for (UINT i = 0; i < _iXCount; ++i)
	{
		for (UINT j = 0; j < _iYCount; ++j)
		{
			CTile* pTile = new CTile();

			pTile->SetPos(Vec2((float)(j * TILE_SIZE), (float)(i * TILE_SIZE)));
			pTile->SetTexture(pTileTex); // 해당 tile 텍스쳐를 지정

			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}
