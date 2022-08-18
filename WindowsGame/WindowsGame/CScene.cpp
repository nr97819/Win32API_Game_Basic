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
				// Dead ���°� �ƴ� ������Ʈ�� Update()
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
		for (size_t j = 0; j < m_arrObj[i].size(); ++j) // iterator ��� �� �� ���� �˰� �Ѿ�� !!
		{
			if (nullptr != m_arrObj[i][j])
			{
				m_arrObj[i][j]->FinalUpdate(); // ��� object�� finalupdate �״�� ȣ���Ŵ

				// Dead ������ ������Ʈ�� FinalUpdate�� �����Ű�� ���� ?
				// [���� 1] Dead ���¿���, �����ϰ� �ִ� Component�� ���� ��ǥ�� ������ �ϹǷ�, ...
				// (FinalUpdate���� ��ǥ�� ���ΰ�ħ �ǹǷ�,)
				// [���� 2] ������ ��ü�� �浹�ϴ� Alive ��ü����, �浹�� ��ü�� delete�Ǿ� �������ٴ� �����
				// �� ������ �˷���� �ϱ� ���� (RED�� ����ؼ� ����� ������ �� �ذ�)
			}
		}
	}
}

void CScene::Render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		vector<CObject*>::iterator iter = m_arrObj[i].begin();

		for (; iter != m_arrObj[i].end();) // erase()�� �ϱ� ���� iterator �ݺ����� ���
		{
			// Dead ���°� �ƴ� ������Ʈ�� Render()
			if (!(*iter)->IsDead())
			{
				(*iter)->Render(_dc);

				// erase()�� ��� ++iter�� �ϸ� iter ���� 2�� �ǳʶٰ� �ǹǷ�, ���⼭�� ++iter
				// (erase�ϸ� ���� ���Ҹ� �ڵ����� �Ѿ�� �ǹǷ�)
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
	// �׷��� ��ä�� ����� �۾��� ���� �����Ƿ�, ���� template �Լ� �����ξ���.

	Safe_Delete_Vec<CObject*>(m_arrObj[(UINT)_eTarget]);

	// T�� �ش��ϴ� <CObject*>�� �����ϰ� �Լ�ó�� �ۼ��ص� ������,
	// �̷��� ��������� T ���� ������ �־��ִ� ���� ����ȴ�.
	// (�����ص� �����Ϸ��� �˾Ƽ� ����ش�.) (�Լ����� ������ �ٸ��ٴ°� �������.) (�׳� ������ ����� �Լ����� �� ��)
}

void CScene::DeleteAll()
{
	// ��� Group, ��, ��� Object���� �����ȴ�.

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeletGroup((GROUP_TYPE)i);
	}
}

void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
	CTexture* pTileTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\tile\\test.bmp");

	// ���� ���� �����̹Ƿ�, Scene�� count �� ����صα�
	m_iTileX = _iXCount;
	m_iTileY = _iYCount;

	// (N x N) ���·� Ÿ�ϵ� ����
	for (UINT i = 0; i < _iXCount; ++i)
	{
		for (UINT j = 0; j < _iYCount; ++j)
		{
			CTile* pTile = new CTile();

			pTile->SetPos(Vec2((float)(j * TILE_SIZE), (float)(i * TILE_SIZE)));
			pTile->SetTexture(pTileTex); // �ش� tile �ؽ��ĸ� ����

			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}
