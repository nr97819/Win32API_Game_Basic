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

	// Tool Scene 진입 시, (N x N) 형태로 타일들 생성
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			CTile* pTile = new CTile();

			pTile->SetPos(Vec2((float)(j * TILE_SIZE), (float)(i * TILE_SIZE)));
			pTile->SetTexture(pTex); // 해당 tile 텍스쳐를 지정

			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
	
	/************************/
	/*		Camera 설정		*/
	/************************/
	// Camera의 초기 LookAt 설정
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CCamera::GetInst()->SetLookAt(vResolution / 2.f); // 해상도의 정중앙을 default로 바라보게 설정 (기본 설정)
}

void CScene_Tool::Exit()
{

}

void CScene_Tool::Update()
{
	// 부모 클래스 (CScene) 쪽의 멤버함수를 호출
	//CScene::Update(); // 유용한 기술

	//// Enter 키가 눌리면, Tool 씬으로 전환 (이동)
	//if (KEY_TAP(KEY::ENTER))
	//{
	//	// Event에 이벤트를 등록하는 "전역 함수"를 호출
	//	ChangeScene(SCENE_TYPE::START);
	//}
}