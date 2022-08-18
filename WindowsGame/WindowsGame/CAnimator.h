#pragma once


class CObject;
class CAnimation;
class CTexture;

class CAnimator
{
private:
	map<wstring, CAnimation*>		m_mapAnim;
	CAnimation*						m_pCurAnim;		// 현재 재생중인 Animation
	CObject*						m_pOwner;

	bool							m_bRepeat;		// 반복재생 여부

public:
	CObject* GetObj() { return m_pOwner; }

public:
	void CreateAnimation(const wstring& _strName, CTexture* _pTex
						, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);
	CAnimation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName, bool _bRepeat);	// 현재 animation (pCurAnim)를 Play 해주는 함수

public:
	void Update();
	void FinalUpdate();
	void Render(HDC _dc);

public:
	CAnimator();
	~CAnimator();

	friend class CObject;
};

