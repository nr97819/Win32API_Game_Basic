#include "pch.h"
#include "CScene_Tool.h"

#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CCore.h"
#include "CResMgr.h"

#include "CTile.h"
#include "CTexture.h"
#include "CScene.h"
#include "CUI.h"

#include "resource.h" // Dialog�� ID ���� �̿��ϱ� ����


CScene_Tool::CScene_Tool()
{

}

CScene_Tool::~CScene_Tool()
{

}

void CScene_Tool::Enter()
{
	// �ػ�
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	// �ؽ�ó �ε�
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\tile\\test.bmp");

	// Tool Scene ���� ��, (N x N) ���·� Ÿ�ϵ� ����
	// (�θ��� Scene�� �����Ǿ� �ִ� �Լ�)
	CreateTile(5, 5);
	

	/********************/
	/*		UI ����		*/
	/********************/
	CUI* pUI = new CUI(false);
	pUI->SetScale(Vec2(500.f, 300.f));
	pUI->SetPos(Vec2(vResolution.x - pUI->GetScale().x, 0.f));

	//CUI* pChildUI = new CUI();
	//pChildUI->SetScale(Vec2(100.f, 40.f));
	//pChildUI->SetPos(Vec2(0.f, 0.f)); // �θ� UI�κ����� ������� Pos

	//pUI->AddChild(pChildUI);

	AddObject(pUI, GROUP_TYPE::UI);


	/************************/
	/*		Camera ����		*/
	/************************/
	// Camera�� �ʱ� LookAt ����
	CCamera::GetInst()->SetLookAt(vResolution / 2.f); // �ػ��� ���߾��� default�� �ٶ󺸰� ���� (�⺻ ����)
}

void CScene_Tool::Exit()
{

}

void CScene_Tool::Update()
{
	// �θ� Ŭ���� (CScene) ���� ����Լ��� ȣ��
	CScene::Update(); // ������ ���

	SetTileIdx();

	//// Enter Ű�� ������, Tool ������ ��ȯ (�̵�)
	//if (KEY_TAP(KEY::ENTER))
	//{
	//	// Event�� �̺�Ʈ�� ����ϴ� "���� �Լ�"�� ȣ��
	//	ChangeScene(SCENE_TYPE::START);
	//}
}

void CScene_Tool::SetTileIdx()
{
	// ���콺 ��Ŭ�� �� ���,
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = MOUSE_POS;

		// MousePos�� ī�޶� ��ǥ (renderPos)�̹Ƿ�, ���� ��ǥ (realPos)�� ��ȯ����� �Ѵ�.
		// (���� Tile�� ��ġ�� ���ؾ� �ϹǷ�)
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		int iTileX = GetTileX();
		int iTileY = GetTileY();

		// ���콺 ��ǥ�� ������ �� �� �����Ƿ� int�� ����
		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		// [���� ó��]
		// �� [����] ����ó���� MousePos�� �ߴ��� ����غ��� (���� ����)
		if (vMousePos.x < 0.f || iTileX <= iCol ||
			vMousePos.y < 0.f || iTileY <= iRow)
		{
			return;
		}

		UINT iIdx = iRow * (iTileX) + iCol;

		// ���� iRow, iCol ������ ����, Tile �׷쿡�� �ش� idx�� ���� Tile�� �����´�.
		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

		// img index 1 ���ϱ� (Test)
		((CTile*)vecTile[iIdx])->IncreaseImgIdx();
	}
}

/************************************/
/*		 Dialog ���ν��� ������		*/
/************************************/
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			// Dialog�� input�� ���, ���ڿ��� �⺻��������, GetDlogItemInt�� Int�� �ٲ��� ��
			// (Text ������ ���� �ִ�.)
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);
			

			/************************************/
			/*		 Tool Scene ��� �̿�		*/
			/************************************/
			// Scene_Tool ���� ������ ���� [���ν���] ���� �Լ��̹Ƿ�, 
			//  SceneMgr�� ���� Scene�� ���� �����;� �Ѵ�.
			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

			// Tool Scene������ ������ ����̹Ƿ�, Tool Scene�� �´��� ����(Ȯ��)
			// dynamic_cast�� ����ȯ�� �Ұ����ϸ� nullptr�� ��ȯ�ϹǷ�,
			//  Tool Scene�� �ƴϾ��ٸ�, nullptr�� ��ȯ�Ǿ ����ó���� �� ����
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			// �� Tile�� ��� ��, ���� Tile ��� ���� (Group�� �����ؼ� ����� �Լ� ȣ��)
			pToolScene->DeletGroup(GROUP_TYPE::TILE);

			// �� Tile�� ���. (Scene�� �ִ� �Լ� ȣ��)
			pToolScene->CreateTile(iXCount, iYCount);


			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}