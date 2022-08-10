#pragma once

#define SINGLE(type)	public:\
							static type* GetInst()\
							{\
								static type obj;\
								return &obj;\
							}\
						private:\
								type();\
								~type();

#define fDT CTimeMgr::GetInst()->GetfDT()
#define DT CTimeMgr::GetInst()->GetDT()


enum class GROUP_TYPE
{
	DEFAULT, // 0 부터 시작

	PLAYER,
	MISSIILE,
	MONSTER,

	END = 32 // 최대 32개 그룹 고정
};

enum class SCENE_TYPE
{
	TOOL, // map_tool 씬
	START,
	STAGE_01,
	STAGE_02,
	
	END
};