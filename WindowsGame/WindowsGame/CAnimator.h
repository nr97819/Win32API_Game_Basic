#pragma once


class CObject;
class CAnimation;

class CAnimator
{
private:
	map<wstring, CAnimation*>		m_mapAnim;
	CObject*						m_pOwner;
	
public:
	void CreateAnimation();
	void FindAnimation();
	void Play();

public:
	CAnimator();
	~CAnimator();

	friend class CObject;
};

