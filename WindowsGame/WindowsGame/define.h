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

#define CLONE(type) type* Clone() { return new type(*this); }


#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)

#define PI 3.1415926535f


enum class GROUP_TYPE
{
	DEFAULT, // 0 부터 시작

	PLAYER,
	MONSTER,

	PROJ_PLAYER,
	PROJ_MONSTER,

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

enum class BRUSH_TYPE
{
	HOLLOW,

	END
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,

	END
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,

	SCENE_CHANGE,

	END
};