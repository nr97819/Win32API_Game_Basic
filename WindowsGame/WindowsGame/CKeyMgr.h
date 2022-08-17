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
	NONE,	// ����, ���� ��� �ȴ��� ����
	TAP,	// ���� ���� ����
	HOLD,	// ������ Key-Down ���� ����
	AWAY,	// �� Key-Up �� ����
};

struct tKeyInfo
{
	KEY_STATE	estate;		// Ű�� ���°�
	bool		ePrevPush;	// ���� �����ӿ��� Ű�� ���ȴ��� ����
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

