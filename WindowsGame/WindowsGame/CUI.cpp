#include "CUI.h"


CUI::CUI()
	: m_vecChildUI{}
	, m_pParentUI(nullptr)
	, m_vFinalPos{}
{
}

CUI::~CUI()
{
	// �θ� UI�� �Ҹ�� ��, �ڽ� UI���� ���������� ��� �����ش�.
	Safe_Delete_Vec(m_vecChildUI);
}

void CUI::Update()
{
	/* [���� ����] */


	// �ڽ� Update
	update_child();
}

void CUI::FinalUpdate()
{
	/* [���� ����] */
	// => �θ� vPos + �ڽ��� vPos(Offset) = [�ڽ��� ��ġ] ... �ݺ�

	// UI�� Collider�� ����� ���·� Pos�� �����ȴ�.
	// �θ� UI �κ����� ����� ��ġ ������ ���ȴ�. (offset)

	/* [�θ�] */
	// �θ��� CObject�� FinalUpdate ���� ���� ���� (������Ʈ finalupdate)
	// �θ��� ��ġ�� ���� ��� ����
	CObject::FinalUpdate();

	/* [��] */
	m_vFinalPos = GetPos();

	// �ڽ��� ��ġ�� [�θ� vPos + �ڽ� vPos(offset)]�� ���� ��� ����
	if (GetParent()) // �θ� UI�� �ִٸ�,
	{
		Vec2 vParentPos = GetParent()->GetFinalPos();

		// �߰��� ���� vPos�� ������ ���� vFianlPos�� �ȴ�.
		m_vFinalPos += vParentPos;
	}

	/* [�ڽ�] */
	// �ڽ� FinalUpdate();
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->FinalUpdate();
	}
}

void CUI::Render(HDC _dc)
{
	/* [���� ����] */

	// UI�� Tileó�� LeftTop�� ������ Pos�� ������.
	Vec2 vPos = GetFinalPos(); // GetPos�� �ƴ�, GetFinalPos�� �̿��ϴ� ���� �˰� �Ѿ��
	Vec2 vScale = GetScale();

	Rectangle(_dc
		, int(vPos.x)
		, int(vPos.y)
		, int(vPos.x + vScale.x)
		, int(vPos.y + vScale.y));

	// �ڽ� Render
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
