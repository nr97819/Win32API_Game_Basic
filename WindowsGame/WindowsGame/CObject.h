#pragma once

// 모든 Object들의 부모 역할 (사용될 목적 X)
class CObject
{
private:
	Vec2 m_vPos;
	Vec2 m_vScale;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; };
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; };

	Vec2 GetPos() { return m_vPos; };
	Vec2 GetScale() { return m_vScale; };

public:
	CObject();
	virtual ~CObject();
};

