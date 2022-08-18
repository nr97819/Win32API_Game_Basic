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

#include "resource.h" // Dialog의 ID 값을 이용하기 위함


CScene_Tool::CScene_Tool()
{

}

CScene_Tool::~CScene_Tool()
{

}

void CScene_Tool::Enter()
{
	// 해상도
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	// 텍스처 로드
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\tile\\test.bmp");

	// Tool Scene 진입 시, (N x N) 형태로 타일들 생성
	// (부모인 Scene에 구현되어 있는 함수)
	CreateTile(5, 5);
	

	/********************/
	/*		UI 생성		*/
	/********************/
	CUI* pUI = new CUI(false);
	pUI->SetScale(Vec2(500.f, 300.f));
	pUI->SetPos(Vec2(vResolution.x - pUI->GetScale().x, 0.f));

	//CUI* pChildUI = new CUI();
	//pChildUI->SetScale(Vec2(100.f, 40.f));
	//pChildUI->SetPos(Vec2(0.f, 0.f)); // 부모 UI로부터의 상대적인 Pos

	//pUI->AddChild(pChildUI);

	AddObject(pUI, GROUP_TYPE::UI);


	/************************/
	/*		Camera 설정		*/
	/************************/
	// Camera의 초기 LookAt 설정
	CCamera::GetInst()->SetLookAt(vResolution / 2.f); // 해상도의 정중앙을 default로 바라보게 설정 (기본 설정)
}

void CScene_Tool::Exit()
{

}

void CScene_Tool::Update()
{
	// 부모 클래스 (CScene) 쪽의 멤버함수를 호출
	CScene::Update(); // 유용한 기술

	SetTileIdx();

	//// Enter 키가 눌리면, Tool 씬으로 전환 (이동)
	//if (KEY_TAP(KEY::ENTER))
	//{
	//	// Event에 이벤트를 등록하는 "전역 함수"를 호출
	//	ChangeScene(SCENE_TYPE::START);
	//}
}

void CScene_Tool::SetTileIdx()
{
	// 마우스 좌클릭 한 경우,
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = MOUSE_POS;

		// MousePos는 카메라 좌표 (renderPos)이므로, 실제 좌표 (realPos)로 변환해줘야 한다.
		// (실제 Tile의 위치와 비교해야 하므로)
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		int iTileX = GetTileX();
		int iTileY = GetTileY();

		// 마우스 좌표가 음수가 될 수 있으므로 int로 변경
		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		// [예외 처리]
		// 왜 [음수] 예외처리만 MousePos로 했는지 고민해보기 (정답 있음)
		if (vMousePos.x < 0.f || iTileX <= iCol ||
			vMousePos.y < 0.f || iTileY <= iRow)
		{
			return;
		}

		UINT iIdx = iRow * (iTileX) + iCol;

		// 구한 iRow, iCol 정보를 통해, Tile 그룹에서 해당 idx를 가진 Tile을 가져온다.
		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

		// img index 1 더하기 (Test)
		((CTile*)vecTile[iIdx])->IncreaseImgIdx();
	}
}

/************************************/
/*		 Dialog 프로시저 구현부		*/
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
			// Dialog의 input의 경우, 문자열이 기본형이지만, GetDlogItemInt가 Int로 바꿔준 것
			// (Text 버전도 따로 있다.)
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);
			

			/************************************/
			/*		 Tool Scene 기능 이용		*/
			/************************************/
			// Scene_Tool 과는 관련이 없는 [프로시저] 전역 함수이므로, 
			//  SceneMgr을 통해 Scene을 먼저 가져와야 한다.
			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

			// Tool Scene에서만 가능한 기능이므로, Tool Scene이 맞는지 검증(확인)
			// dynamic_cast는 형변환이 불가능하면 nullptr를 반환하므로,
			//  Tool Scene이 아니었다면, nullptr가 반환되어서 예외처리가 될 예정
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			// 새 Tile을 깔기 전, 기존 Tile 모두 제거 (Group을 지정해서 지우는 함수 호출)
			pToolScene->DeletGroup(GROUP_TYPE::TILE);

			// 새 Tile을 깐다. (Scene에 있는 함수 호출)
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