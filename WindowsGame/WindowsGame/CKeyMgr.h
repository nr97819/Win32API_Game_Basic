#pragma once

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,

	Q, W, E, R, T,
	Y, U, I, O, P,
	A, S, D, F, G,
	Z, X, C, V, B,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LBTN,
	RBTN,

	LAST
};

enum class KEY_STATE
{
	NONE,	// 현재, 이전 모두 안눌린 상태
	TAP,	// 누른 직후 시점
	HOLD,	// 누르고 Key-Down 누른 시점
	AWAY,	// 막 Key-Up 뗀 시점
};

struct tKeyInfo
{
	KEY_STATE	estate;		// 키의 상태값
	bool		ePrevPush;	// 이전 프레임에서 키가 눌렸는지 여부
};

class CKeyMgr
{
	SINGLE(CKeyMgr);
private:
	vector<tKeyInfo>	m_vecKey;
	Vec2				m_vCurMousePos;

public:
	void Init();
	void Update();

public:
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].estate; }
	Vec2 GetMousePos() { return m_vCurMousePos; }
};

