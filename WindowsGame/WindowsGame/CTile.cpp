#include "pch.h"
#include "CTile.h"

#include "CCamera.h"

#include "CTexture.h"


CTile::CTile()
	: m_pTileTex(nullptr)
	, m_iImgIdx(0)
{
	// 항상 정해진 Tile Size에 맞게 초기화 해준다.
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
	// Texture가 없다면, 출력 X
	if (nullptr == m_pTileTex || -1 == m_iImgIdx) // -1인 경우, 아무것도 참조하지 않음
		return;

	UINT iWidth = m_pTileTex->Width();
	UINT iHeight = m_pTileTex->Height();

	UINT iMaxCol = UINT(iWidth / TILE_SIZE);
	UINT iMaxRow = UINT(iHeight / TILE_SIZE);

	UINT iCurRow = m_iImgIdx / iMaxCol;
	UINT iCurCol = m_iImgIdx % iMaxCol;

	// 이미지 범위를 벗어난 index(행 값) 예외 처리 (최대 행은 정해져 있다.)
	// (Col(열) 값은 어차피 iMaxCol로 나누니까 예외 처리 안해도 문제 없다.)
	if (iMaxRow <= iCurRow)
		assert(nullptr); // 무조건 예외 알림

	Vec2 vRealPos = GetPos();
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(vRealPos);
	Vec2 vScale = GetScale();

	// CTile의 경우, 다른 CObject들과는 다르게, 중앙이 아닌 LeftTop을 위치값으로 갖는다.
	// (그릴 때, 주의)
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