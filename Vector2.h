#pragma once
#include <cmath>
#include <vector>
#include <Windows.h>


struct Vector2
{

	double x_;
	double y_;


	template<typename Tx, typename Ty> Vector2(Tx x, Ty y);
	Vector2(POINT p);
	Vector2();

	bool isIn (std::pair<Vector2, Vector2> range);
	friend Vector2 operator+  (const Vector2& v1, const Vector2& v2);
	friend Vector2 operator-  (const Vector2& v1, const Vector2& v2);
	friend Vector2 operator*  (const Vector2& v1, const double&  d );
	friend Vector2 operator*  (const Vector2& p1, const Vector2& p2);
	friend Vector2 operator/  (const Vector2& p1, const Vector2& p2);
	friend bool    operator== (const Vector2& p1, const Vector2& p2);
	friend bool    operator!= (const Vector2& p1, const Vector2& p2); 
	friend double  operator~  (const Vector2& v);
};

template<typename Tx, typename Ty> 
Vector2::Vector2(Tx x, Ty y)
	:	x_(x),
		y_(y)
{}