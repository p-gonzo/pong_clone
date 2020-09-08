#pragma once

class Vec2
{
public:
	Vec2();
	Vec2( float X, float Y );
	Vec2 operator+( Vec2 const &rhs );
	Vec2& operator+=( Vec2 const &rhs );
	Vec2 operator*( float rhs );

	float x;
    float y;
};