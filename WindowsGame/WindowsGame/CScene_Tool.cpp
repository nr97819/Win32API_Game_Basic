#include "pch.h"
#include "CScene_Tool.h"

#include "CKeyMgr.h"
#include "CSceneMgr.h"


CScene_Tool::CScene_Tool()
{

}

CScene_Tool::~CScene_Tool()
{

}

void CScene_Tool::Enter()
{
	// 타일 생성


	

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