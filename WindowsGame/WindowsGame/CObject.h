#pragma once


class CCollider;

// 모든 Object들의 부모 역할 (사용될 목적 X)
class CObject
{
private:
	Vec2 m_vPos;
	Vec2 m_vScale;

	CCollider* m_pCollider;


public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; };
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; };

	Vec2 GetPos() { return m_vPos; };
	Vec2 GetScale() { return m_vScale; };

	void CreateCollider();


public:
	virtual void Update() = 0;
	virtual void finalupdate() final; // 오버라이딩 방지
	virtual void Render(HDC _dc);

public:
	CObject();
	virtual ~CObject();
};

