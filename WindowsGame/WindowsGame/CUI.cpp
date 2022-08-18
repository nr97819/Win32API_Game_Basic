#include "CUI.h"

#include "CKeyMgr.h"
#include "CCamera.h"


//CUI::CUI() {}
CUI::CUI(bool _bCamAff)
	: m_vecChildUI{}
	, m_pParentUI(nullptr)
	, m_vFinalPos{}
	, m_bCamAffected(false)
	, m_bMouseOn(false)
	, m_bLBtnDown(false)
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
	// �� Update
	// ...

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

	// (beta ���) UI Mouse üũ
	MouseOnCheck();

	/* [�ڽ�] */
	// �ڽ� FinalUpdate();
	finalupdate_child();
}

void CUI::Render(HDC _dc)
{
	/* [���� ����] */

	// UI�� Tileó�� LeftTop�� ������ Pos�� ������.
	Vec2 vPos = GetFinalPos(); // GetPos�� �ƴ�, GetFinalPos�� �̿��ϴ� ���� �˰� �Ѿ��
	Vec2 vScale = GetScale();

	if (m_bCamAffected)
	{
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}

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

void CUI::finalupdate_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->FinalUpdate();
	}
}

void CUI::render_child(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Render(_dc);
	}
}

void CUI::MouseOnCheck()
{
	Vec2 vMousePos = MOUSE_POS;
	Vec2 vScale = GetScale();

	// ���� CamAffected UI���, ī�޶� renderPos�� �̿�
	if (m_bCamAffected)
	{
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
	}

	// ���콺 Ŀ���� UI ������ On�� ���¶��,
	if (m_vFinalPos.x <= vMousePos.x && m_vFinalPos.x + vScale.x >= vMousePos.x &&
		m_vFinalPos.y <= vMousePos.y && m_vFinalPos.y + vScale.y >= vMousePos.y)
	{
		m_bMouseOn = true;
	}
	// ���콺 Ŀ���� UI ������ On�� ���°� �ƴ϶��,
	else
	{
		m_bMouseOn = false;
	}
}

void CUI::MouseOn()
{
}

void CUI::MouseLBtnDown()
{
}

void CUI::MosueLBtnUp()
{
}

void CUI::MosueLBtnClicked()
{
}
