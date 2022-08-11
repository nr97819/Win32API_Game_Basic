#pragma once

struct Vec2
{
	float x;
	float y;

public:
	// Vector의 대각선 길이 반환
	float Length()
	{
		return sqrt((x * x) + (y * y));
	}

	// Vector의 Normailize 함수
	Vec2& Normalize()
	{
		float fLen = Length();

		// 제로 벡터 예외 처리 -> 길이가 0인 경우 = (x=0 && y=0)
		assert(fLen != 0.f);

		x /= fLen;
		y /= fLen;

		return *this;
	}

public:
	Vec2& operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

	Vec2 operator + (Vec2 _vOther)
	{
		return Vec2(x += _vOther.x, y += _vOther.y);
	}

	Vec2 operator - (Vec2 _vOther)
	{
		return Vec2(x -= _vOther.x, y -= _vOther.y);
	}

	Vec2 operator * (Vec2 _vOther)
	{
		return Vec2(x *= _vOther.x, y *= _vOther.y);
	}

	Vec2 operator / (Vec2 _vOther)
	{
		// Divided by Zero 예외 처리
		assert(!(0.f == _vOther.x || 0.f == _vOther.y));

		return Vec2(x /= _vOther.x, y /= _vOther.y);
	}

public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vec2(int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{}

	Vec2(const POINT& _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{}

	/*Vec2(Vec2& vPos)
		: x(vPos.x)
		, y(vPos.y)
	{}*/
};