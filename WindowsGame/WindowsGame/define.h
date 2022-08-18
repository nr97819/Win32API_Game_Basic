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
#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos()

#define PI 3.1415926535f

#define TILE_SIZE 64 // sprite에 따라서 다를 수 있다.


enum class GROUP_TYPE
{
	DEFAULT = 0,
	TILE = 1,		// (*) render 시, Tile은 가장 바닥에 그려져야 하므로,

	PLAYER,
	MONSTER,

	PROJ_PLAYER,
	PROJ_MONSTER,

	UI = 31,		// (*) render 시, UI는 가장 위에 그려져야 하므로,
	END = 32		// 최대 32개 그룹 고정
};

enum class SCENE_TYPE
{
	TOOL,
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