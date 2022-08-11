#include "pch.h"
#include "SelectGDI.h"

#include "CCore.h"


SelectGDI::SelectGDI(HDC _dc, PEN_TYPE _ePenType)
	: m_hDC(_dc)
	, m_hDefaultPen(nullptr)
	, m_hDefaultBrush(nullptr)
{
	HPEN hGreenPen = CCore::GetInst()->GetPen(_ePenType);
	m_hDefaultPen = (HPEN)SelectObject(_dc, hGreenPen);
}

SelectGDI::SelectGDI(HDC _dc, BRUSH_TYPE _eBrushType)
	: m_hDC(_dc)
	, m_hDefaultPen(nullptr)
	, m_hDefaultBrush(nullptr)
{
	HBRUSH hHollowBrush = CCore::GetInst()->GetBrush(_eBrushType);
	m_hDefaultBrush = (HBRUSH)SelectObject(_dc, hHollowBrush);
}

SelectGDI::~SelectGDI()
{
	// ���� �ٸ� Pen�� ���� �ִٸ�
	if (nullptr != m_hDefaultPen)
	{
		SelectObject(m_hDC, m_hDefaultPen);
		m_hDefaultPen = nullptr;
	}

	// ���� �ٸ� Brush�� ���� �ִٸ�
	if (nullptr != m_hDefaultBrush)
	{
		SelectObject(m_hDC, m_hDefaultBrush);
		m_hDefaultBrush = nullptr;
	}
}
