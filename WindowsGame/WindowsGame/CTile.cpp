#include "pch.h"
#include "CTile.h"

#include "CCamera.h"

#include "CTexture.h"


CTile::CTile()
	: m_pTileTex(nullptr)
	, m_iImgIdx(0)
{
	// �׻� ������ Tile Size�� �°� �ʱ�ȭ ���ش�.
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
}

CTile::~CTile()
{
}

void CTile::Update()
{

}

void CTile::Render(HDC _dc)
{
	// Texture�� ���ٸ�, ��� X
	if (nullptr == m_pTileTex || -1 == m_iImgIdx) // -1�� ���, �ƹ��͵� �������� ����
		return;

	UINT iWidth = m_pTileTex->Width();
	UINT iHeight = m_pTileTex->Height();

	UINT iMaxCol = UINT(iWidth / TILE_SIZE);
	UINT iMaxRow = UINT(iHeight / TILE_SIZE);

	UINT iCurRow = m_iImgIdx / iMaxCol;
	UINT iCurCol = m_iImgIdx % iMaxCol;

	// �̹��� ������ ��� index(�� ��) ���� ó�� (�ִ� ���� ������ �ִ�.)
	// (Col(��) ���� ������ iMaxCol�� �����ϱ� ���� ó�� ���ص� ���� ����.)
	if (iMaxRow <= iCurRow)
		assert(nullptr); // ������ ���� �˸�

	Vec2 vRealPos = GetPos();
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(vRealPos);
	Vec2 vScale = GetScale();

	// CTile�� ���, �ٸ� CObject����� �ٸ���, �߾��� �ƴ� LeftTop�� ��ġ������ ���´�.
	// (�׸� ��, ����)
	Rectangle(_dc
		, int(vRenderPos.x)
		, int(vRenderPos.y)
		, int(vRenderPos.x + vScale.x)
		, int(vRenderPos.y + vScale.y));

	BitBlt(_dc
		, int(vRenderPos.x)
		, int(vRenderPos.y)
		, int(vScale.x)
		, int(vScale.y)
		, m_pTileTex->GetDC()
		, int(iCurCol * TILE_SIZE)
		, int(iCurRow * TILE_SIZE)
		, SRCCOPY);
}