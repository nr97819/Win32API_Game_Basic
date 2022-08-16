#pragma once


class CAnimator;
class CTexture;

struct tAnimFrm
{
	Vec2 vLT;			// 자를 LeftTop 위치
	Vec2 vSlice;		// 자를 크기
	float fDuration;	// 지속 시간
};

class CAnimation
{
private:
	wstring				m_strName;
	CAnimator*			m_pAnimator;
	CTexture*			m_pTex;		// animatino이 사용하는 리소스에 대한 정보
	vector<tAnimFrm>	m_vecFrm;	// 각 프레임에 대한 정보 tAnimFrm을 담은 벡터
	int					m_iCurFrm;	// 현재 frame (그려질 현재 frame)
	float				m_fAccTime; // 누적 시간

	bool				m_bFinish;	// 1바퀴 재생 완료 여부

public:
	void Update();
	void Render(HDC _dc);

public:
	const wstring& GetName() { return m_strName; }
	
	bool IsFinish() { return m_bFinish; }
	void SetFrame(int _iFrameIdx) 
	{ 
		m_bFinish = false;		// finish 상태 해제
		m_iCurFrm = _iFrameIdx;	// 해당 index로 프레임 설정
		m_fAccTime = 0.f;		// 누적 시간 0.f로 초기화
		// -> 문제 있는 것 같다. (나중에 수정 하자)
	}

private:
	// 한 번 정해진 이름은 다시는 바뀌면 안되므로, private으로 설정
	void SetName(const wstring& _strName) { m_strName = _strName; }

public:
	void Create(const wstring& _strName, CTexture* _pTex
		, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);

public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

