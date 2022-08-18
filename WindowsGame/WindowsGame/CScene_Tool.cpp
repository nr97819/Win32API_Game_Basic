#include "pch.h"
#include "CScene_Tool.h"

#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CCore.h"
#include "CResMgr.h"

#include "CTile.h"
#include "CTexture.h"


CScene_Tool::CScene_Tool()
{

}

CScene_Tool::~CScene_Tool()
{

}

void CScene_Tool::Enter()
{
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\tile\\test.bmp");

	// Tool Scene ���� ��, (N x N) ���·� Ÿ�ϵ� ����
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			CTile* pTile = new CTile();

			pTile->SetPos(Vec2((float)(j * TILE_SIZE), (float)(i * TILE_SIZE)));
			pTile->SetTexture(pTex); // �ش� tile �ؽ��ĸ� ����

			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
	
	/************************/
	/*		Camera ����		*/
	/************************/
	// Camera�� �ʱ� LookAt ����
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CCamera::GetInst()->SetLookAt(vResolution / 2.f); // �ػ��� ���߾��� default�� �ٶ󺸰� ���� (�⺻ ����)
}

void CScene_Tool::Exit()
{

}

void CScene_Tool::Update()
{
	// �θ� Ŭ���� (CScene) ���� ����Լ��� ȣ��
	//CScene::Update(); // ������ ���

	//// Enter Ű�� ������, Tool ������ ��ȯ (�̵�)
	//if (KEY_TAP(KEY::ENTER))
	//{
	//	// Event�� �̺�Ʈ�� ����ϴ� "���� �Լ�"�� ȣ��
	//	ChangeScene(SCENE_TYPE::START);
	//}
}