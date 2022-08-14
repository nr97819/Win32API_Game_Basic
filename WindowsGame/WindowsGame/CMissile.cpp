#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"
#include "CCollider.h"


CMissile::CMissile()
	: m_fTheta(PI / 4.f)
	, m_vDir(Vec2(1.f, 1.f)) // 45도에 해당하는 Vector값으로 초기화
{
	// [벡터의 정규화] - (루트2를 1로 설정) -> 추후 배수를 적용하기 위함
	// 정규화 공식 이용 (대각선의 길이로 나눈 뒤, 둘을 더한다)
	m_vDir.Normalize();
	// 정규화 함수 -> 직접 구현

	CreateCollider();
	GetCollider()->SetScale(Vec2(15.f, 15.f)); // collider의 범위 조정
}

CMissile::~CMissile()
{
}

void CMissile::Update()
{
	Vec2 vPos = GetPos();

	vPos.x += 600.f * m_vDir.x * fDT;
	vPos.y += 600.f * m_vDir.y * fDT;

	SetPos(vPos);
}

void CMissile::Render(HDC _dc)
{
	// 그리기
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	
	Ellipse(_dc
		, int(vPos.x - vScale.x / 2.f)
		, int(vPos.y - vScale.y / 2.f)
		, int(vPos.x + vScale.x / 2.f)
		, int(vPos.y + vScale.y / 2.f)
	);

	SetPos(vPos);

	// 컴포넌트 render
	component_render(_dc);
}

void CMissile::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Monster")
	{
		// Event Manager에 자신을 삭제하도록 요청 (삭제 이벤트 등록)
		DeleteObject(this);
	}
}