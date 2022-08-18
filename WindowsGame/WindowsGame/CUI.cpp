#include "CUI.h"


CUI::CUI()
	: m_vecChildUI{}
	, m_pParentUI(nullptr)
	, m_vFinalPos{}
{
}

CUI::~CUI()
{
	// 부모 UI가 소멸될 때, 자식 UI들을 계층적으로 모두 지워준다.
	Safe_Delete_Vec(m_vecChildUI);
}

void CUI::Update()
{
	/* [계층 구조] */


	// 자식 Update
	update_child();
}

void CUI::FinalUpdate()
{
	/* [계층 구조] */
	// => 부모 vPos + 자식의 vPos(Offset) = [자식의 위치] ... 반복

	// UI도 Collider와 비슷한 형태로 Pos가 결정된다.
	// 부모 UI 로부터의 상대적 위치 값으로 사용된다. (offset)

	/* [부모] */
	// 부모인 CObject의 FinalUpdate 내용 먼저 수행 (컴포넌트 finalupdate)
	// 부모의 위치를 먼저 잡는 과정
	CObject::FinalUpdate();

	/* [나] */
	m_vFinalPos = GetPos();

	// 자식의 위치를 [부모 vPos + 자식 vPos(offset)]을 통해 잡는 과정
	if (GetParent()) // 부모 UI가 있다면,
	{
		Vec2 vParentPos = GetParent()->GetFinalPos();

		// 추가로 나의 vPos를 더해준 값이 vFianlPos가 된다.
		m_vFinalPos += vParentPos;
	}

	/* [자식] */
	// 자식 FinalUpdate();
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->FinalUpdate();
	}
}

void CUI::Render(HDC _dc)
{
	/* [계층 구조] */

	// UI도 Tile처럼 LeftTop을 본인의 Pos로 가진다.
	Vec2 vPos = GetFinalPos(); // GetPos가 아닌, GetFinalPos를 이용하는 이유 알고 넘어가기
	Vec2 vScale = GetScale();

	Rectangle(_dc
		, int(vPos.x)
		, int(vPos.y)
		, int(vPos.x + vScale.x)
		, int(vPos.y + vScale.y));

	// 자식 Render
	render_child(_dc);
}

void CUI::update_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Update();
	}
}

void CUI::render_child(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Render(_dc);
	}
}
